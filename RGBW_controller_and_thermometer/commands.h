/* Commands for the sketch
 *  You can call these via Serial
 *  led <val> <val2> | <val> 0=Red 1=Green 2=Blue 3=White 4=Brightness <val2> 0-255 (Set individually)
 *  led <val> <val2> <val3> <val4> <val5> | <val>Red <val2>Green <val3>Blue <val4>Brightness [0-255] (Set all at once)
 *  ledpower | Turn leds on and off
 *  ledpowernow | Turn leds on and off instantly
 *  screen <val> | Change screen display
 *  dst | Enable/Disable DST offset
 *  save | Save config
 *  load | Load config
 *  configclear | Clear config
 *  temprst | Reset temperature range
 */



void ledPower() {
  if (ledState == 0) {ledState = 1; oldState = true;} else {ledState = 0; oldState = false;} //Change between on and off
  ledUpdate = 1; //There has been a change, update analogWrite
  #if screenEnable
    int oldPage = screenPage; //Store old page location
    screenPage = 2; //Change page to "LED ON(OFF)"
   #if screenOLED 
    activeDisplay(); delay(500); //Update and display for 1 second 
   #endif
    screenPage = oldPage; //Restore old page location
  #endif
}


void ledPowerNow() { //Instant on/off
  if (ledState == 1) {ledP = 0;} //Changing to off, tun power to 0
  if (ledState == 0) {ledP = 255;} //Changing to on, turn power to 255
  ledPower(); //Runs regular ledPower() command (We are just skipping the fade)
}

#if serialCommands
  void screenChange(int arg_cnt, char **args) {
    screenPage = cmdStr2Num(args[1],10);
  }
  
  //Serial command "led"
  void ledChange(int arg_cnt, char **args) { //First argument will me the command name 
    if (arg_cnt == 3) {ledC[cmdStr2Num(args[1],10)] = cmdStr2Num(args[2],10);} //If 3 arguments, adjust single led channel
    if (arg_cnt >= 6) {for(int i = 0; i < 5; i++) {ledC[i] = cmdStr2Num(args[i+1],10);}}  //If 6 arguments adjust all channels and brightness
    ledUpdate = 1;
  }
#endif

void configSave() { //Save config
 EEPROM.write(0,1);
 int i=5;
 EEPROM.put(i,ledC);
 i += sizeof(ledC);
 EEPROM.put(i,DST);
 i += sizeof(DST);
 EEPROM.put(i,enableTimer);
 i += sizeof(enableTimer);
 EEPROM.put(i,fadeTime);
 i += sizeof(fadeTime);
 EEPROM.put(i,tempUnit);
 i += sizeof(tempUnit);
 EEPROM.put(i,ledCo);
 i+= sizeof(ledCo);
 Serial.print(F("Config Saved Size: "));
 Serial.println(i);
}

void configLoad() { //Load config
 int i = 5;
 EEPROM.get(i,ledC);
 i += sizeof(ledC);
 EEPROM.get(i,DST);
 i += sizeof(DST);
 EEPROM.get(i,enableTimer);
 i += sizeof(enableTimer);
 EEPROM.get(i,fadeTime);
 i += sizeof(fadeTime);
 EEPROM.get(i,tempUnit);
 i += sizeof(tempUnit);
 EEPROM.put(i,ledCo);
 i+= sizeof(ledCo);
 Serial.print(F("Config Loaded Size: "));
 Serial.println(i);
}

void configClear() { //Set 0 to 0 so config will not autoload (Can stil be loaded manually
    EEPROM.write(0,0);
    Serial.println(F("Config Cleared"));
  }

//-------------------------------------------------

void lightTimerAdd(int _timer) {
  
      for (int a=0;a<5;a++) //Save color and brightness setting from current setting
        {ledCo[_timer][a] = ledC[a];
      }
}



