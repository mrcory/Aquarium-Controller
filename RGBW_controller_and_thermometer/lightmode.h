//New light controls

bool timerState[times]; //Store true false state for timer triggers


int convertTime(int _hour, int _minute) { //Turn hour and minute into a minute count
  int _converted = (_hour*60)+_minute;
    return _converted;
}

bool ledCheck() { //Check if between times
  int _now = convertTime(hour(),minute());
  bool _state = false;
  
  for (int i=0;i<times;i++) {
    if (between(_now,convOnTimes[i],convOffTimes[i]) ) {_state = true; currentTimer = i; 
      if (!timerState[i]) { //If the current timer is not true then make it so.
        for (int x=0;i<=times;x++) {
          if (x != i) { //Change all values that are not for the current timer to false
            timerState[x] = false;
          }
        }
      }
    }
  }

  if (currentTimer == offTimer) {
    ledState = 0;
    _state = false;
  }

  return _state;
}



void controlSetup() {
  for (int i=0;i<times;i++) {
    convOnTimes[i]  = convertTime(ledOnTimes[i][0],ledOnTimes[i][1]);
    convOffTimes[i] = convertTime(ledOffTimes[i][0],ledOffTimes[i][1]);
  }
}

void colorChange1(bool _force) {

   if ((currentTimer != oldTimer) || (_force)) {
      //for (int i = 0; i < 5; i++) 
      //  {ledC[i] = ledCo[currentTimer][i]; //Load ledC from stored values
      //}
      ledUpdate = 1;
      Serial.print(F("Color Change, Timer: ")); Serial.println(currentTimer); //Print out when color changes 

      oldTimer = currentTimer;
      memcpy(ledTarget,ledCo[currentTimer],5*sizeof(int)); //Load ledTarget from stored values
      

   }
}

void timerCheck() {
  if (ledCheck() == true && ledState == 0) {ledPower();colorChange1(false);}
  if (ledCheck() == false && ledState == 1) {ledPower();colorChange1(false);}
}

void colorFade() {
  
  for (int i=0;i<=5;i++) {{
    if (ledC[i] != ledTarget[i]) {
      if (ledC[i] < ledTarget[i]) {
        ledC[i]++;
        ledUpdate = 1;
    }
      if (ledC[i] > ledTarget[i]) {
        ledC[i]--;
        ledUpdate = 1;
}}}}}



void ledAdjust(int _mode) { //New led controller

  if (_mode == 1) {
    if (ledState == 1 && ledC[4] > ledP) { //Adjust power to target +
      ledP = ledP + fadeStep;
      ledUpdate = 1;
    }
  
    if (ledState == 0 && ledPMin < ledP) { //Adjust power to target -
      ledP = ledP - fadeStep;
      ledUpdate = 1;
    }
    
    colorChange1(false);
  }

  if (_mode == 2) {
      if (timer(crossFade*1000,3)) { //Every [crossfade]*1000 milliseconds change by one step
      colorFade();
    }
  }

}



