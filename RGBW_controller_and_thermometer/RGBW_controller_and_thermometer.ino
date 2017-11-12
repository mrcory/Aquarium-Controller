

/*LED Controller for Aquarium
   by: Cory McGahee
   Free for non-commercial use only.
   This header must be included in all distributions.
   Credits:
   Several presets from http://planetpixelemporium.com/tutorialpages/light.html
   Temp sensor code http://www.milesburton.com/?title=Dallas_Temperature_Control_Library

   Done:
   Get temp
   Get time
   Fixed fadetime
   Display temp

   Todo:
   Add button controls
*/


const String ver = "0.1-pre"; //Program Version

#include <TimeLib.h>
#include <TimeAlarms.h>
#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Cmd.h>
#include "config.h" //Config file



//i2c device stuff
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
RTC_DS3231 rtc; //Declare RTC (?)


//Internal Variables
int ledState = 0; //0 for turning off, 1 for turning on
int debugLVL = 0; //Print some debug stuff (0-3)
DateTime timeNow; //Hold time
int ledUpdate = 1;
float ledP = 0; //Led Intensity 1-255 Don't adjust
int screenPage = 0; //What page to be displayed on the screen




//Color presets (R,G,B,W)
const int colorWhite[4] {255, 255, 255, 0}; //White without 4th channel
const int colorWhiteFull[4] {255, 255, 255, 255}; //white with 4th channel
const int colorHighNoon[4] {255, 255, 251, 0};
const int colorOvercast[4] {201, 226, 255, 0};
const int colorBlacklight[4] {167, 0, 255, 0};
const int colorMoon[4] {151, 147, 148, 0}; //Test

//Include other files
#include "temp.h" //Tempurature functions and variables
#include "debug.h" //Debug functions
#include "screen.h"
#include "commands.h" //Functions for the commands below

void setup() {

  Serial.begin(9600);
  cmdInit(&Serial);
  updateTime();

  //Add Commands
  cmdAdd("ledR", ledRedUpdate);
  cmdAdd("ledw", ledWhiteUpdate);
  cmdAdd("ledg", ledGreenUpdate);
  cmdAdd("ledb", ledBlueUpdate);
  cmdAdd("color", colorChange);
  cmdAdd("debug", debugUpdate);
  cmdAdd("ledpower", ledPower);
  cmdAdd("colorSet", colorSet);
  cmdAdd("screen", screenChange);


  //Create Alarms and Timers
  Alarm.alarmRepeat(timeOn[0], timeOn[1], timeOn[2], turnOn); //Turn on led
  Alarm.alarmRepeat(timeOff[0], timeOff[1], timeOff[2], turnOff); //Turn off led
  Alarm.alarmRepeat(0, 0, 0, updateTime); //Update Arduino time at midnight
  Alarm.timerRepeat(tempTime, tempUpdate); //Call temp update

  //Do Some Setup
  ledP = ledPMin; //Set power to minimum
  if (fadeTime > 0) {fadeStep = (ledPT / (fadeTime * 60.0));} else {fadeStep = 255;} //Make fadeStep from fadeTime or make it instant (255)
  rtc.begin(); //Initialize rtc
  timeNow = rtc.now(); //Set time
  sensors.begin(); //Start sensor lib
  
  display.begin(SSD1306_SWITCHCAPVCC, displayAddress); //Initialize with I2C address (CHECK THIS)

  //Draw Version
  display.clearDisplay();
  display.setCursor(0,0); //Set text position
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Controller Version: ");
  display.print(ver);
  display.display();
  delay(1500); //Show verision for a bit
  display.clearDisplay(); //Clear logo
  tempUpdate(); //Update temp
  displayUpdate(); //Display it
}

//Loop runs once per second
void loop() {
  debugFunc();
  displayUpdate();
  Alarm.delay(500);
  cmdPoll();
  timeNow = rtc.now(); //Update time

  if (ledState == 1 && ledPT > ledP) { //Adjust power to target +
    ledP = ledP + fadeStep;
    ledUpdate = 1;
  }

  if (ledState == 0 && ledPMin < ledP) { //Adjust power to target -
    ledP = ledP - fadeStep;
    ledUpdate = 1;
  }

  //If ledP oversteps power target, set value to power target
  if (ledState == 1 && ledP > ledPT) {
    ledP = ledPT;
  }

  if (ledState == 0 && ledP <= ledPMin) {
    ledP = ledPMin;
  }


  if (ledUpdate == 1) { //Write LED Output
    analogWrite(ledPinR, map(ledR, 0, 255, 0, ledP)); //Set power red
    analogWrite(ledPinG, map(ledG, 0, 255, 0, ledP)); //Set power green
    analogWrite(ledPinB, map(ledB, 0, 255, 0, ledP)); //Set power blue
    analogWrite(ledPinW, map(ledW, 0, 255, 0, ledP)); //Set power white
    if (debugLVL > 0) {
    Serial.println("Output Update");} //If debug enabled say when updated
    ledUpdate = 0; //Don't analogwrite unless needed
  }
}


void updateTime() { //Update time from rtc
  //rtc.adjust(DateTime(timeNow.year(), timeNow.month(), timeNow.day(), timeNow.hour()-1, timeNow.minute(), timeNow.second()));
  
  timeNow = rtc.now();
  setTime(timeNow.hour(), timeNow.minute(), timeNow.second(), timeNow.month(), timeNow.day(), timeNow.year());

  Alarm.delay(500);
}


