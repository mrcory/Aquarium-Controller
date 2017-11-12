
const int barLocX = 0; //Where to start drawing the bars X
const int barLocY = 42; //Where to start drawing the bars Y




void drawHBar(int locX, int locY, int height, int width, int percent) { //Draw a progrss bar
  int aLocX = map(percent, 1, 100, 1, width);
  display.drawLine(locX, locY, locX + width, locY, WHITE); //Draw outline of progress bar
  display.drawLine(locX, locY + height, locX + width, locY + height, WHITE); //Draw lower outline of progress bar

  if (locX - (locX + aLocX > 1) ) { //If value is 0 then don't fill the bar
    for (int i = 0; i < height; i++) { //Draw body of progress bar
      display.drawLine(locX, locY + i, locX + aLocX, locY + i, WHITE);
    }
  }

}

void ledStatus() { //Show LED value bars
  display.setTextSize(1);
  display.drawChar(0, barLocY, 'R', WHITE, BLACK, 1); //Bar label
  display.setCursor(8, barLocY); display.print(ledC[0]); //Display value digits
  drawHBar(0, barLocY + 8, 3, 25, map(ledC[0], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(30, barLocY, 'G', WHITE, BLACK, 1); //Bar label
  display.setCursor(38, barLocY); display.print(ledC[1]); //Display value digits
  drawHBar(30, barLocY + 8, 3, 25, map(ledC[1], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(60, barLocY, 'B', WHITE, BLACK, 1); //Bar label
  display.setCursor(68, barLocY); display.print(ledC[2]); //Display value digits
  drawHBar(60, barLocY + 8, 3, 25, map(ledC[2], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(90, barLocY, 'W', WHITE, BLACK, 1); //Bar label
  display.setCursor(98, barLocY); display.print(ledC[3]); //Display value digits
  drawHBar(90, barLocY + 8, 3, 25, map(ledC[3], 0, 255, 0, 100)); //Testing progress bar

  display.drawChar(0, barLocY + 15, 'P', WHITE, BLACK, 1);
  drawHBar(9, barLocY + 18, 3, 51, map(ledP, 0, 255, 0, 100));

  display.drawChar(65, barLocY + 15, 'B', WHITE, BLACK, 1);
  drawHBar(74, barLocY + 18, 3, 51, map(ledC[4], 0, 255, 0, 100));
}

void displayUpdate() { //Update info display

  display.clearDisplay(); //Clean the Screen


  if (screenPage == 1) { //Screen 0 display
    if (tempEnabled) { //Add Temperature to Display
      //Update temperature display
      display.setCursor(0, 0); //Set cursor location
      display.setTextSize(1);
      display.println(tempUnit);
      if (tNeg == 1) {
        display.print(" -"); //If temp negative add a minus sign
      }
      display.setCursor(10, 0);
      display.setTextSize(3); //Make it large
      display.println(temp);
    }

    //Display Time on screen
    display.setTextSize(1);
    display.setCursor(80, 24);
    display.print(timeNow.hour());
    display.print(":");
    display.print(timeNow.minute());
    display.print(":");
    display.print(timeNow.second());

    ledStatus(); //Show LED status bars

if (enableTimer) {
    //Display on and off times
    display.setCursor(0, 24);
    display.setTextSize(1);
    display.print("On :  "); display.print(timeOn[0]); display.print(":"); display.print(timeOn[1]); display.print(":"); display.println(timeOn[2]);
    display.print("Off: "); display.print(timeOff[0]); display.print(":"); display.print(timeOff[1]); display.print(":"); display.print(timeOff[2]);
  }
}


  if (screenPage == 0) {
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println();
    display.print(hour());
    display.print(":");
    display.print(minute());
    display.print(":");
    display.println(second());
    display.print("Power State: ");
    display.print(ledState);
    display.println(" ");

    display.setCursor(0, 44);
    display.print("RGBW Aquarium Controller by: Cory McGahee");

  }

  if (screenPage == 2) {
    display.setCursor(0, 0);
    display.setTextSize(3);
    if (ledState == 1) {
      display.print("LED ON");
    }
    if (ledState == 0) {
      display.print("LED OFF");
    }
  ledStatus(); //Show LED status bars
  }

  display.display(); //Put the stuff on the display
}





