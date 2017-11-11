void drawHBar(int locX,int locY,int height,int width,int percent) { //Draw a progrss bar
  int aLocX = map(percent,1,100,1,width);
  display.drawLine(locX,locY,locX+width,locY,WHITE); //Draw outline of progress bar
  display.drawLine(locX,locY+height,locX+width,locY+height,WHITE); //Draw lower outline of progress bar
  
  for(int i = 0; i < height; i++) { //Draw body of progress bar
    display.drawLine(locX,locY+i,locX+aLocX,locY+i,WHITE);
  }

}

void displayUpdate() { //Update info display

  display.clearDisplay(); //Clean the Screen

  if (tempEnabled) { //Add Temperature to Display
    //Update temperature display
    display.setCursor(0, 0); //Set cursor location
    display.setTextSize(1);
    display.print(tempUnit);
    display.print(" "); //Just a space
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

  drawHBar(0,50,3,30,50); //Testing progress bar
  
  display.display(); //Put the stuff on the display
}





