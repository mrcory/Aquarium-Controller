/*
   Variables for configureing various things.
*/


//Temperature Settings
char tempUnit = 'F'; //What unit do you want? (C or F)
int tempWarnHi = 82; //High temp warning. (Set with the same unit as above)
int tempWarnLo = 72; //Low temp warning. (Set with the same unit as above)

//Pin Connections 
const int ledPinR = 9; //Red 9
const int ledPinG = 10; //Green 10
const int ledPinB = 11; //Blue 11
const int ledPinW = 8; //White channel 8
const int tempPin = 12; //DS18B20 pin
const int displayAddress = 0x3c; //Display i2c address (Woking with my ebay oled)

//Various Configs
const int ledPMin = 0; //Minimum led power output 0-255
const int tempTime = 4; //Temp update interval in seconds 0-255
int fadeTime = 10; //Fade time in minutes 0-255



//Time Keeping. Only one can be true
#define ds3231 false
#define ds1307 false
#define gpsRtc true //Requires arduino Mega

                          //Custom board will use Serial1 (19 and 18)
#define gpsSerial Serial1 //Which Serial to use for the GPS (You could also change to software serial)
#define gpsBaud 9600

boolean DST = false; //Set DST (Can be changed with "dst" via Serial
const int utcOffset = -5; //Timezone offset from UTC


const int times = 3; //How many timers?

int ledOnTimes [5] [2]{ //Times to turn on (24 hour)
  {9,30},
  {12,01},
  {17,00}
};
int ledOffTimes [5] [2]{ //Times to turn off (24 hour)
  {12,00},
  {16,59},
  {19,00}
};


//Colors (0-255)
//Red Grn Blu Wht Pwr

// Colors for timers       
int ledCo [5] [5] {
  {255,255,200,255,45},
  {255,255,200,255,70},
  {255,125,19 ,50 ,40}
};

#include "configPlus.h"
