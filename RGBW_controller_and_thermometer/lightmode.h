//New light controls



int convertTime(int _hour, byte _minute) {
  int _converted = (_hour*60)+_minute;
    return _converted;
}

bool ledCheck() {
  int _now = convertTime(hour(),minute());
  bool _state = false;
  
  for (byte i=0;i<times;i++) {
    if (between(_now,convOnTimes[i],convOffTimes[i])) {_state = true; currentTimer = i;
    }
  }

  return _state;
}



void controlSetup() {
  for (byte i=0;i<times;i++) {
    convOnTimes[i]  = convertTime(ledOnTimes[i][0],ledOnTimes[i][1]);
    convOffTimes[i] = convertTime(ledOffTimes[i][0],ledOffTimes[i][1]);
  }
}

void colorChange1() {
   
      for (byte i = 0; i < 5; i++) 
        {ledTarget[i] = ledCo[currentTimer][i];
      }
      ledUpdate = 1;
      //Serial.print(F("Color Change, Timer: ")); Serial.println(currentTimer); //Print out when color changes 
}

void timerCheck() {
  if (ledCheck() == true && ledState == 0) {ledPower();colorChange1();}
  if (ledCheck() == false && ledState == 1) {ledPower();colorChange1();}
}

colorFade() {
  
  for (byte i=0;i<5;i++) {{
    if (ledC[i] != ledTarget[i]) {
      if (ledC[i] < ledTarget[i]) {
        ledC[i]++;
    }
      if (ledC[i] > ledTarget[i]) {
        ledC[i]--;
}}}}}

void ledAdjust(byte _mode) { //New led controller

  if (_mode == 1) {
    if (ledState == 1 && ledC[4] > ledP) { //Adjust power to target +
      ledP = ledP + fadeStep;
      ledUpdate = 1;
    }
  
    if (ledState == 0 && ledPMin < ledP) { //Adjust power to target -
      ledP = ledP - fadeStep;
      ledUpdate = 1;
    }
  }

if (timer(crossFade*1000,3)) { //Every [crossfade]*1000 milliseconds change by one step
  colorFade();
}
  
  colorChange1();
}



