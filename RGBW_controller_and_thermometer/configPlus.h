//Config stuff overflow

float fadeStep = 5; //Increase/Decrease per step (Will be properly set based on fadeTime
boolean enableTimer = true; //Disable or enable timer
int crossFade = 5; //Crossfade time in seconds per step

//Enable or disable serial commands
#define serialCommands false //Disable to save sram and flash space

//Enable/disable Temperature
#define tempEnable true

//Enable/disable Screen
#define screenEnable true

//Enable Menu (Not coded yet)
#define enableMenu false

//Diable or Enable Temperature warning
#define tempWarnEnable false

#if tempWarnEnable //If above is true, this will be included in the program.
//Add aditional functions to be run when temperature warning has been triggered.
//Maybe a light or a buzzer or a siren
void additionalWarn() {
  //Fill in here
}
#endif

//New debug serial contrtol
//true will allow Serial.print() feedback.
#define serial_debug false
