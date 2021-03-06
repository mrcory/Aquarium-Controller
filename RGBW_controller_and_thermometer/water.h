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
unsigned long newDrainTime = drainTime;       //Using for Blynk settings
unsigned long convFillTime = fillTime*1000;    //Convert fill time from seconds to milliseconds
unsigned long newFillTime = fillTime;         //Using for Blynk settings
unsigned long safetyDrainTime = 0; //Minimum drain time for overfill protection
bool pumpRun = false;
bool pumpLock = false;
bool pumpRunEmergency = false;


#if waterOverfillProtection
bool waterOver(byte _pin) {
  if (analogRead(_pin) > readThreshold) {
    return true;
  } else {
    return false;
  }
}
#endif

#if !waterOverfillProtection //If not using overfill protection just return a false safe all the time
bool waterOver(byte _pin) {
  return false;
}
#endif



void pumpController() {
  if ((pumpRun || pumpRunEmergency) && !pumpLock ) {
    analogWrite(pumpControl,255);

      if (waterOver(waterOverfull)) {
        timerReset(8);
        Serial.println("Water OVERFILL!");
      }
  }
    if ((!pumpRun && !pumpRunEmergency) || pumpLock) {
      analogWrite(pumpControl,0);
      Serial.println("Pump Off");
    }
}

bool waterOverCheck() {
  if (waterOver(waterOverfull)) {
    pumpRunEmergency = true;
      
  } else {
    if (timer(emergencyDrainTime,8)) {    
      pumpRunEmergency = false;
    }
  }

  Serial.print("Over: "); Serial.println(analogRead(waterOverfull));
}

bool waterSafe() { //Return true if water safety not tripped
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

  pumpController(); //Run the pump Controller
  waterOverCheck();

   if(newDrainTime != drainTime) {
    drainTime = newDrainTime;
    convDrainTime = drainTime*1000;
   }

   if(newFillTime != fillTime) {
    fillTime = newFillTime;
    convFillTime = fillTime*1000;
   }

  if (waterSafe() == false) { //If water is not safe then force pins to low
    pumpRun = false;
    pumpLock = true;
    analogWrite(waterFill,0); 
  }

  #if wifiEnable //Trigger water change cycle via Blynk app
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
    pumpRun = true; //Run the pump

  if (senseMode == 1) { //Single Sensor mode will use a timer
    if (timer(convDrainTime,6) == true) {
      waterStage++;
      timerReset(6);
      pumpRun = false; //Stop the pump

      if (debugMe == true) { Serial.println("[Water] Water Filling");}
      
        #if wifiEnable
          Blynk.notify("{DEVICE_NAME} water drained. Starting fill.");
        #endif
    }
    
  } else {
    pumpRun = false; //Make sure pump is turned off
  }

  if (senseMode == 2) {
      if (waterLevelCheck(waterSenseLo) == true || timer(convDrainTime,6) == true) { //Timer overide in case of sensor failure
        waterStage++; //Go to fill stage
        timerReset(6); //Reset timer
        pumpRun = false; //Stop the pump

        if (debugMe == true) { Serial.println("[Water] Water Filling");}
        
        #if wifiEnable
          Blynk.notify("{DEVICE_NAME} water drained. Starting fill.");
        #endif
      
      }
  }
}

//-----Next Stage

  if (waterStage == 2) { //This stage just resets the timer and continues. Needed to allow topping off the tank
    timerReset(6);       // with the safety timer without first draining.
    waterStage++;
  }

 //----Next Stage

  if (waterSafe() == true && waterStage == 3) {
    pumpRun = false; //Double sure pump is off
    analogWrite(waterFill, 255);

    if (waterLevelCheck(waterSenseHi) == true || timer(convFillTime,6) == true) {
      waterStage = 0;          //Reset water change state to 0
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
