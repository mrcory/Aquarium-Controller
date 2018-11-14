
//Setup TFT
void screenSetup1() { 
  display.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  analogWrite(tft_pin,tft_brightness);
  display.setRotation(3);
}

void displayTemp(_x,_y) {
  display.print("Temp ");
}

void activeDisplay() {
  showTemp(0,0);
}

display.setTextWrap(false);
display.fillScreen(ST77XX_BLACK);
display.setCursor(0,30);
display.setTextColor(ST77XX_RED);
display.setTextSize(1);

display.print("This is a test.");
