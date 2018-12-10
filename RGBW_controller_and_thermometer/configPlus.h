//Config stuff overflow

float fadeStep = 5; //Increase/Decrease per step (Will be properly set based on fadeTime
boolean enableTimer = true; //Disable or enable timer
int crossFade = 5; //Crossfade time in seconds per step

//Enable or disable serial commands
#define serialCommands true //Disable to save sram and flash space

//Enable/disable Temperature
#define tempEnable true

//Enable/disable Screen
#define screenEnable true

//Choose a screen
#define screenOLED false
#define screenTFT true

//TFT Settings
int tft_brightness = 25; //0-255 Controls a pwm pin
int tft_pin = 2; //Reset pin(?)

//OLED Settings
#define oled_width 128
#define oled_height 64


//Enable Menu (Not coded yet)
#define enableMenu false

//Disable or Enable Temperature warning
#define tempWarnEnable false

//Disable or Enable Water Fill
#define waterFillEnable false

#if tempWarnEnable //If above is true, this will be included in the program.
//Add aditional functions to be run when temperature warning has been triggered.
//Maybe a light or a buzzer or a siren
void additionalWarn() {
  //Fill in here
}
#endif

#if waterFillEnable //If water fill is enabled define these
  #define waterPin 0
  #define waterSense 0
  #define waterSense2 0
  #define waterTimeMin 0
  #define waterTimeMax 1000
#endif
