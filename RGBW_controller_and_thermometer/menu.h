//Menu Stuff
//Will not be updated. Swapping to MQTT control

 
const char ledLetter[] = {'R','G','B','W'};
const int menuLine = 0;
int buttonReturn = 0; //Left -1, right 1, up 2, down -2, back/menu 3
int saveSet = 0;

#include <AnalogButtons.h>


//Buttons!
bool upClick() {
  buttonReturn = 2;
  Serial.println("Up");
  return true;
}

bool downClick() {
  buttonReturn = -2;
  Serial.println("Dn");
  return true;
  
}

bool rightClick() {
  buttonReturn = 1;
  Serial.println("Rt");
  return true;
  
}

bool leftClick() {
  buttonReturn = -1;
  Serial.println("Lt");
  return true;
  
}

bool menuClick() {
  buttonReturn = 3;
  Serial.println("Mn");
  
  
  if (menuActive == true) {menuActive = false;} //If menu active disable it
  else
  if (menuActive == false) {menuActive = true;} //If menu not active enable it

  return true;
}

bool menuHold() {
  buttonReturn = -3;
  Serial.println("MnH");
  return true;
  
}

//Set resistor values for buttons here
  #define _upVal 840
  #define _downVal 957
  #define _leftVal 979
  #define _rightVal 930
  #define _menuVal 700


AnalogButtons analogButtons(A1, INPUT);

Button up = Button(840, &upClick);
Button down = Button(957, &downClick);
Button right = Button(930, &rightClick);
Button left = Button(979, &leftClick);
Button menu = Button(700, &menuClick, &menuHold);


void menuRun() {
  if (menuActive) { //If menu is active
    
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
      for (int i = 0; i < 5; i++) 
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
