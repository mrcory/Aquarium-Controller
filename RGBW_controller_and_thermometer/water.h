//Water change related

int waterPin; //Water control pin
int waterSense; //Water sensor pin
int waterSense2; //Upper water sensor

int waterTimeMin;
int waterTimeMax;

bool waterOn = false;

pinMode(waterPin,OUTPUT); //Set control pin to output
pinMode(waterSense,INPUT); //Set sensor pin

void waterFill() { //Call to start flow
  waterOn = true;
}

void waterEmerStop() { //Call to stop flow
  waterOn = false;
}

bool waterLevelCheck(byte _pin) { //Return true if waterSense pin is high
  if (digitalRead(_pin) == HIGH) {
    return true;
  } else {
    return false;
  }
}

bool waterOveride() { //Timer overide
  return false;
}

void waterFillStopCheck() {
  if (waterLevelCheck(waterSense) true || waterLevelCheck(waterSense2) true || waterOveride() true) {
    waterOn = false;
  }
}

#include "waterbutton.h" //Temporary button control while menu is not done
