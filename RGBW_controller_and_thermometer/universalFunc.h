//Math Stuff

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
#define countDataAmount 4 //Number of timers
unsigned long countData[countDataAmount] = {0}; //Holds count information. (Adjust for numeber of timers needed.)



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

void timerSetup() {
  for (int i=0;i<countDataAmount;i++) {
    millisCount(0,i);
  }
}

bool timer(unsigned long _interval,int _id) { //_interval in millis, _id in countData
  if (millisCount(1,_id) >= _interval) {
    millisCount(0,_id);
    return true;
  } else {
    return false;
  }
}



