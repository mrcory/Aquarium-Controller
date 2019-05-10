//New light controls
int globalNow = 0;


int convertTime(int _hour, int _minute) {
  int _converted = (_hour*60)+_minute;
    return _converted;
}

bool ledCheck() {
  int _now = convertTime(hour(),minute());
  bool _state = false;

  globalNow = _now;
  
  for (int i=0;i<times;i++) {
    if (between(_now,convOnTimes[i],convOffTimes[i])) {currentTimer = i; _state = true;
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

void calculateFade() {
  if (fadeTime > 0) { //If a fadetime has been set solve for fadeStep to match it
    fadeStep = (ledCo[currentTimer][4] / (fadeTime * 60.0)); //Make fadeStep from fadeTime or make it instant (255)
  } else {
    fadeStep = 255; //If fateTime is set to 0 then just turn on and off completely
  }
}

void colorChange1(bool _force,int _forceTimer) {

   if ((currentTimer != oldTimer) /*&& _force == false*/) {
      ledUpdate = 1;
      Serial.print(F("[LED] Change, Timer: ")); Serial.println(currentTimer); //Print out when color changes 
      memcpy(ledTarget,ledCo[currentTimer],5*sizeof(int)); //Load ledTarget from stored values
      oldTimer = currentTimer;
   }

   if (_force == true) {
    memcpy(ledTarget,ledCo[_forceTimer],5*sizeof(int));
   }

   calculateFade();

}

void timerCheck() {
  //colorChange1(false,0);
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
      Serial.println("LED+");
    }
  
    if (ledState == 0 && ledPMin < ledP) { //Adjust power to target -
      ledP = ledP - fadeStep;
      ledUpdate = 1;
      Serial.println("LED-");
    }

    colorFade();
    colorChange1(false,0);
  }

}


