//Contains functions for display
#include "ui.h"

bool screenFirstRun = true; //Flag for first run
bool oldWarn = false;

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

const unsigned char blynk_small [] PROGMEM = {
  // 'blynk_small, 30x30px
  0x18, 0x02, 0x00, 0xc0, 0x0c, 0x07, 0x01, 0x80, 0x06, 0x07, 0x03, 0x00, 0x03, 0x02, 0x06, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x7f, 0xf8, 0x00, 
  0x00, 0x60, 0x78, 0x00, 0x00, 0x60, 0x38, 0x00, 0x00, 0x60, 0x18, 0x00, 0x00, 0x60, 0x38, 0x00, 
  0x00, 0x60, 0x70, 0x00, 0x38, 0x7f, 0xe0, 0xe0, 0xfe, 0x7f, 0xe3, 0xf8, 0x38, 0x7f, 0xf0, 0xe0, 
  0x00, 0x60, 0x78, 0x00, 0x00, 0x60, 0x3c, 0x00, 0x00, 0x60, 0x1c, 0x00, 0x00, 0x60, 0x0c, 0x00, 
  0x00, 0x60, 0x1c, 0x00, 0x00, 0x60, 0x3c, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0x7f, 0xf8, 0x00, 
  0x00, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x02, 0x03, 0x00, 0x0c, 0x07, 0x01, 0x80, 
  0x18, 0x07, 0x00, 0xc0, 0x30, 0x02, 0x00, 0x60
};


//------New Bitmaps
const unsigned char waterMap [] PROGMEM = {
  // 'water, 30x15px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x0c, 0x07, 0xfe, 0x00, 0x1c, 
  0x1e, 0x0f, 0x00, 0x70, 0x38, 0x07, 0xc0, 0xe0, 0xf0, 0x01, 0xf7, 0xc0, 0xe0, 0x00, 0x7f, 0x00, 
  0x80, 0xf0, 0x3e, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x0c, 0x1f, 0xff, 0x00, 0x3c, 
  0x7f, 0xff, 0x80, 0x7c, 0xff, 0xff, 0xf1, 0xfc, 0xff, 0xff, 0xff, 0xfc
};

const unsigned char downMap [] PROGMEM = {
  // 'down, 30x15px
  0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 
  0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 
  0x03, 0xc7, 0x8f, 0x00, 0x01, 0xe7, 0x9e, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xf8, 0x00, 
  0x00, 0x3f, 0xf0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x07, 0x80, 0x00
};

const unsigned char upMap [] PROGMEM = {
  // 'up, 30x15px
  0x00, 0x07, 0x80, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x7f, 0xf8, 0x00, 
  0x00, 0xff, 0xfc, 0x00, 0x01, 0xe7, 0x9e, 0x00, 0x03, 0xc7, 0x8f, 0x00, 0x00, 0x07, 0x80, 0x00, 
  0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 
  0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00
};

const unsigned char autoMap [] PROGMEM = {
  // 'auto, 30x15px
  0x00, 0x07, 0x80, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x1c, 0xe0, 0x00, 
  0x00, 0x1c, 0xe0, 0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 0x18, 0x70, 0x00, 0x00, 0x38, 0x70, 0x00, 
  0x00, 0x38, 0x70, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x7f, 0xf8, 0x00, 
  0x00, 0x70, 0x38, 0x00, 0x00, 0xe0, 0x1c, 0x00, 0x00, 0xe0, 0x1c, 0x00
};

const unsigned char blankMap [] PROGMEM = {
  // 'auto, 30x15px
  0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 
  0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 
  0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 
  0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc
};

void blynkLogo(int _x,int _y,uint16_t _color) {
  display.drawBitmap(_x,_y,blynk_small,30,30,_color);
}

/* Just keeping for reference
void waterBitmapDisplay(int _x, int _y,unsigned long _frameDelay, uint16_t _color1, uint16_t _color2) { //Test for animated bitmap
  static unsigned long timer;
  static int frame = 0;
  static bool resetTime = true;

  if (resetTime) { //Set time to millis()
    timer = millis();
    resetTime = false;
  }

  if (millis() - timer >= _frameDelay) {
    if (frame == 0) {Serial.print("[DEBUG] ");
      display.drawBitmap(_x,_y,waterBitmap,30,30,_color1);
      timer = millis();
      frame = 1;
    } else {
    if (frame == 1) {Serial.print("[DEBUG1] ");
      display.drawBitmap(_x,_y,waterBitmap,30,30,_color2); 
      timer = millis();
      frame = 0;
    }
    }
  }
  
}
*/


void showTime(int _posX,int _posY, float _size) {

  static byte myHour;
  static byte myMinute;
  
  if (!_size) { _size = 1;};
    if (screenFirstRun == true) { //First run only
      display.drawBitmap(_posX,_posY,clockBitmap,9,9,ST77XX_WHITE); //Draw a clock icon that is 9x9
    }
    
    display.setTextSize(_size);
    display.setCursor(_posX+11,_posY+2); //Write the time to the scren with an offset for the clock icon

    myHour = hour();
    if (myHour <10) {display.print(F("0"));}
    display.print(myHour);
    display.print(F(":"));
    myMinute = minute();
    if (myMinute <10) {display.print(F("0"));}
    display.print(myMinute);

}

void showHiLo(int _posX,int _posY, float _size) { //97,0
  display.setTextSize(_size); //Reset cursor size for safety
  display.setCursor(_posX,_posY); //Set cursor position
  display.print(F("High: "));
  display.print(tempHi,1); //Display tempHi with 1 decimal place
  display.setCursor(_posX,_posY+8); //Set cursor position
  display.print(F("Low : "));
  display.print(tempLo,1); //Display tempLo with 1 decimal place
        
}

void showTemp(int _posX,int _posY, float _size) {
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
  display.drawLine(locX, locY, locX + width, locY, progressEdge); //Draw outline of progress bar
  display.drawLine(locX, locY + height, locX + width, locY + height, progressEdge); //Draw lower outline of progress bar
  
    for (int i = 1; i < height; i++) { //Draw body of progress bar
      
      
      if (locX - (locX + aLocX) < 0) {
        display.drawLine(locX + aLocX, locY + i, locX + width, locY + i, backGround); //Fill rest of bar in background color
      }

      display.drawLine(locX, locY + i, locX + aLocX, locY + i, progressFill); //Fill visible bar
    }

}

void ledStatus(int _X, int _Y, uint16_t _color, uint16_t _back) { //Show LED value bars <location X, location Y>
  display.setTextSize(1);
  display.drawChar(_X, _Y, 'R', _color, _back, 1); //Bar label
  display.setCursor(_X+8, _Y); display.print(ledC[0]); //Display value digits
  drawHBar(_X,_Y + 8, 3, 25, map(ledC[0], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+30,_Y, 'G', _color, _back, 1); //Bar label
  display.setCursor(_X+38, _Y); display.print(ledC[1]); //Display value digits
  drawHBar(_X+30,_Y + 8, 3, 25, map(ledC[1], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+60,_Y, 'B', _color, _back, 1); //Bar label
  display.setCursor(_X+68,_Y); display.print(ledC[2]); //Display value digits
  drawHBar(_X+60,_Y+ 8, 3, 25, map(ledC[2], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+90,_Y, 'W', _color, _back, 1); //Bar label
  display.setCursor(_X+98,_Y); display.print(ledC[3]); //Display value digits
  drawHBar(_X+90,_Y + 8, 3, 25, map(ledC[3], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(0,_Y + 15, 'P', _color, _back, 1);
  drawHBar(_X+9,_Y + 18, 3, 50, map(ledP, 0, 255, 0, 100));

  display.drawChar(_X+65,_Y + 15, 'B', _color, _back, 1);
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
    
    if (tempWarn == true && tempWarn != oldWarn) {
      display.drawBitmap(_posX,_posY,warnBitmap,9,9,warnColor);
    } else {
      if (tempWarn == false && tempWarn != oldWarn) {
        display.drawBitmap(_posX,_posY,warnBitmap,9,9,backGround);
    }
    }

    oldWarn = tempWarn;
  }
#endif

#if waterFillEnable
  void drawIcon() {
    static byte lastDrawn = 0;
    static bool drawn = false;

    if (waterStage == 1 && lastDrawn != 1) {
      display.drawBitmap(90,90,blankMap,30,15,backGround);
      display.drawBitmap(90,90,downMap,30,15,iconColor);
      lastDrawn = 1;
      drawn = true;
    }

    if (waterStage == 2 && lastDrawn != 2) {
      display.drawBitmap(90,90,blankMap,30,15,backGround);
      display.drawBitmap(90,90,upMap,30,15,iconColor);
      lastDrawn = 2;
      drawn = true;
    }
    
    if (drawn == true && waterStage == 0) { //Clear the icon area
      display.drawBitmap(90,90,blankMap,30,15,backGround);
      drawn = false;
      lastDrawn = 0;

      if (waterMode == 1) {
        display.drawBitmap(90,90,autoMap,30,15,iconColor);
      }
    }
    

    
  }


#endif
