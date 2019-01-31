/*Water change related
I take no responsibility for any damage this causes. Always have a hardware failsafe.
For example a float valve that will physically cut off the water. Also, you could run
power for the valve through a switch that is actuated by a float. 
*/

bool waterOn = false;
bool waterDrain = false;
bool waterFail = false;

void waterSetup() {
  pinMode(waterPin,OUTPUT); //Set control pin to output
  pinMode(waterSense,INPUT); //Set sensor pin
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
  if (waterLevelCheck(waterSense) == true || waterLevelCheck(waterSense2) == true || waterOveride() == true) {
    waterOn = false;
  }
}

bool waterSafe() { //Return true if water safety not tripped
  waterOn = false;; //Force water to turn off
  return !waterFail;
}

