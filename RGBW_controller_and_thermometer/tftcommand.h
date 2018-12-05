//Contains functions for display

#define colon ':' //Saving a little space


//Create array to draw an arrow from
#if enableMenu
const int RIGHT [5] [5] {
  {0,0,1,0,0},
  {0,1,1,1,0},
  {1,1,1,1,1},
  {0,0,1,0,0},
  {0,0,1,0,0}
};

const int LEFT [5] [5] {
  {0,0,1,0,0},
  {0,0,1,0,0},
  {1,1,1,1,1},
  {0,1,1,1,0},
  {0,0,1,0,0}
};

const int DOWN [5] [5] {
  {0,0,1,0,0},
  {0,0,1,1,0},
  {1,1,1,1,1},
  {0,0,1,1,0},
  {0,0,1,0,0}
};

const int UP [5] [5] {
  {0,0,1,0,0},
  {0,1,1,0,0},
  {1,1,1,1,1},
  {0,1,1,0,0},
  {0,0,1,0,0}
};

void drawArrowUP(int _X,int _Y) { //Draw an arrow from an array. X,Y,(DOWN,UP,RIGHT,LEFT)
  for (int y=0;y<5;y++) {
    for (int x=0;x<5;x++) {
      if (UP[x][y] == 1) {
        display.drawPixel(_X+x,_Y+y,ST77XX_ST77XX_WHITE);
      }
    }
  }
}

void drawArrowRIGHT(int _X,int _Y) { //Draw an arrow from an array. X,Y,(DOWN,UP,RIGHT,LEFT)
  for (int y=0;y<5;y++) {
    for (int x=0;x<5;x++) {
      if (RIGHT[x][y] == 1) {
        display.drawPixel(_X+x,_Y+y,ST77XX_WHITE);
      }
    }
  }
}

void drawArrowDOWN(int _X,int _Y) { //Draw an arrow from an array. X,Y,(DOWN,UP,RIGHT,LEFT)
  for (int y=0;y<5;y++) {
    for (int x=0;x<5;x++) {
      if (DOWN[x][y] == 1) {
        display.drawPixel(_X+x,_Y+y,ST77XX_WHITE);
      }
    }
  }
}
#endif

void showTime(int _posX,int _posY, float _size) {
  if (!_size) { _size = 1;};
    display.setTextSize(_size);
    display.setCursor(_posX,_posY); //80,24
    if (hour() <10) {display.print("0");}
    display.print(hour());
    display.print(colon);
    display.print(minute());
    if (minute() <10) {display.print("0");}
    display.print(colon);
    if (second() <10) {display.print("0");}
    display.print(second());
}

void showHiLo(int _posX,int _posY, float _size) { //97,0
  display.setTextSize(_size); //Reset cursor size for safety
  display.setCursor(_posX,_posY); //Set cursor position
  display.print("High: ");
  display.print(tempHi,_size); //Display tempHi with 1 decimal place
  display.setCursor(_posX,_posY+8); //Set cursor position
  display.print("Low : ");
  display.print(tempLo,_size); //Display tempLo with 1 decimal place
        
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
        display.drawLine(locX + aLocX, locY + i, locX + width, locY + i, ST77XX_BLUE); //Fill rest of bar in background color
      }

      display.drawLine(locX, locY + i, locX + aLocX, locY + i, ST77XX_WHITE); //Fill visible bar
    }
  //}

}

void ledStatus(int _X, int _Y) { //Show LED value bars <location X, location Y>
  display.setTextSize(1);
  display.drawChar(_X, _Y, 'R', ST77XX_WHITE, ST77XX_BLACK, 1); //Bar label
  display.setCursor(_X+8, _Y); display.print(ledC[0]); //Display value digits
  drawHBar(_X,_Y + 8, 4, 25, map(ledC[0], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+30,_Y, 'G', ST77XX_WHITE, ST77XX_BLACK, 1); //Bar label
  display.setCursor(_X+38, _Y); display.print(ledC[1]); //Display value digits
  drawHBar(_X+30,_Y + 8, 4, 25, map(ledC[1], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+60,_Y, 'B', ST77XX_WHITE, ST77XX_BLACK, 1); //Bar label
  display.setCursor(_X+68,_Y); display.print(ledC[2]); //Display value digits
  drawHBar(_X+60,_Y+ 8, 4, 25, map(ledC[2], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+90,_Y, 'W', ST77XX_WHITE, ST77XX_BLACK, 1); //Bar label
  display.setCursor(_X+98,_Y); display.print(ledC[3]); //Display value digits
  drawHBar(_X+90,_Y + 8, 4, 25, map(ledC[3], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(0,_Y + 15, 'P', ST77XX_WHITE, ST77XX_BLACK, 1);
  drawHBar(_X+9,_Y + 18, 4, 50, map(ledP, 0, 255, 0, 100));

  display.drawChar(_X+65,_Y + 15, 'B', ST77XX_WHITE, ST77XX_BLACK, 1);
  drawHBar(_X+74,_Y + 18, 4, 50, map(ledC[4], 0, 255, 0, 100));
}

//Refresh rate controller
bool fpsControl(int _rate) {
  if (timer(1000/_rate,4)) {
    return true;
  } else {
    return false;
  }
}
