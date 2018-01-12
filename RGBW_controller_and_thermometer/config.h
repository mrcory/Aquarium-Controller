/*
   Variables for configureing various things.
*/

//Temperature Settings
//boolean tempEnabled = true; //Are you using a temp probe?
char tempUnit = 'F'; //What unit do you want? (C or F)
int tempWarnHi = 82; //High temp warning. (Set with the same unit as above)
int tempWarnLo = 72; //Low temp warning. (Set with the same unit as above)

//Pin Connections 
const int ledPinR = 2; //Red 
const int ledPinG = 4; //Green (Pin 4 goes high on start)
const int ledPinB = 6; //Blue
const int ledPinW = 8; //White channel
const int tempPin = 10; //DS18B20 pin
const int displayAddress = 0x3c; //Display i2c address (Woking with my ebay oled)

//Various Configs
float fadeStep = 5; //Increase/Decrease per step (Will be properly set based on fadeTime
const int ledPMin = 0; //Minimum led power output 0-255
const int tempTime = 4; //Temp update interval in seconds
int fadeTime = 30; //Fade time in minutes
boolean enableTimer = true; //Disable or enable timer

//Time Keeping. Only one can be true
#define ds3231 false
#define ds1307 false
#define gpsRtc true

boolean DST = false; //Set DST (Can be changed with "dst" via Serial
const int utcOffset = -5; //Timezone offset from UTC


//Enable or disable serial commands
#define serialCommands true

//Enable Menu (Not coded yet)
#define enableMenu true
#define buttonPin A1

//Diable or Enable Temperature warning
#define tempWarnEnable false

#if tempWarnEnable //If above is true, this will be included in the program.
//Add aditional functions to be run when temperature warning has been triggered.
//Maybe a light or a buzzer or a siren
void additionalWarn() {
  //Fill in here
}
#endif

const int times = 2; //How many timers?

int ledOnTimes [times] [2]{ //Times to turn on (24 hour)
  {9,30},
  {13,00}
};
int ledOffTimes [times] [2]{ //Times to turn off (24 hour)
  {12,00},
  {19,00}
};

//Selects the color for each timer
int colorChoice [times] {0,1}; //Which color to use with each timer

//Colors (0-255) Set the initial color.
//Red Grn Blu Wht Pwr
//colorChoice options
int ledCo [2] [5] {
  {255,255,200,255,125},
  {255,125,19 ,50 ,175}
};
