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


const String ver = "1.2-dev"; //Program Version 

#include <Time.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Cmd.h> //Comment out when not enabling Serial commands
#include <EEPROM.h>
#include "config.h" //Config file


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
int ledHold[5]; //Holds timer1 led color value while timer 2 is in use

//Include other files
#include "temp.h" //Tempurature functions and variables
#include "screen.h" //Screen functions
#include "commands.h" //Functions for the commands below

AlarmID_t LedOn1; //Define LedOn alarm
AlarmID_t LedOff1; //Define LedOff alarm
AlarmID_t LedOn2;
AlarmID_t LedOff2;
AlarmID_t TimeUpdate; //Define TimeUpdate alarm

#if ds3231 || ds1307 //If ds3231 or ds1307 being used, create proper timeUpdate function
  DateTime timeNow;
    void updateTimeNow() {
      timeNow = RTC.now();
      setTime(timeNow.second(),timeNow.minute(),timeNow.hour(),timeNow.month(),timeNow.day(),timeNow.year());
      if (DST) {adjustTime(3600);} //Adjust time for DST
    }
    #elif gpsRtc
  TinyGPSPlus GPS; //If using GPS for time decare as RTC
    void updateTimeNow() {
      setTime(GPS.time.second(),GPS.time.minute(),GPS.time.hour(),GPS.date.month(),GPS.date.day(),GPS.date.year());
      adjustTime(utcOffset * 3600); //Adjust time for UTC setting
      if (DST) {adjustTime(3600);} //Adjust time for DST
    }
#else
  #error "No RTC defined. Check config.h"
    }
#endif

void setup() {
  Wire.begin();
  Serial.begin(9600);
  updateTimeNow(); //Update time via selected time keeper
  //setTime(timeNow.hour(),timeNow.minute(),timeNow.second(),timeNow.month(),timeNow.day(),timeNow.year()); //Set time
  setTime(19,54,0,12,4,17);

  if (EEPROM.read(0) == 1) { //If 0 is 1 the autoload config
    Serial.print(F("Saved "));
    configLoad();
  }

  for (int i=0;i<=5;i++) {ledHold[i] = ledC[i];} //Save ledC for grabbing later

#if defined (serialCommands) //If not defined then don't create commands

  cmdInit(&Serial);
  //Add Commands
  cmdAdd("ledpower", ledPower);
  cmdAdd("ledpowernow", ledPowerNow);
  cmdAdd("screen", screenChange);
  cmdAdd("led", ledChange);
  cmdAdd("temprst",tempRngRst);
  cmdAdd("dst",DSTset);
  cmdAdd("save",configSave);
  cmdAdd("load",configLoad);
  cmdAdd("configclear",configClear);
#endif

//Create Alarms and Timers
LedOn1 = Alarm.alarmRepeat(timeOn1[0],timeOn1[1],timeOn1[3],timerOn1); //Turn on led
LedOff1 = Alarm.alarmRepeat(timeOff1[0],timeOff1[1],timeOff1[2],timerOff); //Turn off led
//Timer 2
LedOn2 = Alarm.alarmRepeat(timeOn2[0],timeOn2[1],timeOn2[3],timerOn2);
LedOff2 = Alarm.alarmRepeat(timeOff2[0],timeOff2[1],timeOff2[2],timerOff);
//TimeUpdate = Alarm.alarmRepeat(0,0,0,timeUpdate); //Update time from the RTC and reset alarms
Alarm.timerRepeat(tempTime, tempUpdate); //Call temp update

  //Do Some Setup
  ledP = ledPMin; //Set power to minimum
  if (fadeTime > 0) { //If a fadetime has been set solve for fadeStep to match it
    fadeStep = (ledC[4] / (fadeTime * 60.0)); //Make fadeStep from fadeTime or make it instant (255)
  } else {
    fadeStep = 255; //If fateTime is set to 0 then just turn on and off completely
  }
  
  
  sensors.begin(); //Start sensor lib

  display.begin(SSD1306_SWITCHCAPVCC, displayAddress); //Initialize with I2C address
  display.setTextColor(WHITE); //Set text color so it is visible

  delay(250); //Give some time for the temp probe to start
  tempUpdate(); //Update temp
  delay(250); //Give some time for the temp probe to start
  tempRngRst(); //Reset temp min/max range
}

//Loop runs once per second
void loop() {
  displayUpdate(); //Draw the screen for the display
  Alarm.delay(500);
  
  #if defined (serialCommands)
    cmdPoll(); //Poll for commands via Serial
  #endif

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
  updateTimeNow(); //Call time update function created from selected RTC
  
  Alarm.free(LedOn1); //Free alarm so we can recreate it with a new time (or the same)
  LedOn1 = Alarm.alarmRepeat(timeOn1[0],timeOn1[1],timeOn1[3],timerOn1); //Turn on led
  Alarm.free(LedOff1); //Free alarm so we can recreate it with a new time (or the same)
  LedOff1 = Alarm.alarmRepeat(timeOff1[0],timeOff1[1],timeOff1[2],timerOff); //Turn off led
  Alarm.free(TimeUpdate); //Free alarm so we can recreate it with a new time (or the same)
  TimeUpdate = Alarm.alarmRepeat(0,0,0,timeUpdate);

  if (timerMode == 2) { //If double timer mode is enabled
    if (timeOn1 != timeOn2 || timeOff1 != timeOff2) { //If timers are not set for the same time
      Alarm.free(LedOn2); //Free alarm so we can recreate it with a new time (or the same)
      LedOn2 = Alarm.alarmRepeat(timeOn2[0],timeOn2[1],timeOn2[3],timerOn2); //Turn on led
      Alarm.free(LedOff2); //Free alarm so we can recreate it with a new time (or the same)
      LedOff2 = Alarm.alarmRepeat(timeOff2[0],timeOff2[1],timeOff2[2],timerOff); //Turn off led
      Alarm.free(TimeUpdate); //Free alarm so we can recreate it with a new time (or the same)
   } else { //If in single timer mode just free them
    Alarm.free(LedOn2);
    Alarm.free(LedOff2);
  }
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
  timeUpdate(); //Update time and recreate alarms
}



