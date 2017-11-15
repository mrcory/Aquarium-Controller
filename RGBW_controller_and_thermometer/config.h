/*
   Variables for configureing various things.
*/

//Temperature Settings
boolean tempEnabled = true;
String tempUnit = "F"; //What unit do you want? (C or F)

//Pin Connections 
const int ledPinR = 2; //Red 
const int ledPinG = 4; //Green
const int ledPinB = 6; //Blue
const int ledPinW = 8; //White channel
const int tempPin = 10; //DS18B20 pin
const int displayAddress = 0x3c; //Display i2c address (Woking with my ebay oled)


//Colors (0-255) Set the initial color.
int ledC[5] = {255,255,255,255,255}; //Red, Green, Blue, White, Target Brightness (All vals 0-255)

//Various Configs
float fadeStep = 5; //Increase/Decrease per step
const int ledPMin = 0; //Minimum led power output 0-255
const int tempTime = 3; //Temp update interval in seconds
int fadeTime = 10; //Fade time in minutes
boolean enableTimer = true; //Disable or enable timer

//Light on/off times
int timeOn[3] = {8,30,0}; //Set time to turn on (24 hour time) <hour, minute, second>
int timeOff[3] = {22,1,30}; //Set time off (24 hour time) <hour, minute, second>
