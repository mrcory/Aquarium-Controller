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
  static bool screenFirstRun = true; //Flag for first run
  static bool flipFlop = true; //ledStatus will update every other refresh.
  
  if (fpsControl(4000)) { //Set the refresh rate in milliseconds
  display.setTextColor(ST7735_WHITE, ST7735_BLACK); //So you don't need to clear the screen
  
  showTemp(0,0,1.5);
  showTime(0,24,1.5);

  showHiLo(97,0,0.5);

  
  if (flipFlop == true) {
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

  
  }
}
