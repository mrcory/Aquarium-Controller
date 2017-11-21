/* Commands for the sketch
 *  You can call these via Serial
 *  led <val> <val2> | <val> 0=Red 1=Green 2=Blue 3=White 4=Brightness <val2> 0-255 (Set individually)
 *  led <val> <val2> <val3> <val4> <val5> | <val>Red <val2>Green <val3>Blue <val4>Brightness [0-255] (Set all at once)
 *  ledpower | Turn leds on and off
 *  ledpowernow | Turn leds on and off instantly
 *  screen <val> | Change screen display
 */

void colorSet(int arg_cnt, char **args) {
  if (arg_cnt >= 7) {
    ledC[0] = cmdStr2Num(args[1], 10);
    ledC[1] = cmdStr2Num(args[2], 10);
    ledC[2] = cmdStr2Num(args[3], 10);
    ledC[3] = cmdStr2Num(args[4], 10);
    ledP = cmdStr2Num(args[5], 10);
    ledState = cmdStr2Num(args[6], 10);
  }
}

void ledPower() {
  int oldPage = screenPage; //Store old page location
  if (ledState == 0) {ledState = 1;} else {ledState = 0;} //Chang between on and off
  ledUpdate = 1; //There has been a change, update analogWrite
  screenPage = 2; //Change page to "LED ON(OFF)"
  displayUpdate(); Alarm.delay(1000); //Update and display for 1 second
  screenPage = oldPage; //Restore old page location
}

void ledPowerNow() { //Instant on/off
  if (ledState == 1) {ledP = 0;} //Changing to off, tun power to 0
  if (ledState == 0) {ledP = 255;} //Changint to on, turn power to 255
  ledPower(); //Runs regular ledPower() command (We are just skipping the fade)
}

void colorChange(int colorSet[5]) {
  for (int i=0;i<5;i++){
    ledC[i] = colorSet[i];
  }
  ledUpdate = 1;
}

void screenChange(int arg_cnt, char **args) {
  screenPage = cmdStr2Num(args[1],10);
}

//Timer led finctions | Set state correctly to run ledPower() [If state has been flipped for some reason]
//Check if timer is enabled, if not make no change
void timerOn() { if (ledState == 0 && enableTimer) {ledPower();ledState = 1;Serial.println("Turn On");}}
void timerOff() { if (ledState == 1 && enableTimer) {ledPower();ledState = 0;Serial.println("Turn Off");}}

//Serial command "led"
void ledChange(int arg_cnt, char **args) { //First argument will me the command name 
  if (arg_cnt == 3) {ledC[cmdStr2Num(args[1],10)] = cmdStr2Num(args[2],10);} //If 3 arguments, adjust single led channel
  if (arg_cnt >= 6) {for(int i = 0; i < 5; i++) {ledC[i] = cmdStr2Num(args[i+1],10);}}  //If 6 arguments adjust all channels and brightness
  ledUpdate = 1;
}



void configSave() { //Save config
 EEPROM.write(0,1);
 int i=5;
 EEPROM.put(i,ledC);
 i += sizeof(ledC);
 EEPROM.put(i,timeOn);
 i += sizeof(timeOn);
 EEPROM.put(i,timeOff);
 i += sizeof(timeOff);
 EEPROM.put(i,DST);
 i += sizeof(DST);
 EEPROM.put(i,enableTimer);
 i += sizeof(enableTimer);
 EEPROM.put(i,fadeTime);
 i += sizeof(fadeTime);
 EEPROM.put(i,tempUnit);
 i += sizeof(tempUnit);
 Serial.print("Config Saved");
 Serial.print(" Size: ");
 Serial.println(i);
}

void configLoad() { //Load config
 int i = 5;
 EEPROM.get(i,ledC);
 i += sizeof(ledC);
 EEPROM.get(i,timeOn);
 i += sizeof(timeOn);
 EEPROM.get(i,timeOff);
 i += sizeof(timeOff);
 EEPROM.get(i,DST);
 i += sizeof(DST);
 EEPROM.get(i,enableTimer);
 i += sizeof(enableTimer);
 EEPROM.get(i,fadeTime);
 i += sizeof(fadeTime);
 EEPROM.get(i,tempUnit);
 i += sizeof(tempUnit);
 Serial.print("Config Loaded");
 Serial.print(" Size: ");
 Serial.println(i);
}

void configClear() { //Set 0 to 0 so config will not autoload (Can stil be loaded manually
    EEPROM.write(0,0);
    Serial.println("Config Cleared");
  }


