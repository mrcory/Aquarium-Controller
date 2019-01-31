//Setup TFT

void screenSetup() { 
  display.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  analogWrite(tft_pin,tft_brightness);
  display.setRotation(tftRotation);
  display.fillScreen(backGround); //Initial clear screen
}

void screenReset(int _X, int _Y, float _SIZE) {
  display.setCursor(_X,_Y);
  display.setTextSize(_SIZE);
}



void activeDisplay() {
  
  static bool flipFlop = true; //ledStatus will update every other refresh.
  
  if (fpsControl(2000)) { //Set the refresh rate in milliseconds
  display.setTextColor(text, backGround); //So you don't need to clear the screen


//---Flip Frame
  if (flipFlop == false || screenFirstRun == true) { //Updates odd times
    showTemp(0,0,1.5);
    showTime(0,24,1.5);
    showHiLo(97,0,0.5);

    flipFlop = !flipFlop;
  }

//---Flop Frame
  if (flipFlop == true) { //Updates even times
    ledStatus(0,39,text,backGround);

  #if tempWarnEnable //If temperature warning is enabled draw a warning icon.
    warnIcon(97,18);
  #endif

  #if waterFillEnable
    if (waterOn == true) {
      display.drawBitmap(90,90,upMap,30,15,ST7735_WHITE);
    }  

    if (waterDrain == true) {
      display.drawBitmap(90,90,downMap,30,15,ST7735_WHITE);
    }
  #endif
    
    flipFlop = !flipFlop;
  }

  
  


  
//---First run only
if (screenFirstRun == true) {
  screenReset(0,100,1);

  #if waterFillEnable //Draw some graphics
    display.drawBitmap(90,105,waterMap,30,15,ST7735_WHITE); //Draw a water icon. Will display arrow above when draing or filling
  #endif
  
  screenFirstRun = false;
}

#if wifiEnable
  static bool oldBlynk = false;
  if (Blynk.connected() == true && oldBlynk == false) {
    blynkLogo(130,90,0x2632);
    oldBlynk = true;
    } else {
  if (Blynk.connected() == false && oldBlynk == true) {
    blynkLogo(130,90,ST77XX_BLACK);
    oldBlynk = false;
  }
  }
#endif
  
  }
  //if (drain == true) {
    //waterBitmapDisplay(90,90,1250,0x5F82,ST7735_WHITE); //Animated test (Not using)
  //}
}
