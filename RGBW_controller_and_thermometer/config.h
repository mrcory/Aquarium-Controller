/*
   Variables for configureing various things.
*/


//Temperature Settings
char tempUnit = 'F'; //What unit do you want? (C or F)
int tempWarnHi = 82; //High temp warning. (Set with the same unit as above)
int tempWarnLo = 72; //Low temp warning. (Set with the same unit as above)

//Pin Connections 
const byte ledPinR = 2; //Red 
const byte ledPinG = 4; //Green (Pin 4 goes high on start)
const byte ledPinB = 6; //Blue
const byte ledPinW = 8; //White channel
const byte tempPin = 10; //DS18B20 pin
const int displayAddress = 0x3c; //Display i2c address (Woking with my ebay oled)

//Various Configs
const byte ledPMin = 0; //Minimum led power output 0-255
const byte tempTime = 4; //Temp update interval in seconds 0-255
byte fadeTime = 10; //Fade time in minutes 0-255



//Time Keeping. Only one can be true
#define ds3231 false
#define ds1307 false
#define gpsRtc true //Requires arduino Mega

boolean DST = false; //Set DST (Can be changed with "dst" via Serial
const byte utcOffset = -5; //Timezone offset from UTC


const byte times = 3; //How many timers?

byte ledOnTimes [5] [2]{ //Times to turn on (24 hour)
  {9,30},
  {12,01},
  {17,00}
};
byte ledOffTimes [5] [2]{ //Times to turn off (24 hour)
  {12,00},
  {16,59},
  {19,00}
};


//Colors (0-255)
//Red Grn Blu Wht Pwr

// Colors for timers       
byte ledCo [5] [5] {
  {255,255,200,255,75},
  {255,255,200,255,60},
  {255,125,19 ,50 ,50}
};

#include "configPlus.h"

