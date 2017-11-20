/*LED Controller for Aquarium
   by: Cory McGahee
   Free for non-commercial use only.
   This header must be included in all distributions.
   Original GitHub Upload: 11/6/2017
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


const String ver = "-pre"; //Program Version

#include <TimeLib.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include <DS3231.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Cmd.h>
#include "config.h" //Config file

//i2c device stuff
Adafruit_SSD1306 display(4);
RTClib RTC; //Declare RTC

//Internal Variables
int ledState = 0; //0 for turning off, 1 for turning on
DateTime timeNow; //Hold time
int ledUpdate = 1;
float ledP = 0; //Led Intensity 1-255 Don't adjust
int screenPage = 1; //What page to be displayed on the screen
boolean DST;

//Color presets (R,G,B,W)
const int colorWhite[4] {255, 255, 255, 0}; //White without 4th channel
const int colorWhiteFull[4] {255, 255, 255, 255}; //white with 4th channel
const int colorHighNoon[4] {255, 255, 251, 0};
const int colorOvercast[4] {201, 226, 255, 0};
const int colorBlacklight[4] {167, 0, 255, 0};
const int colorMoon[4] {151, 147, 148, 0}; //Test

//Include other files
#include "temp.h" //Tempurature functions and variables
#include "screen.h"
#include "commands.h" //Functions for the commands below

AlarmID_t LedOn;
AlarmID_t LedOff;
AlarmID_t TimeUpdate;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  cmdInit(&Serial);
  timeNow = RTC.now(); //Set time
  setTime(timeNow.hour(),timeNow.minute(),timeNow.second(),timeNow.month(),timeNow.day(),timeNow.year());

  //Add Commands
  cmdAdd("color", colorChange);
  cmdAdd("ledpower", ledPower);
  cmdAdd("ledpowernow", ledPowerNow);
  cmdAdd("colorSet", colorSet);
  cmdAdd("screen", screenChange);
  cmdAdd("led", ledChange);
  cmdAdd("on",timerOn);
  cmdAdd("off",timerOff);
  cmdAdd("temprst",tempRngRst);
  cmdAdd("dst",DSTset);


  //Create Alarms and Timers
 LedOn = Alarm.alarmRepeat(timeOn[0],timeOn[1],timeOn[3],timerOn); //Turn on led
 LedOff = Alarm.alarmRepeat(timeOff[0],timeOff[1],timeOff[2],timerOff); //Turn off led
 TimeUpdate = Alarm.alarmRepeat(0,0,0,timeUpdate);
  Alarm.timerRepeat(tempTime, tempUpdate); //Call temp update

  //Do Some Setup
  ledP = ledPMin; //Set power to minimum
  if (fadeTime > 0) {
    fadeStep = (ledC[4] / (fadeTime * 60.0)); //Make fadeStep from fadeTime or make it instant (255)
  } else {
    fadeStep = 255;
  }
  
  
  sensors.begin(); //Start sensor lib

  display.begin(SSD1306_SWITCHCAPVCC, displayAddress); //Initialize with I2C address
  display.setTextColor(WHITE); //Set text color so it is visible

  tempUpdate(); //Update temp
  tempRngRst(); //Reset temp min/max range
}

//Loop runs once per second
void loop() {
  displayUpdate();
  Alarm.delay(500);
  cmdPoll();

  if (ledState == 1 && ledC[4] > ledP) { //Adjust power to target +
    ledP = ledP + fadeStep;
    ledUpdate = 1;
  }

  if (ledState == 0 && ledPMin < ledP) { //Adjust power to target -
    ledP = ledP - fadeStep;
    ledUpdate = 1;
  }

  //If ledP oversteps power target, set value to power target
  if (ledState == 1 && ledP > ledC[4]) {
    ledP = ledC[4];
  }

  if (ledState == 0 && ledP <= ledPMin) {
    ledP = ledPMin;
  }


  if (ledUpdate == 1) { //Write LED Output
    analogWrite(ledPinR, map(ledC[0], 0, 255, 0, ledP)); //Set power red
    analogWrite(ledPinG, map(ledC[1], 0, 255, 0, ledP)); //Set power green
    analogWrite(ledPinB, map(ledC[2], 0, 255, 0, ledP)); //Set power blue
    analogWrite(ledPinW, map(ledC[3], 0, 255, 0, ledP)); //Set power white
    ledUpdate = 0; //Don't analogwrite unless needed
  }


}

void timeUpdate() { //Update time and reset alarms
  timeNow = RTC.now(); //Set time
  setTime(timeNow.hour(),timeNow.minute(),timeNow.second(),timeNow.month(),timeNow.day(),timeNow.year());
  
  Alarm.free(LedOn);
  LedOn =  LedOn = Alarm.alarmRepeat(timeOn[0],timeOn[1],timeOn[3],timerOn); //Turn on led
  Alarm.free(LedOff);
  LedOff = Alarm.alarmRepeat(timeOff[0],timeOff[1],timeOff[2],timerOff); //Turn off led
  Alarm.free(TimeUpdate);
  TimeUpdate = Alarm.alarmRepeat(0,0,0,timeUpdate);
}

