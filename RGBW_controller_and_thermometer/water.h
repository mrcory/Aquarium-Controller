/*Water change related
I take no responsibility for any damage this causes. Always have a hardware failsafe.
For example a float valve that will physically cut off the water. Also, you could run
power for the valve through a switch that is actuated by a float. 
*/

#define readThreshold 750                      //Minimum reading required to trigger analogRead

int waterStage = 0;                            //0:OFF 1:Drain 2:FILL
bool waterChangeTrigger = false;
bool waterOn = false;                          //Fill toggle
bool waterDrain = false;
bool waterFail = false;
int waterMode = 0;                             //Water Mode 0-Normal 1-Autofill
unsigned long convDrainTime = drainTime*1000;  //Convert drain time from seconds to milliseconds
unsigned long newDrainTime = drainTime;                      //Using for Blynk settings




bool waterSafe() { //Return true if water safety not tripped
  //waterOn = false;; //Force water to turn off
  return !waterFail;
}

bool waterLevelCheck(byte _pin) { //Return true if waterSense pin is high
  if (analogRead(_pin) >= readThreshold) {
    return true;
  } else {
    return false;
  }
}

void waterFillStopCheck() {
  if (waterLevelCheck(waterSenseHi) == true || waterLevelCheck(waterSenseLo) == true) {
    waterOn = false;
  }
}

void waterSetup() {
  analogWrite(waterFill,0);
  pinMode(waterSenseHi,INPUT);
  
  if (senseMode == 2) {
    pinMode(waterSenseLo,INPUT); //Set sensor pin
  }
  if (debugMe == true) { Serial.println("[Water] Water Change Enabled");}
}


void waterRun() { //Function to run in loop

   if(newDrainTime != drainTime) {
    drainTime = newDrainTime;
    convDrainTime = drainTime*1000;
   }

  if (waterSafe() == false) { //If water is not safe then force pins to low
    analogWrite(pumpControl,0);
    analogWrite(waterFill,0); 
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
    convDrainTime = drainTime*1000;
    Serial.print("VAL: ");
    Serial.println(convDrainTime);
    analogWrite(pumpControl, 255); //Run the pump

  if (senseMode == 1) { //Single Sensor mode will use a timer
    if (timer(convDrainTime,6) == true) {
      waterStage++;
      timerReset(6);
      analogWrite(pumpControl, 0); //Stop the pump

      if (debugMe == true) { Serial.println("[Water] Water Filling");}
      
        #if wifiEnable
          Blynk.notify("{DEVICE_NAME} water drained. Starting fill.");
        #endif
    }
    
  } else {
    analogWrite(pumpControl,0); //Make sure pump is turned off
  }

  if (senseMode == 2) {
      if (waterLevelCheck(waterSenseLo) == true || timer(convDrainTime,6) == true) { //Timer overide in case of sensor failure
        waterStage++; //Go to fill stage
        timerReset(6);
        analogWrite(pumpControl, 0); //Stop the pump

        if (debugMe == true) { Serial.println("[Water] Water Filling");}
        
        #if wifiEnable
          Blynk.notify("{DEVICE_NAME} water drained. Starting fill.");
        #endif
      
      }
  }
}

//-----

  if (waterSafe() == true && waterStage == 2) {
    analogWrite(pumpControl,0); //Double sure pump is off
    analogWrite(waterFill, 255);

    if (waterLevelCheck(waterSenseHi) == true) { // || timer(fillTime*1000,7) == true) {
      waterStage = 0;
      analogWrite(waterFill, 0);

      if (debugMe == true) { Serial.println("[Water] Water Fill Complete");}

      #if wifiEnable
        Blynk.notify("{DEVICE_NAME} water has been filled");
      #endif
    }
  } else {
    analogWrite(waterFill, 0);
  }
  
}
