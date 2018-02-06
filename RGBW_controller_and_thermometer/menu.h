//Menu Stuff

String ledLetter[4] {"R","G","B","W"};
const byte menuLine = 0;
byte buttonReturn = 0; //Left -1, right 1, up 2, down -2, back/menu 3
byte saveSet = 0;


//Buttons!
bool upClick() {
  buttonReturn = 2;
  return true;
}

bool downClick() {
  buttonReturn = -2;
  return true;
}

bool rightClick() {
  buttonReturn = 1;
  return true;
}

bool leftClick() {
  buttonReturn = -1;
  return true;
}

bool menuClick() {
  buttonReturn = 3;
  return true;
  
  if (menuActive) {menuActive == false;} //If menu active disable it
  else
  if (!menuActive) {menuActive == true;} //If menu not active enable it
}

bool menuHold() {
  buttonReturn = -3;
  return true;
}



AnalogButtons analogButtons(buttonPin, INPUT);
Button up = Button(_upVal, &upClick);
Button down = Button(_downVal, &downClick);
Button right = Button(_rightVal, &rightClick);
Button left = Button(_leftVal, &leftClick);
Button menu = Button(_menuVal, &menuClick, &menuHold);



void menuRun() {
  if (menuActive) { //If menu is active
    //drawArrowRIGHT(1,menuLine); //Draw arrow
    
    if (buttonReturn != 0 && menuLine < 5) {
      if (rightClick) {ledC[menuLine]++;}
      if (leftClick)  {ledC[menuLine]--;}
      buttonReturn = 0;
    }

    if (buttonReturn != 0 && menuLine == 5) {
      if (rightClick) {saveSet++;}
      if (leftClick)  {saveSet--;}
    }

  if (menuClick) {
    menuActive = false; 
  }

  if (menuHold) {
    //Add config save stuff here
      for (byte i = 0; i < 5; i++) 
        {ledCo[currentTimer][i] = ledC[i];
        display.clearDisplay();
        display.setCursor(0,0);
        display.println(" SAVED!");
        display.display();}
  }
}}


//Page 1
void MenuPageOne() {
  display.setCursor(6,0);
  for (int i=0;i<4;i++) { //Draw the led array vals
    if (menuLine == i) {
      display.print(">");
    }
    display.print(" ");
    display.println(ledLetter[i]);
    display.println(ledC[i]);
  }

  if (menuLine == 4) {
    display.print(">");
  }
  display.println(F(" Bright"));
  display.println(ledC[4]);

  display.print(F("Hold Menu to save."));
  
  menuRun();
}



