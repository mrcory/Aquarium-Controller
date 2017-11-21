/*
   Variables for configureing various things.
*/

//Temperature Settings
boolean tempEnabled = true; //Are you using a temp probe?
char tempUnit = 'F'; //What unit do you want? (C or F)
int tempWarnHi = 82; //High temp warning. (Set with the same unit as above)
int tempWarnLo = 72; //Low temp warning. (Set with the same unit as above)


//Pin Connections 
const PROGMEM int ledPinR = 2; //Red 
const PROGMEM int ledPinG = 4; //Green
const PROGMEM int ledPinB = 6; //Blue
const PROGMEM int ledPinW = 8; //White channel
const PROGMEM int tempPin = 11; //DS18B20 pin
const PROGMEM int displayAddress = 0x3c; //Display i2c address (Woking with my ebay oled)


//Colors (0-255) Set the initial color.
int ledC[5] = {255,255,255,255,255}; //Red, Green, Blue, White, Target Brightness (All vals 0-255)

//Various Configs
float fadeStep = 5; //Increase/Decrease per step (Will be properly set based on fadeTime
const PROGMEM int ledPMin = 0; //Minimum led power output 0-255
const PROGMEM int tempTime = 2; //Temp update interval in seconds
int fadeTime = 30; //Fade time in minutes
boolean enableTimer = true; //Disable or enable timer
boolean DST = false; //Set DST (Can be changed with "dst" via Serial

//Light on/off times for display only
int timeOn[3] = {8,30,0}; //Set time to turn on (24 hour time) <hour, minute, second>
int timeOff[3] = {20,0,0}; //Set time off (24 hour time) <hour, minute, second>

//Comment out to disable Serial commands (Save a little space) Good for non-Mega boards
//Also Comment out "#include <Cmd.h>" in the main .ino
#define serialCommands
