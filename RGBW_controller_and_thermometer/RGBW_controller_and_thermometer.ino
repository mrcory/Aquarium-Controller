


/*LED Controller for Aquarium
   by: Cory McGahee
   Free for non-commercial use only.
   This header must be included in all distributions.
   Original GitHub Upload: 11/6/2017
   Credits:
   Temp sensor code http://www.milesburton.com/?title=Dallas_Temperature_Control_Library
   GPS incoming info function taken from example program
todo:
*/

//const String ver = "2.2.0-dev"; //Program Version
//Last Tested version: 2.2.0-dev


#include <TimeLib.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <EEPROM.h>



#include "config.h" //Config file




//Include the correct library for the screen used.
#if screenTFT
  #include <Adafruit_ST7735.h>
#endif

#if screenOLED
  #include <Adafruit_SSD1306.h>
#endif

//Are we gonna enable serial monitor based control?
#if serialCommands
  #include <Cmd.h>
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


//Setup our screen.
#if screenOLED == true
  Adafruit_SSD1306 display(oled_width, oled_height, &Wire, 4); //Set the screen resolution
#endif

#if screenTFT == true
  Adafruit_ST7735 display = Adafruit_ST7735(53, 50, 51, 52, 4); //Set the screen pins
#endif

//Internal Variables
byte ledState = 0; //0 for turning off, 1 for turning on
byte ledUpdate = 1;
float ledP = 0; //Led Intensity 1-255 Don't adjust
byte screenPage = 1; //What page to be displayed on the screen
byte ledC[5] = {255}; //Fill with a default value
int ledTarget[5] = {0};
byte oldTimer = 100;
int convOnTimes[times]; //Stores the timer on times in a function compatible format
int convOffTimes[times]; //Store the timer off times in a function compatible format
byte currentTimer = 0; //The current timer being used. Determines what colors should be used.
bool oldState = false; //Just used for triggering
bool firstRun = true; //Label for first loop
bool ledHold = false; //Hold led adjustment

#if wifiEnable
  int ledWifi[5] = {0};

#endif


      char buf_mySSID[150];
      char buf_wifiPassword[150];
      char buf_token[150];

//Include other files
#include "universalFunc.h" //Some universal functions



//----WIFI Variabeles
  String mySSID;
  String wifiPassword;
  String blynkToken;



#if tempEnable
  #include "temp.h" //Tempurature functions and variables
#endif

//Some more includes
#include "commands.h" //Functions for the commands below
#include "lightmode.h" //New light controls


#if wifiEnable
  #include <ESP8266_Lib.h>
  #include <BlynkSimpleShieldEsp8266.h>
  #include <Ethernet.h>
  #include <Blynk.h>
#endif

#if waterFillEnable
  #include "water.h"
#endif

#if wifiEnable
  #include "wifi.h" //Blynk and wifi related stuff

  ESP8266 wifi(&espSerial);
#endif



#if screenEnable
  #if screenOLED == true
    #include "screencommands.h" //Supporting functions for below.
    #include "screen.h" //Used for controlling the display.
#endif

  #if screenTFT == true
    #include "tftcommand.h" //Supporting functions for below.
    #include "tft.h" //Used for controlling the display.
  #endif
#endif

#include "time.h" //Time stuff moved here

#if blynkRTC
#include <WidgetRTC.h>
WidgetRTC rtc;
BlynkTimer timer1;
#endif



void setup() {

#if waterFillEnable
  waterSetup();
#endif



  #if gpsRtc
    gpsSerial.begin(gpsBaud); //Start the serial port for the gps unit
  #endif

  Wire.begin();
  Serial.begin(9600);

  

  checkConfig(); //Check if we need to load the config at start


  #if serialCommands //If not defined then don't create commands
                     //See top of commands.h for reference
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
    cmdAdd("time",updateTimeNow);

      cmdAdd("pass",wifiPass);
      cmdAdd("ssid",wifiSSID);
      cmdAdd("token",blynkSet);
   
  #endif

  #if screenEnable && serialCommands
    cmdAdd("screen", screenChange);
  #endif



  //Do Some Setup
  colorChange1(true,currentTimer); //Force a color change

  ledP = ledPMin; //Set power to minimum

  if (fadeTime > 0) { //If a fadetime has been set solve for fadeStep to match it
    fadeStep = (ledC[4] / (fadeTime * 60.0)); //Make fadeStep from fadeTime or make it instant (255)
  } else {
    fadeStep = 255; //If fateTime is set to 0 then just turn on and off completely
  }

  #if tempEnable
    tempSetup(); //Perform the needed setup actions from temp.h
  #endif

  #if screenEnable
      screenSetup(); //Perform the setup for either screen
  #endif

  controlSetup(); //Convert times and other setup stuff.
  timerSetup(); //Start counters


  #if wifiEnable
  
    espSerial.begin(espBaud);
    
      #if defined(blynk_server)

      //Convert the stored strings to Char

      mySSID.toCharArray(buf_mySSID,150);
      blynkToken.toCharArray(buf_token,150);
      wifiPassword.toCharArray(buf_wifiPassword,150);


      //Okay, changed to a selfhosted server. Public shouldn't be able to access it.
      
        Blynk.begin(buf_token,wifi,buf_mySSID,buf_wifiPassword,blynk_server,blynk_port);
        #else
      #if defined(blynk_ip)
      Blynk.begin(buf_token,wifi,buf_mySSID,buf_wifiPassword,blynk_ip,blynk_port);
      #else
        #error "No server target. Check configPlus.h for server."
      #endif
    #endif
    
    
  #endif


#if blynkRtc
  rtc.begin();
  setSyncInterval(timeToUpdate/1000);
#endif

  updateTimeNow(); //Update time via selected time keeper




if (debugMe == true) {
  wifiFeedback(); //Print wifi info
}

}


void loop() {

  #if waterFillEnable
    waterRun();
  #endif

  
  #if wifiEnable
  
  if (Blynk.connected() == true) {
    Blynk.run();
    //timer1.run();
  } else {
    Serial.println("[BLYNK] Attempting to connect...");
    Blynk.connect(3000); //Attempt to connect for 3 seconds.
    if (Blynk.connected() == true) {Serial.println("[BLYNK] Connected!");}
    
  }
  #endif

  #if gpsRtc //If using GPS for RTC read the serial buffer in
    gpsRead();
  #endif



  timerCheck();

  #if serialCommands
    cmdPoll(); //Poll for commands via Serial
  #endif

  #if gpsRtc //If using GPS for RTC read the serial buffer in
    gpsRead();
  #endif

  if (timer(1000,0)) { //Adjust LED every second
    if (!ledHold) {
      ledAdjust(1);
    } else {
      ledAdjust(0);
  }}

  #if tempEnable
    if (timer(tempTime*1000,1)) { //Timer for tempUpdate()
      tempUpdate();
      
      #if wifiEnable
        sendTemp(); //Send temp to Blynk
      #endif
    }
  #endif

  if (timer(timeToUpdate,2)) { //Update time
    updateTimeNow();
  }

  //If ledP oversteps power target, set value to power target
  if (ledState == 1 && ledP > ledC[4]) {
    ledP = ledC[4];
  }

  if (ledState == 0 && ledP <= ledPMin) {
    ledP = ledPMin;
  }

#if wifiEnable
  //Use this when LED contol is being bypassed
  if (ledHold == true) {
    analogWrite(ledPinR, map(ledWifi[0], 0, 255, 0, ledWifi[4])); //Set power red
    analogWrite(ledPinG, map(ledWifi[1], 0, 255, 0, ledWifi[4])); //Set power green
    analogWrite(ledPinB, map(ledWifi[2], 0, 255, 0, ledWifi[4])); //Set power blue
    analogWrite(ledPinW, map(ledWifi[3], 0, 255, 0, ledWifi[4])); //Set power white
    ledUpdate = 1;
  }
#endif

  if (ledUpdate == 1 && ledHold != true) { //Write LED Output
    analogWrite(ledPinR, map(ledC[0], 0, 255, 0, ledP)); //Set power red
    analogWrite(ledPinG, map(ledC[1], 0, 255, 0, ledP)); //Set power green
    analogWrite(ledPinB, map(ledC[2], 0, 255, 0, ledP)); //Set power blue
    analogWrite(ledPinW, map(ledC[3], 0, 255, 0, ledP)); //Set power white
    ledUpdate = 0; //Don't analogwrite unless needed
  }

  #if gpsRtc //If using GPS for RTC read the serial buffer in (2 for safety)
    gpsRead();
  #endif

  #if screenEnable
    activeDisplay(); //Run the display
  #endif

} //Loop end


void DSTset() { //Set DST

  if (DST) { //If DST currently enable then disable it
    DST = false;
    Serial.println(F("[TIME] DST Disabled")); //Confirm via serial
    }
  else { //If DST current disabled the enable it
    DST = true;
    Serial.println(F("[TIME] DST Enabled")); //Confirm via Serial
    }
  updateTimeNow(); //Update time and recreate alarms


}

#if gpsRtc
  //Send info to tinyGPS++
  static void gpsRead() {
  while (gpsSerial.available() > 0)
    GPS.encode(gpsSerial.read());
  }
#endif

#if blynkRtc

void updateTimeNow() {
    
  }
#endif
