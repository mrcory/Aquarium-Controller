//Config stuff overflow

float fadeStep = 5; //Increase/Decrease per step (Will be properly set based on fadeTime
boolean enableTimer = true; //Disable or enable timer
byte crossFade = 5; //Crossfade time in seconds per step

//Enable or disable serial commands
#define serialCommands true //Disable to save sram and flash space

//Enable/disable Temperature
#define tempEnable true

//Enable/disable Screen
#define screenEnable true

//Enable Menu (Not coded yet)
#define enableMenu false
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

#if enableMenu && screenEnable //Set resistor values for buttons here
  #define _upVal 1002
  #define _downVal 929
  #define _leftVal 860
  #define _rightVal 970
  #define _menuVal 1013
#endif
