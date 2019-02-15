/*Water change related
I take no responsibility for any damage this causes. Always have a hardware failsafe.
For example a float valve that will physically cut off the water. Also, you could run
power for the valve through a switch that is actuated by a float. 
*/

int waterStage = 0; //0:OFF 1:Drain 2:FILL
bool waterChangeTrigger = false;
bool waterOn = false; //Fill toggle
bool waterDrain = false;
bool waterFail = false;
byte waterMode = 0; //Water Mode 0-Normal 1-Autofill

bool waterSafe() { //Return true if water safety not tripped
  //waterOn = false;; //Force water to turn off
  return !waterFail;
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
  if (waterLevelCheck(waterSenseHi) == true || waterLevelCheck(waterSenseLo) == true || waterOveride() == true) {
    waterOn = false;
  }
}

void waterSetup() {
  pinMode(waterFill,OUTPUT); //Set control pin to output
  pinMode(waterSenseLo,INPUT); //Set sensor pin
  pinMode(waterSenseHi,INPUT);
}

void waterRun() { //Function to run in loop
  /*
  if (waterLevelCheck(waterSenseHi) == true || waterSafe() == true) { //Safety Check
    waterOn = false; 
  }
  */

  #if wifiEnable
    if (waterChangeTrigger == true && waterStage == 0) { //Blynk Control
      waterStage = 1;
    }
  #endif
  
  if (waterSafe() == true && waterStage == 1) {
    digitalWrite(pumpControl, HIGH); //Run the pump

    if (waterLevelCheck(waterSenseLo) == true) {
       waterStage++; //Go to fill stage

      #if wifiEnable
        Blynk.notify("{DEVICE_NAME} water drained. Starting fill.");
      #endif
    
    }
  } else {
    digitalWrite(pumpControl, LOW); //Stop the pump
  }

//-----

  if (waterSafe() == true && waterStage == 2) {
    digitalWrite(waterFill, HIGH);

    if (waterLevelCheck(waterSenseHi) == true) {
      waterStage = 0;

      #if wifiEnable
        Blynk.notify("{DEVICE_NAME} water has been filled");
      #endif
    }
  } else {
    digitalWrite(waterFill, LOW);
  }
  
}
