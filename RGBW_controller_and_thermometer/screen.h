
const int barLocX = 0; //Where to start drawing the bars X
const int barLocY = 42; //Where to start drawing the bars Y
int screenPage = 0; //What page to be displayed on the screen



void drawHBar(int locX,int locY,int height,int width,int percent) { //Draw a progrss bar
  int aLocX = map(percent,1,100,1,width);
  display.drawLine(locX,locY,locX+width,locY,WHITE); //Draw outline of progress bar
  display.drawLine(locX,locY+height,locX+width,locY+height,WHITE); //Draw lower outline of progress bar

  if (locX - (locX + aLocX > 1) ) { //If value is 0 then don't fill the bar
    for(int i = 0; i < height; i++) { //Draw body of progress bar
    display.drawLine(locX,locY+i,locX+aLocX,locY+i,WHITE);
    }
  }

}

void ledStatus() { //Show LED value bars
  display.drawChar(0,barLocY,'R',WHITE,BLACK,1); //Bar label
  drawHBar(0,barLocY+8,3,25,map(ledR,0,255,0,100)); //Testing progress bar

  display.drawChar(30,barLocY,'G',WHITE,BLACK,1); //Bar label
  drawHBar(30,barLocY+8,3,25,map(ledG,0,255,0,100)); //Testing progress bar

  display.drawChar(60,barLocY,'B',WHITE,BLACK,1); //Bar label
  drawHBar(60,barLocY+8,3,25,map(ledB,0,255,0,100)); //Testing progress bar

  display.drawChar(90,barLocY,'W',WHITE,BLACK,1); //Bar label
  drawHBar(90,barLocY+8,3,25,map(ledW,0,255,0,100)); //Testing progress bar

  display.drawChar(0,barLocY+15,'P',WHITE,BLACK,1);
  drawHBar(9,barLocY+18,3,128,map(ledP,0,255,0,100));
}

void displayUpdate() { //Update info display

  display.clearDisplay(); //Clean the Screen


if (screenPage == 0) {
  if (tempEnabled) { //Add Temperature to Display
    //Update temperature display
    display.setCursor(0, 0); //Set cursor location
    display.setTextSize(1);
    display.println(tempUnit);
    if (tNeg == 1) {display.print(" -");} //If temp negative add a minus sign
    display.setCursor(10,0);
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

  display.setCursor(0,24);
  display.setTextSize(1);
  display.print("Next: ");
  display.print(nextTime[0]);
  display.print(":");
  display.print(nextTime[1]);
  ledStatus();
}

  display.display(); //Put the stuff on the display
}





