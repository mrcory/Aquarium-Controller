//New light controls



int convertTime(int _hour, int _minute) {
  int _converted = (_hour*60)+_minute;
    return _converted;
}

bool ledCheck() {
  int _now = convertTime(hour(),minute());
  bool _state = false;
  
  for (int i=0;i<times;i++) {
    if (between(_now,convOnTimes[i],convOffTimes[i])) {_state = true; currentTimer = i;
    }
  }

  return _state;
}



void controlSetup() {
  for (int i=0;i<times;i++) {
    convOnTimes[i]  = convertTime(ledOnTimes[i][0],ledOnTimes[i][1]);
    convOffTimes[i] = convertTime(ledOffTimes[i][0],ledOffTimes[i][1]);
  }
}

void colorChange1(bool _force,byte _forceTimer) {

   if ((currentTimer != oldTimer) && _force == false) {
      ledUpdate = 1;
      Serial.print(F("[LED] Change, Timer: ")); Serial.println(currentTimer); //Print out when color changes 
      memcpy(ledTarget,ledCo[currentTimer],5*sizeof(int)); //Load ledTarget from stored values
      oldTimer = currentTimer;
   }

   if (_force == true) {
    memcpy(ledTarget,ledCo[_forceTimer],5*sizeof(int));
   }

  //oldTimer = currentTimer;
}

void timerCheck() {
  if (ledCheck() == true && ledState == 0) {ledPower();colorChange1(false,0);}
  if (ledCheck() == false && ledState == 1) {ledPower();colorChange1(false,0);}
}

void colorFade() {
  
  for (int i=0;i<=5;i++) {{
    if (ledC[i] != ledTarget[i]) {
      if (ledC[i] < ledTarget[i]) {
        ledC[i] += crossFade;
        ledUpdate = 1;
    }
      if (ledC[i] > ledTarget[i]) {
        ledC[i] -= crossFade;
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

    colorFade();
    colorChange1(false,0);
  }

}
