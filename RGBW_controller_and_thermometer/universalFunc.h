unsigned long tempNum; //Testing


//Math Stuff

//Return true id _target is between _bottom and _top
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


//Mode 0 resets the timer
//Mode 1 counts the time that has passed in milliseconds
unsigned long millisCount(int _mode, int _id) { //_mode: 0-Start 1-Stop | _id Identity number (allow more by editing the length of countData
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

//Fills timer array with 0's
void timerSetup() {
  for (int i=0;i<countDataAmount;i++) {
    millisCount(0,i);
  }
}

//Check if a timer has gone over the trigger amount in milliseconds
bool timer(int _interval,int _id) { //_interval in millis, _id in countData

  tempNum = _interval * 1000;
  
  if (millisCount(1,_id) >= tempNum) {
    millisCount(0,_id);
    return true;
  } else {
    return false;
  }
}



