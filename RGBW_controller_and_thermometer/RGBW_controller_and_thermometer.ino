/*LED Controller for Aquarium
   by: Cory McGahee
   Free for non-commercial use only.
   This header must be included in all distributions.
   Original GitHub Upload: 11/6/2017
   Credits:
   Temp sensor code http://www.milesburton.com/?title=Dallas_Temperature_Control_Library
todo:
   Add button controls
*/

const String ver = "1.4.2-dev"; //Program Version 
//Last Tested version: 1.4.1-dev


#include <TimeLib.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#include "config.h" //Config file

#if serialCommands
  #include <Cmd.h> //Comment out when not enabling Serial commands
#endif

//Include library for time keeping.
#if ds3231 || ds1307 //If using one of these RTCs include lib
  #include <RTClib.h>
#endif

#if ds1307 //Declar "RTC" for either RTC
  RTC_DS1307 RTC;
#elif ds3231
  RTC_DS3231 RTC;
#endif

#if gpsRtc //If using a GPS device include lib
  #include <TinyGPS++.h>
#endif

//i2c device stuff
Adafruit_SSD1306 display(4); //display_reset

//Internal Variables
int ledState = 0; //0 for turning off, 1 for turning on
int ledUpdate = 1;
float ledP = 0; //Led Intensity 1-255 Don't adjust
int screenPage = 1; //What page to be displayed on the screen
int configSaved;
int ledC[5] = {255,255,255,255,100};
int ledTarget[5] = {0};
bool menuActive = false;
int oldTimer = 100;
bool lightOveride = false;

int convOnTimes[times];
int convOffTimes[times];
int currentTimer = 0;


//int arrowL = 0;
bool oldState = false;

//const int arrow [2] [6] {
//  {0,30,60,90,0,65},       //Arrow X locations
//  {18,18,18,18,51,51}         //Arrow Y locations
//};

//Include other files
#include "universalFunc.h" //Some universal functions

  #if tempEnable
    #include "temp.h" //Tempurature functions and variables
  #endif

  #if screenEnable
   #include "screencommands.h"
   #include "screen.h" //Screen functions
    #if enableMenu
      #include "menu.h"
    #endif
  #endif
 

#include "commands.h" //Functions for the commands below
#include "lightmode.h" //New light controls


#if ds3231 || ds1307 //If ds3231 or ds1307 being used, create proper timeUpdate function
  DateTime timeNow;
    void updateTimeNow() {
      timeNow = RTC.now();
      setTime((timeNow.hour() + utcOffset),timeNow.minute(),timeNow.second(),timeNow.month(),timeNow.day(),timeNow.year());
      if (DST) {adjustTime(3600);} //Adjust time for DST
    }
    #elif gpsRtc
  TinyGPSPlus GPS; //If using GPS for time decare as RTC
    void updateTimeNow() {
    
     gpsRead();


    int _utcAdjust = GPS.time.hour() + utcOffset;
    if (DST) {_utcAdjust++;} //Adjust time for DST
    if (isNegative(_utcAdjust)) {_utcAdjust = (_utcAdjust + 24);}

      setTime(_utcAdjust,GPS.time.minute(),GPS.time.second(),GPS.date.month(),GPS.date.day(),GPS.date.year());
      //adjustTime(utcOffset * 3600); //Adjust time for UTC setting
      
      Serial.print("GPS Time: ");
      Serial.print(GPS.time.hour());
      Serial.print(":");
      Serial.print(GPS.time.minute());
      Serial.print(":");
      Serial.println(GPS.time.second());

      Serial.print("Arduino Time: ");
      Serial.print(hour());
      Serial.print(":");
      Serial.print(minute());
      Serial.print(":");
      Serial.println(second());;

    }
#else
  #error "No RTC defined. Check config.h"
    }
#endif



//#if enableMenu && screenEnable //Set resistor values for buttons here
  #define _upVal 840
  #define _downVal 957
  #define _leftVal 979
  #define _rightVal 930
  #define _menuVal 700
//#endif





void setup() {
  //<><><><><><><><>
#if gpsRtc
  gpsSerial.begin(gpsBaud); //Start the serial port for the gps unit
#endif

  Wire.begin();
  Serial.begin(9600);
  updateTimeNow(); //Update time via selected time keeper
  //setTime(16,28,0,12,8,17);

  if (EEPROM.read(0) == 1) { //If 0 is 1 the autoload config
    Serial.print(F("Saved "));
    configLoad();
  }


#if serialCommands //If not defined then don't create commands

  cmdInit(&Serial);
  //Add Commands
  cmdAdd("ledpower", ledPower);
  cmdAdd("ledpowernow", ledPowerNow);
  cmdAdd("led", ledChange);
  cmdAdd("dst",DSTset);
  cmdAdd("save",configSave);
  cmdAdd("load",configLoad);
  cmdAdd("configclear",configClear);
  cmdAdd("color",colorChange1);
  cmdAdd("time",timeUpdate);
#endif

#if screenEnable && serialCommands
  cmdAdd("screen", screenChange);
#endif



  //Do Some Setup
  colorChange1(true); //Force a color change
  
  ledP = ledPMin; //Set power to minimum
  if (fadeTime > 0) { //If a fadetime has been set solve for fadeStep to match it
    fadeStep = (ledC[4] / (fadeTime * 60.0)); //Make fadeStep from fadeTime or make it instant (255)
  } else {
    fadeStep = 255; //If fateTime is set to 0 then just turn on and off completely
  }

  #if tempEnable
    tempSetup();
  #endif

  #if screenEnable
    screenSetup();
  #endif

  controlSetup(); //Convert times and other setup stuff.
  timerSetup(); //Start counters

#if enableMenu
    analogButtons.add(up);
    analogButtons.add(down);
    analogButtons.add(right);
    analogButtons.add(left);
    analogButtons.add(menu);
#endif

}


void loop() {

#if enableMenu
  analogButtons.check();
#endif
  
  //if (ledCheck() == true) {Serial.println("true");}
  timerCheck();

  #if screenEnable
    displayUpdate(); //Draw the screen for the display
  #endif
  
  #if serialCommands
    cmdPoll(); //Poll for commands via Serial
  #endif

#if gpsRtc //If using GPS for RTC read the serial buffer in
  gpsRead();
#endif

  if (timer(1000,0) && menuActive == false) { //Adjust LED every second
    ledAdjust(1);
  }

#if tempEnable
  if (timer(tempTime*1000,1)) { //Timer for tempUpdate()
    tempUpdate();
  }
#endif

  if (timer(60000,2)) { //Update time every 24 hours
    timeUpdate();
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

#if gpsRtc //If using GPS for RTC read the serial buffer in (2 for safety)
  gpsRead();
#endif
  
} //Loop end

void timeUpdate() { //Update time and reset alarms
  updateTimeNow(); //Call time update function created from selected RTC
}

void DSTset() { //Set DST
  
  if (DST) { //If DST currently enable then disable it
    DST = false;
    Serial.println(F("DST Disabled")); //Confirm via serial
    }
  else { //If DST current disabled the enable it
    DST = true;
    Serial.println(F("DST Enabled")); //Confirm via Serial
    }
  timeUpdate(); //Update time

}

#if gpsRtc
//Send info to tinyGPS++
static void gpsRead()
{
while (gpsSerial.available() > 0)
  GPS.encode(gpsSerial.read());
}
#endif

