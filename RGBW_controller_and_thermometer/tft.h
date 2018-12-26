//Setup TFT

void screenSetup() { 
  display.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  analogWrite(tft_pin,tft_brightness);
  display.setRotation(tftRotation);
  display.fillScreen(ST77XX_BLACK); //Initial clear screen
}

void screenReset(int _X, int _Y, float _SIZE) {
  display.setCursor(_X,_Y);
  display.setTextSize(_SIZE);
}



void activeDisplay() {
  static bool flipFlop = true; //ledStatus will update every other refresh.
  
  if (fpsControl(2000)) { //Set the refresh rate in milliseconds
  display.setTextColor(ST7735_WHITE, ST7735_BLACK); //So you don't need to clear the screen

  if (flipFlop == false || screenFirstRun == true) { //Updates odd times
    showTemp(0,0,1.5);
    showTime(0,24,1.5);

    showHiLo(97,0,0.5);
  }
  
  if (flipFlop == true) { //Updates even times
    ledStatus(0,39);
    
    screenReset(72,100,1);
    
    if (ledState == 1) { 
      display.print(F("ON ")); //needs to be 3 characters long to clear the screen
        } else {
      display.print(F("OFF"));
      }
  
    flipFlop = !flipFlop;
  }
  
  #if tempWarnEnable //If tempurature warning is enabled draw a warning icon.
    warnIcon(97,18);
  #endif

  
  
  if (screenFirstRun == true) {
    screenReset(0,100,1);
    display.print(F("LED Status: "));
    screenFirstRun = false;
  }

#if wifiEnable
  static bool oldBlynk = false;
  if (Blynk.connected() == true && oldBlynk == false) {
    blynkLogo(100,60,"0x2632");
    oldBlynk = true;
    } else {
  if (Blynk.connected() == false && oldBlynk == true) {
    blynkLogo(100,60,"0x0000");
    oldBlynk = false;
  }
  }
#endif
  
  }
}
