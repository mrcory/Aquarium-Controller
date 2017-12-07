//Contains functions for display

#define colon ':' //Saving a little space

//Create array to draw an arrow from
const int UP [5] [5] {
  {0,0,1,0,0},
  {0,1,1,1,0},
  {1,1,1,1,1},
  {0,0,1,0,0},
  {0,0,1,0,0}
};

const int DOWN [5] [5] {
  {0,0,1,0,0},
  {0,0,1,0,0},
  {1,1,1,1,1},
  {0,1,1,1,0},
  {0,0,1,0,0}
};

const int RIGHT [5] [5] {
  {0,0,1,0,0},
  {0,0,1,1,0},
  {1,1,1,1,1},
  {0,0,1,1,0},
  {0,0,1,0,0}
};

const int LEFT [5] [5] {
  {0,0,1,0,0},
  {0,1,1,0,0},
  {1,1,1,1,1},
  {0,1,1,0,0},
  {0,0,1,0,0}
};

void showTime(int _posX,int _posY, int _size) {
    display.setTextSize(1);
    display.setCursor(_posX,_posY); //80,24
    display.print(hour());
    display.print(colon);
    display.print(minute());
    display.print(colon);
    display.print(second());
}

void showHiLo(int _posX,int _posY) { //97,0
  display.setTextSize(1); //Reset cursor size for safety
  display.setCursor(_posX,_posY); //Set cursor position
  display.print(tempHi,1); //Display tempHi with 1 decimal place
  display.setCursor(_posX,_posY+8); //Set cursor position
  display.print(tempLo,1); //Display tempLo with 1 decimal place
        
}

void showTemp(int _posX,int _posY) { //0,0
      //Update temperature display
      display.setCursor(_posX,_posY);
      display.setTextSize(1);
      display.println(tempUnit); //Display the current temp unit
      if (tNeg == 1) {
        display.print(F("-")); //If temp negative add a minus sign
      }
      display.setCursor(_posX+8,_posY); //Set cursor position
      display.setTextSize(3); //Make it large
      if (temp < 100) {
        display.print(temp,1); //Display temp with 1 decimal place
      } else {
        display.print(F("!Err"));
      }
}

void drawArrowH(int _X,int _Y) {
  display.drawLine(_X,_Y,_X+8,_Y,WHITE); //Arrow Body
  display.drawLine(_X+10,_Y,_X+4,_Y-3,WHITE); //Arrow Point 1
  display.drawLine(_X+10,_Y,_X+4,_Y+3,WHITE); //Arrow Point 2
}

void drawArrow(int _X,int _Y,int _direction[5][5]) { //Draw an arrow from an array. X,Y,(DOWN,UP,RIGHT,LEFT)
  for (int y=0;y<=5;y++) {
    for (int x=0;x<=5;x++) {
      if (_direction[x][y] == 1) {
        display.drawPixel(_X+x,_Y+y,WHITE);
      }
    }
  }
}


void drawHBar(char locX, char locY, char height, char width, char percent) { //Draw a progrss bar
  int aLocX = map(percent, 1, 100, 1, width);
  display.drawLine(locX, locY, locX + width, locY, WHITE); //Draw outline of progress bar
  display.drawLine(locX, locY + height, locX + width, locY + height, WHITE); //Draw lower outline of progress bar

  if (locX - (locX + aLocX > 1) ) { //If value is 0 then don't fill the bar
    for (int i = 0; i < height; i++) { //Draw body of progress bar
      display.drawLine(locX, locY + i, locX + aLocX, locY + i, WHITE);
    }
  }

}

void ledStatus(char _X, char _Y) { //Show LED value bars <location X, location Y>
  display.setTextSize(1);
  display.drawChar(_X, _Y, 'R', WHITE, BLACK, 1); //Bar label
  display.setCursor(_X+8, _Y); display.print(ledC[0]); //Display value digits
  drawHBar(_X,_Y + 8, 3, 25, map(ledC[0], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+30,_Y, 'G', WHITE, BLACK, 1); //Bar label
  display.setCursor(_X+38, _Y); display.print(ledC[1]); //Display value digits
  drawHBar(_X+30,_Y + 8, 3, 25, map(ledC[1], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+60,_Y, 'B', WHITE, BLACK, 1); //Bar label
  display.setCursor(_X+68,_Y); display.print(ledC[2]); //Display value digits
  drawHBar(_X+60,_Y+ 8, 3, 25, map(ledC[2], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(_X+90,_Y, 'W', WHITE, BLACK, 1); //Bar label
  display.setCursor(_X+98,_Y); display.print(ledC[3]); //Display value digits
  drawHBar(_X+90,_Y + 8, 3, 25, map(ledC[3], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(0,_Y + 15, 'P', WHITE, BLACK, 1);
  drawHBar(_X+9,_Y + 18, 3, 51, map(ledP, 0, 255, 0, 100));

  display.drawChar(_X+65,_Y + 15, 'B', WHITE, BLACK, 1);
  drawHBar(_X+74,_Y + 18, 3, 51, map(ledC[4], 0, 255, 0, 100));
}
