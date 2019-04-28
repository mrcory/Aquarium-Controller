//Math Stuff

//Is _target between _bottom and _top. If so return true.
bool between(int _target, int _bottom, int _top) {
  if (_target >= _bottom && _target <= _top) {
    return true;
  } else {
    return false;
  }
}

bool isNegative(int _ref) { //If _ref is negative return true
  if (_ref < 0) {return true;}
  if (_ref >=0) {return false;}
}

//Timing
#define countDataAmount 8 //Number of timers
unsigned long countData[countDataAmount] = {0}; //Holds count information. (Adjust for numeber of timers needed.)
//0-3 = I don't remember at this point
//4 = fpsTimer
//5 = Regular timer
//6 = Water timer
//7 = Test water

//Used by timer function
int millisCount(int _mode, int _id) { //_mode: 0-Start 1-Stop | _id Identity number (allow more by editing the length of countData
  unsigned long _count;
  if (_mode == 0) {
    countData[_id]= millis();
    return 0;
  }

  if (_mode == 1) {
    _count = millis() - countData[_id];
    return _count;
  }

}

//Will set all variables in timer table to 0.
void timerSetup() {
  for (int i=0;i<countDataAmount;i++) {
    millisCount(0,i);
  }
}

//Use this to check if set time has passed.
//Will return true or false
bool timer(unsigned long _interval,int _id) { //_interval in millis, _id in countData
  if (millisCount(1,_id) >= _interval) {
    millisCount(0,_id);
    return true;
  } else {
    return false;
  }
}

void timerReset(byte _id) { //Reset timer start time
  countData[_id]= millis();
}
