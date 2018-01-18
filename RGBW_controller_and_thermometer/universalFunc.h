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
