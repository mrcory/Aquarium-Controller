

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
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Cmd.h>






//i2c device stuff
const int OLED_RESET = 4;
Adafruit_SSD1306 display(OLED_RESET);
RTC_DS3231 rtc; //Declare RTC (?)


//Internal Variables
int ledState = 0; //0 for turning off, 1 for turning on
int debug = 0; //Print some debug stuff (0-3)
DateTime timeNow; //Hold time
float temp;
int ledUpdate = 1;
float ledP = 0; //Led Intensity 1-255 Don't adjust



//Pin Connections
const int ledPinR = 2;
const int ledPinG = 4;
const int ledPinB = 6;
const int ledPinW = 8; //White channel
const int tempPin = 10; //DS18B20 pin
const int ONE_WIRE_BUS = 12; //Data wire pin
const int displayAddress = 0x3D; //Display i2c address


//Colors (0-255) Set the initial color.
int ledPT = 255; //Intensity target 1-255 adjust this
int ledR = 255;
int ledG = 255;
int ledB = 255;
int ledW = 255;

//Various Configs
float fadeStep = 5; //Increase per step
const int ledPMin = 0; //Minimum led power output
const int tempTime = 10; //Temp update interval in seconds
const float fadeTime = 30; //Fade time in minutes 


OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); //// Pass our oneWire reference to Dallas Temperature.

//Color presets (R,G,B,W)
const int colorWhite[4] {255,255,255,0}; //White without 4th channel
const int colorWhiteFull[4] {255,255,255,255}; //white with 4th channel
const int colorHighNoon[4] {255,255,251,0};
const int colorOvercast[4] {201,226,255,0};
const int colorBlacklight[4] {167,0,255,0};
const int colorMoon[4] {151,147,148,0}; //Test


void setup() {
  Serial.begin(9600);
  cmdInit(&Serial);

  //Add Commands
  cmdAdd("ledr", ledRedUpdate);
  cmdAdd("ledw", ledWhiteUpdate);
  cmdAdd("ledg", ledGreenUpdate);
  cmdAdd("ledb", ledBlueUpdate);
  cmdAdd("color", colorChange);
  cmdAdd("debug", debugUpdate);
  cmdAdd("ledOn", turnOn);
  cmdAdd("colorSet", colorSet);

  
  
  Alarm.alarmRepeat(8, 30, 0, turnOn); //Turn on led
  Alarm.alarmRepeat(21, 30, 0, turnOff); //Turn off led
  Alarm.alarmRepeat(0,0,0,updateTime); //Update Arduino time at midnight

  Alarm.timerRepeat(tempTime,tempUpdate); //Call temp update


  ledP = ledPMin; //Set power to minimum
  fadeStep = (ledPT / (fadeTime * 60.0)); //Set fade step based on time

  
  //Init Various
  rtc.begin(); //Initialize rtc
  timeNow = rtc.now(); //Set time
  sensors.begin(); //Start sensor lib
  
  display.begin(SSD1306_SWITCHCAPVCC, displayAddress); //Initialize with I2C address (CHECK THIS)

  //Draw Logo
  display.setCursor(10,10); //Set text position
  display.print("Controller Version: ");
  display.print(ver);
  //delay(1500);
  display.clearDisplay(); //Clear logo

  //DateTime now = rtc.now(); //Update time
  //setTime(timeNow.hour(),timeNow.minute(),timeNow.second(),timeNow.month(),timeNow.day(),timeNow.year()); // set time to Saturday 8:29:00am Jan 1 2011

  if (debug == 0) {Serial.println("Debug disabled. (Just a reminder.)"); }
  tempUpdate(); //Update temp and display it
}

//Loop runs once per second
void loop() {
  Alarm.delay(1000);
  cmdPoll();
  timeNow = rtc.now(); //Update time



  //Adjust power to target +
  if (ledState == 1 && ledPT > ledP) {
    ledP = ledP + fadeStep;
    ledUpdate = 1;
  }
  
  //Adjust power to target -
  if (ledState == 0 && ledPMin < ledP) {
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


    
if (ledUpdate == 1) {
    analogWrite(ledPinR, map(ledR, 0, 255, 0, ledP)); //Set power red
    analogWrite(ledPinG, map(ledG, 0, 255, 0, ledP)); //Set power green
    analogWrite(ledPinB, map(ledB, 0, 255, 0, ledP)); //Set power blue
    analogWrite(ledPinW, map(ledW, 0, 255, 0, ledP)); //Set power white
    Serial.println("Output Update");
}

if (debug > 0) {
  if (debug == 1) { //Debug information Set 1
    Serial.println();
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.print(second());
    Serial.print(" ");
    Serial.print("Power State: ");
    Serial.print(ledState);
    Serial.println(" ");
  }

  if (debug == 2) { //Debug Info lvl 2
    Serial.print("Red "); Serial.print(map(ledR, 0, 255, 0, ledP));
    Serial.print(" Green "); Serial.print(map(ledG, 0, 255, 0, ledP));
    Serial.print(" Blue "); Serial.print(map(ledB, 0, 255, 0, ledP));
    Serial.print(" White "); Serial.print(map(ledW, 0, 255, 0, ledP));
    Serial.print(" Power "); Serial.println(ledP);
  }

  if (debug == 3) {
    Serial.print("Fade Steps ");
    Serial.print(fadeStep);
    Serial.print(" Temp ");
    Serial.println(temp);
  }

}

  ledUpdate = 0; //Don't analogwrite unless needed

}

void turnOn() {
  ledState = 1;
  ledUpdate = 1;
  Serial.println("State turn on");
}

void turnOff() {
  ledState = 0;
  ledUpdate = 1;
  Serial.println("State turn off");
}

void colorChange(int colorSet[5]) {
    ledR = colorSet[0];
    ledG = colorSet[1];
    ledB = colorSet[2];
    ledW = colorSet[3];
//    ledP = powerSet;
    ledUpdate = 1;
}

void updateTime() { //Update time from rtc
    timeNow = rtc.now();
    setTime(timeNow.hour(),timeNow.minute(),timeNow.second(),timeNow.month(),timeNow.day(),timeNow.year());
}

void tempUpdate() { //Update temp and display
  sensors.requestTemperatures(); //Get temp reading
  temp = sensors.getTempFByIndex(0); //Set temp from first sensor

  //Display
  display.clearDisplay(); //Clean the Screen
  display.setCursor(5,5); //Set cursor location
  display.setTextSize(5); //Make it large
  display.print("Temperature: ");
  display.print(temp);
  display.print("°F");
  display.setTextSize(1); //Now, turn it back down
}

void debugUpdate(int arg_cnt, char **args) { //Update debug value in serial monitor
    debug = cmdStr2Num(args[1],10);
    Serial.print("Debug changed to ");
    Serial.println(debug);
    
}

void ledRedUpdate(int arg_cnt, char **args) {
    ledR = cmdStr2Num(args[1],10);
    //Serial.println(cmdStr2Num(args[1],10));
    Serial.print("Red Updated to ");
    Serial.println(ledR);
    ledUpdate = 1;
}

void ledBlueUpdate(int arg_cnt, char **args) {
    ledB = cmdStr2Num(args[1],10);
    //Serial.println(cmdStr2Num(args[1],10));
    Serial.print("Blue Updated to ");
    Serial.println(ledB);
    ledUpdate = 1;
}

void ledGreenUpdate(int arg_cnt, char **args) {
    ledG = cmdStr2Num(args[1],10);
    //Serial.println(cmdStr2Num(args[1],10));
    Serial.print("Green Updated to ");
    Serial.println(ledG);
    ledUpdate = 1;
}

void ledWhiteUpdate(int arg_cnt, char **args) {
    ledW = cmdStr2Num(args[1],10);
    //Serial.println(cmdStr2Num(args[1],10));
    Serial.print("White Updated to ");
    Serial.println(ledW);
    ledUpdate = 1;
}

void colorSet(int arg_cnt, char **args) {
  if (arg_cnt >= 7) {
    ledR = cmdStr2Num(args[1],10);
    ledG = cmdStr2Num(args[2],10);
    ledB = cmdStr2Num(args[3],10);
    ledW = cmdStr2Num(args[4],10);
    ledP = cmdStr2Num(args[5],10);
    ledState = cmdStr2Num(args[6],10);
  }
}

