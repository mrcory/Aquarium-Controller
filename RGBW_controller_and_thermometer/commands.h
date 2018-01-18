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
  byte oldPage = screenPage; //Store old page location
  if (ledState == 0) {ledState = 1; oldState = true;} else {ledState = 0; oldState = false;} //Change between on and off
  ledUpdate = 1; //There has been a change, update analogWrite
  screenPage = 2; //Change page to "LED ON(OFF)"
  displayUpdate(); delay(500); //Update and display for 1 second
  screenPage = oldPage; //Restore old page location
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
    if (arg_cnt >= 6) {for(byte i = 0; i < 5; i++) {ledC[i] = cmdStr2Num(args[i+1],10);}}  //If 6 arguments adjust all channels and brightness
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
 Serial.print(F("Config Loaded Size: "));
 Serial.println(i);
}

void configClear() { //Set 0 to 0 so config will not autoload (Can stil be loaded manually
    EEPROM.write(0,0);
    Serial.println(F("Config Cleared"));
  }

//-------------------------------------------------
void goRight() {
  arrowL++;
}

void goLeft() {
  arrowL--;
}

int countData[2] = {0};

//Cal
int millisCount(byte _mode, byte _id) { //_mode: 0-Start 1-Stop | _id Identity number 1-3 (allow more by editing the length of millisCountData
  int _count;
  if (_mode == 0) {
    countData[_id]= millis();
    return 0;
  }

  if (_mode == 1) {
    _count = millis() - countData[_id];
    return _count;
  }

}


void timerAdd(byte _timer) {
  
      for (byte a=0;a<5;a++) //Save color and brightness setting from current setting
        {ledCo[_timer][a] = ledC[a];
      }
}



