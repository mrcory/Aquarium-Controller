//New light controls

int convOnTimes[times];
int convOffTimes[times];
byte currentTimer = 0;

int timeMin() { //Convert hour and minute (Hour*60+Minute)
  int _time = (hour()*60) + minute();
  return _time;
}

bool ledCheck() {
  int _now = timeMin();
  bool _state = false;
  
  for (byte i=0;i<times;i++) {
    if (between(_now,convOnTimes[i],convOffTimes[i])) {_state = true; currentTimer = i;
    }
  }

  return _state;
}

int convertTime(int _hour, byte _minute) {
  int _converted = (_hour*60)+_minute;
    return _converted;
}

void controlSetup() {
  for (byte i=0;i<times;i++) {
    convOnTimes[i]  = convertTime(ledOnTimes[i][0],ledOnTimes[i][1]);
    convOffTimes[i] = convertTime(ledOffTimes[i][0],ledOffTimes[i][1]);
  }
}

void colorChange1() {
   
      for (byte a=0;a<5;a++) 
        {ledC[a] = ledCo[currentTimer][a];
      }
    
}

void timerCheck() {
  if (ledCheck() == true && ledState == 0) {ledPower();colorChange1();}
  if (ledCheck() == false && ledState == 1) {ledPower();colorChange1();}
}

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
  
}
