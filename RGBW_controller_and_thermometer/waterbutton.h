#include <AnalogButtons.h>

void dummy() {
  bool _dummy true;  
}

bool upClick() {
  waterFill();
  return true;
}

bool downClick() {
  waterEmerStop();
  return true;
}

Button up = Button(840, &dummy, &upClick);
Button down = Button(957, &downClick);
