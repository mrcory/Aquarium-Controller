//Menu functions and things

int menuOneL = 4;
int arrowPos = 0;
int menuLength = 0;
int menuPage = 0;

const String menu[4][6] = {
{"Back", "LED Power", "Timer", "Colors", "Info", "end"},
{"Back","Timed ON/OFF", "Instant ON/OFF","end"}
};

void menuDisplay() {
  int menuStop = 10;
  int i;
  display.print("Menu  Pos: ");
  display.print(arrowPos);
  display.print(" Menu: ");
  display.println(menuPage);
  

  if (enter) {menuPage = arrowPos;enter=false;arrowPos=0;}
  else
    for (i=0; i < 6; i++){
      if (menu[menuPage][i] != "end" ) {
        display.setCursor(20,(i*8)+8); //Position cursor
        display.print(menu[menuPage][i]);}
      else {
        menuStop = i+1;
        menuLength = i-1;
      }
  

  }
}

void dn() {if (menuLength > arrowPos) {arrowPos++;}}
void up() {if (arrowPos > 0) {arrowPos--;}}
void enterButton() {enter = true;}
