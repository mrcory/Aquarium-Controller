/*


void displayTemp(_x,_y) {
  display.print("Temp ");
}

void activeDisplay() {
  showTemp(0,0);
}



display.print("This is a test.");
*/ 

//Setup TFT
void screenSetup() { 
  display.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  analogWrite(tft_pin,tft_brightness);
  display.setRotation(3);
  display.fillScreen(ST77XX_BLACK); //Initial clear screen
}

void screenReset(int _X, int _Y, float _SIZE) {
  //display.setTextWrap(false);
  //display.fillScreen(ST77XX_BLACK);
  display.setCursor(_X,_Y);
  //display.setTextColor(ST77XX_RED);
  display.setTextSize(_SIZE);
}



void activeDisplay() {
  if (timer(1000,4)) { //Set the refresh rate
  display.setTextColor(ST7735_WHITE, ST7735_BLACK); //So you don't need to clear the screen
  
  showTemp(0,0,1.5);
  showTime(0,24,1.5);

  showHiLo(97,0,0.5);
  ledStatus(0,39);

  #if tempWarnEnable //If tempurature warning is enabled draw a warning icon.
    warnIcon(97,13);
  #endif

  screenReset(0,100,1);
  display.print("LED Status: ");
  if (ledState == 1) { 
    display.print("ON "); //needs to be 3 characters long to clear the screen
  } else {
    display.print("OFF");
  }

  
  }
}
