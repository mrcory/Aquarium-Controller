//Pin Connections
const int ledPinR = 2;
const int ledPinG = 4;
const int ledPinB = 6;
const int ledPinW = 8; //White channel
const int tempPin = 10; //DS18B20 pin
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

//Light on/off times
int timeOn[3] = {8,30,0}; //Set time to turn on (24 hour time) <hour, minute, second>
int timeOff[3] = {21,30,0}; //Set time off (24 hour time) <hour, minute, second>
