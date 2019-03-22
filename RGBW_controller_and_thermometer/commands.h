/* Commands for the sketch
    You can call these via Serial
    led <val> <val2> | <val> 0=Red 1=Green 2=Blue 3=White 4=Brightness <val2> 0-255 (Set individually)
    led <val> <val2> <val3> <val4> <val5> | <val>Red <val2>Green <val3>Blue <val4>Brightness [0-255] (Set all at once)
    ledpower | Turn leds on and off
    ledpowernow | Turn leds on and off instantly
    screen <val> | Change screen display - depreciated
    dst | Enable/Disable DST offset
    save | Save config
    load | Load config
    configclear | Clear config
    temprst | Reset temperature range
    ------------ Wifi Dependent
    ssid <ssid> | Set your SSID
    pass <password> | Set the password for wifi
    token <Blynk Token> | Set the Blynk server token
*/


//Thanks to https://circuits4you.com/2018/10/16/arduino-reading-and-writing-string-to-eeprom/

String read_String(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}

void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
}

void ledPower() {
  if (ledState == 0) {
    ledState = 1;  //Change between on and off
    oldState = true;
  } else {
    ledState = 0;
    oldState = false;
  }
  ledUpdate = 1; //There has been a change, update analogWrite
#if screenEnable
  int oldPage = screenPage; //Store old page location
  screenPage = 2; //Change page to "LED ON(OFF)"
#if screenOLED && screenEnable
  //displayUpdate(); delay(500); //Update and display
#endif
  screenPage = oldPage; //Restore old page location
#endif
}


void ledPowerNow() { //Instant on/off
  if (ledState == 1) {
    ledP = 0; //Changing to off, tun power to 0
  }
  if (ledState == 0) {
    ledP = 255; //Changing to on, turn power to 255
  }
  ledPower(); //Runs regular ledPower() command (We are just skipping the fade)
}

#if serialCommands
void screenChange(int arg_cnt, char **args) {
  screenPage = cmdStr2Num(args[1], 10);
}

//Serial command "led"
void ledChange(int arg_cnt, char **args) { //First argument will me the command name
  if (arg_cnt == 3) {
    ledC[cmdStr2Num(args[1], 10)] = cmdStr2Num(args[2], 10); //If 3 arguments, adjust single led channel
  }
  if (arg_cnt >= 6) {
    for (int i = 0; i < 5; i++) {
      ledC[i] = cmdStr2Num(args[i + 1], 10); //If 6 arguments adjust all channels and brightness
    }
  }
  ledUpdate = 1;
}
#endif

void configSave() { //Save config
  EEPROM.write(0, 1); //First bit is used as a flag for autoloading
  int i = 5; //Offset by 5
  EEPROM.put(i, ledC);
  i += sizeof(ledC);
  EEPROM.put(i, DST);
  i += sizeof(DST);
  EEPROM.put(i, enableTimer);
  i += sizeof(enableTimer);
  EEPROM.put(i, fadeTime);
  i += sizeof(fadeTime);
  EEPROM.put(i, tempUnit);
  i += sizeof(tempUnit);
  EEPROM.put(i, ledCo);
  i += sizeof(ledCo);
  //Set offset manually
  i = 90; //Manual offset
  writeString(i,mySSID);
  i+= 75;
  writeString(i,wifiPassword);
  i+= 50;
  writeString(i,blynkToken);
  i+= 100;
  Serial.print(F("[CONFIG] Saved | "));
  Serial.print(i);
  Serial.print(F(" bytes"));
}

void configLoad() { //Load config
  int i = 5; //Offset by 5
  EEPROM.get(i, ledC);
  i += sizeof(ledC);
  EEPROM.get(i, DST);
  i += sizeof(DST);
  EEPROM.get(i, enableTimer);
  i += sizeof(enableTimer);
  EEPROM.get(i, fadeTime);
  i += sizeof(fadeTime);
  EEPROM.get(i, tempUnit);
  i += sizeof(tempUnit);
  EEPROM.put(i, ledCo);
  i += sizeof(ledCo);
  //Manually offset
  i = 90;
  mySSID = read_String(i);
  i+= 75;
  wifiPassword = read_String(i);
  i+= 50;
  blynkToken = read_String(i);
  i+= 100;

  Serial.print(F("[Config] Loaded | "));
  Serial.print(i);
  Serial.println(F(" bytes"));
}

void configClear() { //Set 0 to 0 so config will not autoload (Can stil be loaded manually
  EEPROM.write(0, 0);
  Serial.println(F("[Config] Cleared"));
}

void checkConfig() { //Check if we need to load the config at start
  if (EEPROM.read(0) == 1) { //If 0 is 1 the autoload config
    configLoad();
  }
}

//-------------------------------------------------

void lightTimerAdd(int _timer) {

  for (int a = 0; a < 5; a++) //Save color and brightness setting from current setting
  { ledCo[_timer][a] = ledC[a];
  }
}

#if serialCommands



void wifiSSID(int arg_cnt, char **args) {
  Serial.print(F("Old SSID: "));
  Serial.println(mySSID);
  mySSID = String(args[1]);
  Serial.print(F("SSID: ")); Serial.println(mySSID);
  configSave();
}

void wifiPass(int arg_cnt, char **args) {
  Serial.print(F("Old Pass: "));
  Serial.println(wifiPassword);
  wifiPassword = String(args[1]); //Set password
  configSave(); //Save the config
  Serial.print(F("Pass: ")); Serial.println(wifiPassword);
}

void blynkSet(int arg_cnt, char **args) {
  Serial.print(F("Old Token: "));
  Serial.println(blynkToken);
  blynkToken = String(args[1]); //Set Blynk server token
  configSave(); //Save the config
  Serial.print(F("Token: ")); Serial.println(blynkToken);
}

#endif
