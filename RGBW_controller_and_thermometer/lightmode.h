//New light controls

int convOnTimes[times];
int convOffTimes[times];
int currentTimer = 0;

int timeMin() { //Convert hour and minute (Hour*60+Minute)
  int _time = (hour()*60) + minute();
  return _time;
}

bool ledCheck() {
  int _now = timeMin();
  bool _state = false;
  for (int i=0;i<times;i++) {
    if (_now >=  convOnTimes[i] && _now <= convOffTimes[i]) {_state = true; currentTimer = i;
     //Break the loop
    }
   // else { delay(500); Serial.println(_now); }
  }

  return _state;
}

int convertTime(int _hour, int _minute) {
  int _converted = (_hour*60)+_minute;
    return _converted;
}

void controlSetup() {
  for (int i=0;i<times;i++) {
    convOnTimes[i]  = convertTime(ledOnTimes[i][0],ledOnTimes[i][1]);
    convOffTimes[i] = convertTime(ledOffTimes[i][0],ledOffTimes[i][1]);
  }
}

void colorChange1() {
   
      for (int a=0;a<5;a++) 
        {ledC[a] = ledCo[colorChoice[currentTimer]][a];
      }
    
}

void timerCheck() {
  if (ledCheck() == true && ledState == 0) {ledPower();colorChange1();}
  if (ledCheck() == false && ledState == 1) {ledPower();colorChange1();}
}

