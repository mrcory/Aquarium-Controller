#define colon ':'
 
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

void drawArrow(int _X,int _Y) {
  display.drawLine(_X,_Y,_X+10,_Y,WHITE); //Arrow Body
  display.drawLine(_X+10,_Y,_X+5,_Y-3,WHITE); //Arrow Point 1
  display.drawLine(_X+10,_Y,_X+5,_Y+3,WHITE); //Arrow Point 2
}

void displayUpdate() { //Update info display

  display.clearDisplay(); //Clean the Screen
  display.setCursor(0,0); //Set cursor location
  display.setTextSize(1);


  if (screenPage == 1) { //Screen 1 display
    if (tempEnabled) { //Add Temperature to Display
      //Update temperature display
      display.setTextSize(1);
      display.println(tempUnit); //Display the current temp unit
      if (tNeg == 1) {
        display.print(F("-")); //If temp negative add a minus sign
      }
      display.setCursor(8, 0); //Set cursor position
      display.setTextSize(3); //Make it large
      if (temp < 100) {
        display.print(temp,1); //Display temp with 1 decimal place
      } else {
        display.print("!Err");
      }

      display.setTextSize(1); //Reset cursor size for safety
      display.setCursor(97,0); //Set cursor position
      display.print(tempHi,1); //Display tempHi with 1 decimal place
      display.setCursor(97,8); //Set cursor position
      display.print(tempLo,1); //Display tempLo with 1 decimal place

      if (tempWarn == F("Hi") || tempWarn == F("Lo")) {
        display.setCursor(80,32);
        display.print(F("!Temp "));
        display.print(tempWarn);
      }
    }

    //Display Time on screen
    display.setTextSize(1);
    display.setCursor(80, 24);
    display.print(hour());
    display.print(colon);
    display.print(minute());
    display.print(colon);
    display.print(second());

    ledStatus(0,42); //Show LED status bars

if (enableTimer) {
    //Display on and off times
    display.setCursor(0, 24);
    display.setTextSize(1);
    display.print(F("On : ")); display.print(timeOn[0]); display.print(colon); display.print(timeOn[1]); display.print(colon); display.println(timeOn[2]);
    display.print(F("Off: ")); display.print(timeOff[0]); display.print(colon); display.print(timeOff[1]); display.print(colon); display.print(timeOff[2]);
  }
}


  if (screenPage == 0) {
    display.setTextSize(1);
    display.println();
    display.print(hour());
    display.print(colon);
    display.print(minute());
    display.print(colon);
    display.println(second());
    display.print(F("Power State: "));
    display.print(ledState);
    display.println(" ");
    display.print(F("Version: "));
    display.println(ver);
    if (EEPROM.read(0) == 1) { //If position 0 is 1 then there is a saved config
      display.println(F("Config Saved"));
    }

    display.setCursor(0, 44);
    display.print(F("RGBW Aquarium Controller by: Cory McGahee"));

  }

  if (screenPage == 2) {
    display.setCursor(0, 0);
    display.setTextSize(3);
    if (ledState == 1) {
      display.print(F("LED ON"));
    } else {
      display.print(F("LED OFF"));
    }
  ledStatus(0,42); //Show LED status bars
  }


  display.display(); //Put the stuff on the display


}
