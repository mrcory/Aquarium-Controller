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

void waterFillStopCheck() {
  if (waterLevelCheck(waterSenseHi) == true || waterLevelCheck(waterSenseLo) == true || waterOveride() == true) {
    waterOn = false;
  }
}

void waterSetup() {
  pinMode(waterFill,OUTPUT); //Set control pin to output
  digitalWrite(waterFill,LOW);
  pinMode(waterSenseHi,INPUT);

  if (senseMode == 2) {
    pinMode(waterSenseLo,INPUT); //Set sensor pin
  }
  if (debugMe == true) { Serial.println("[Water] Water Change Enabled");}
}


void waterRun() { //Function to run in loop

  if (waterSafe() == false) { //If water is not safe then force pins to low
    digitalWrite(pumpControl,LOW);
    digitalWrite(waterFill,LOW); 
  }

  #if wifiEnable
    if (waterChangeTrigger == true && waterStage == 0 && waterSafe() == true) { //Blynk Control
      waterStage = 1;
      timerReset(6);
      waterChangeTrigger = false; //Reset Trigger
      
      if (debugMe == true) { Serial.println("[Water] Water Draining");}
      
    }
  #endif
  
  if (waterSafe() == true && waterStage == 1) {
    digitalWrite(pumpControl, HIGH); //Run the pump

  if (senseMode == 1) { //Single Sensor mode will use a timer
    if (timer(drainTime,6) == true) {
      waterStage++;
      timerReset(6);
      digitalWrite(pumpControl, LOW); //Stop the pump

      if (debugMe == true) { Serial.println("[Water] Water Filling");}
      
        #if wifiEnable
          Blynk.notify("{DEVICE_NAME} water drained. Starting fill.");
        #endif
    }
    
  } else {
    digitalWrite(pumpControl,LOW); //Make sure pump is turned off
  }

  if (senseMode == 2) {
      if (waterLevelCheck(waterSenseLo) == true || timer(drainTime,6) == true) { //Timer overide in case of sensor failure
        waterStage++; //Go to fill stage
        timerReset(6);
        digitalWrite(pumpControl, LOW); //Stop the pump

        if (debugMe == true) { Serial.println("[Water] Water Filling");}
        
        #if wifiEnable
          Blynk.notify("{DEVICE_NAME} water drained. Starting fill.");
        #endif
      
      }
  }
}

//-----

  if (waterSafe() == true && waterStage == 2) {
    digitalWrite(waterFill, HIGH);

    if (waterLevelCheck(waterSenseHi) == true || timer(fillTime,6) == true) {
      waterStage = 0;
      digitalWrite(waterFill, LOW);

      if (debugMe == true) { Serial.println("[Water] Water Fill Complete");}

      #if wifiEnable
        Blynk.notify("{DEVICE_NAME} water has been filled");
      #endif
    }
  } else {
    digitalWrite(waterFill, LOW);
  }
  
}
