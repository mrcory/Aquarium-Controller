//Contains functions for display

#define colon ':' //Saving a little space


//BITMAPS
const unsigned char clockBitmap [] PROGMEM = {
  // 'clock, 9x9px
  0x08, 0x00, 0x2a, 0x00, 0x49, 0x00, 0x88, 0x80, 0x86, 0x80, 0x80, 0x80, 0x41, 0x00, 0x22, 0x00, 
  0x1c, 0x00
};

const unsigned char warnBitmap [] PROGMEM = {
  // 'warn, 9x9px
  0x1c, 0x00, 0x36, 0x00, 0x63, 0x00, 0x49, 0x00, 0xc9, 0x80, 0x80, 0x80, 0xc9, 0x80, 0x63, 0x00, 
  0x7f, 0x00
};


void showTime(int _posX,int _posY, float _size) {
  if (!_size) { _size = 1;};
    display.drawBitmap(_posX,_posY,clockBitmap,9,9,ST77XX_WHITE); //Draw a clock icon that is 9x9
    display.setTextSize(_size);
    display.setCursor(_posX+11,_posY+2); //Write the time to the scren with an offset for the clock icon
    if (hour() <10) {display.print("0");}
    display.print(hour());
    display.print(colon);
    display.print(minute());
    if (minute() <10) {display.print("0");}
    //display.print(colon);
    //if (second() <10) {display.print("0");}
    //display.print(second());
    display.print(" "); //Cover errant extra 0 that shows up by morning. (Lazy fix)
}

void showHiLo(int _posX,int _posY, float _size) { //97,0
  display.setTextSize(_size); //Reset cursor size for safety
  display.setCursor(_posX,_posY); //Set cursor position
  display.print("High: ");
  display.print(tempHi,1); //Display tempHi with 1 decimal place
  display.setCursor(_posX,_posY+8); //Set cursor position
  display.print("Low : ");
  display.print(tempLo,1); //Display tempLo with 1 decimal place
        
}

void showTemp(int _posX,int _posY, float _size) { //0,0
      //Update temperature display
      display.setCursor(_posX,_posY);
      display.setTextSize(_size);
      display.println(tempUnit); //Display the current temp unit
      if (tNeg == 1) {
        display.print(F("-")); //If temp negative add a minus sign
      } else {
        display.print(F(" "));
      }
      display.setCursor(_posX+8,_posY); //Set cursor position
      display.setTextSize(_size*2); //Make it large
      if (temp < 100) {
        display.print(temp,_size); //Display temp with 1 decimal place
      } else {
        display.print(F("!Err"));
      }
}


void drawHBar(int locX, int locY, int height, int width, int percent) { //Draw a progrss bar
  int aLocX = map(percent, 0, 100, 0, width);
  display.drawLine(locX, locY, locX + width, locY, ST77XX_WHITE); //Draw outline of progress bar
  display.drawLine(locX, locY + height, locX + width, locY + height, ST77XX_WHITE); //Draw lower outline of progress bar
  

  //if (locX - (locX + aLocX > 1) ) { //If value is 0 then don't fill the bar
    for (int i = 1; i < height; i++) { //Draw body of progress bar
      
      
      if (locX - (locX + aLocX) < 0) {
        display.drawLine(locX + aLocX, locY + i, locX + width, locY + i, ST77XX_BLACK); //Fill rest of bar in background color
      }

      display.drawLine(locX, locY + i, locX + aLocX, locY + i, ST77XX_WHITE); //Fill visible bar
    }
  //}

}

void ledStatus(int _X, int _Y) { //Show LED value bars <location X, location Y>
  display.setTextSize(1);
  display.drawChar(_X, _Y, 'R', ST77XX_WHITE, ST77XX_BLACK, 1); //Bar label
  display.setCursor(_X+8, _Y); display.print(ledC[0]); //Display value digits
  drawHBar(_X,_Y + 8, 3, 25, map(ledC[0], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+30,_Y, 'G', ST77XX_WHITE, ST77XX_BLACK, 1); //Bar label
  display.setCursor(_X+38, _Y); display.print(ledC[1]); //Display value digits
  drawHBar(_X+30,_Y + 8, 3, 25, map(ledC[1], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+60,_Y, 'B', ST77XX_WHITE, ST77XX_BLACK, 1); //Bar label
  display.setCursor(_X+68,_Y); display.print(ledC[2]); //Display value digits
  drawHBar(_X+60,_Y+ 8, 3, 25, map(ledC[2], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+90,_Y, 'W', ST77XX_WHITE, ST77XX_BLACK, 1); //Bar label
  display.setCursor(_X+98,_Y); display.print(ledC[3]); //Display value digits
  drawHBar(_X+90,_Y + 8, 3, 25, map(ledC[3], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(0,_Y + 15, 'P', ST77XX_WHITE, ST77XX_BLACK, 1);
  drawHBar(_X+9,_Y + 18, 3, 50, map(ledP, 0, 255, 0, 100));

  display.drawChar(_X+65,_Y + 15, 'B', ST77XX_WHITE, ST77XX_BLACK, 1);
  drawHBar(_X+74,_Y + 18, 3, 50, map(ledC[4], 0, 255, 0, 100));
}

//Refresh rate controller
bool fpsControl(unsigned long _rate) { //Return true after _rate
  if (timer(_rate,4)) {
    return true;
  } else {
    return false;
  }
}

#if tempWarnEnable
  void warnIcon(int _posX,int _posY) {
    if (tempWarn == true) {
      display.drawBitmap(_posX,_posY,warnBitmap,9,9,ST77XX_RED);
    } else {
      display.drawBitmap(_posX,_posY,warnBitmap,9,9,ST77XX_BLACK);
    }
  }
#endif
