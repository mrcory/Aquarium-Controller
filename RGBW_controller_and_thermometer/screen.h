void displayUpdate() { //Update info display


  display.clearDisplay(); //Clean the Screen
  
  
  int oldPage;
  
    if (screenPage == 1) { //Screen 1 display
        showTemp(0,0);
        showHiLo(97,0);
        display.setCursor(0,24);
        display.print("Timer ");
        display.print(currentTimer);
        showTime(80,24,1);
  
        ledStatus(0,42); //Show LED status bars
  
      #if tempWarnEnable
        if (tempWarn == true) {
          display.setCursor(80,32);
          display.print(F("Temp WARN"));
          
        }
      #endif
  
  }
  
  if (screenPage == 0) {
      showTime(0,0,1);
      display.println();
      display.print(F("Power State: "));
      display.print(ledState);
      display.println(" ");
      display.print(F("Version: ")); 
      //display.println(ver);
      if (EEPROM.read(0) == 1) { //If position 0 is 1 then there is a saved config
        display.println(F("Config Saved"));
      }
      display.setCursor(0, 44);
      display.print(F("RGBW Aquarium Control by: Cory McGahee"));
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
}

display.display(); //Put the stuff on the display

}
