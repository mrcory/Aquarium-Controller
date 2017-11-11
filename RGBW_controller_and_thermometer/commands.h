void ledRedUpdate(int arg_cnt, char **args) {
  ledR = cmdStr2Num(args[1], 10);
  Serial.print("Red Updated to ");
  Serial.println(ledR);
  ledUpdate = 1;
}

void ledBlueUpdate(int arg_cnt, char **args) {
  ledB = cmdStr2Num(args[1], 10);
  Serial.print("Blue Updated to ");
  Serial.println(ledB);
  ledUpdate = 1;
}

void ledGreenUpdate(int arg_cnt, char **args) {
  ledG = cmdStr2Num(args[1], 10);
  Serial.print("Green Updated to ");
  Serial.println(ledG);
  ledUpdate = 1;
}

void ledWhiteUpdate(int arg_cnt, char **args) {
  ledW = cmdStr2Num(args[1], 10);
  Serial.print("White Updated to ");
  Serial.println(ledW);
  ledUpdate = 1;
}

void colorSet(int arg_cnt, char **args) {
  if (arg_cnt >= 7) {
    ledR = cmdStr2Num(args[1], 10);
    ledG = cmdStr2Num(args[2], 10);
    ledB = cmdStr2Num(args[3], 10);
    ledW = cmdStr2Num(args[4], 10);
    ledP = cmdStr2Num(args[5], 10);
    ledState = cmdStr2Num(args[6], 10);
  }
}

void turnOn() {
  int oldPage = screenPage;
  ledState = 1;
  ledUpdate = 1;
  Serial.println("State turn on");
  screenPage = 2;
  displayUpdate();
  Alarm.delay(1000);
  screenPage = oldPage;
}

void turnOff() {
  ledState = 0;
  ledUpdate = 1;
  Serial.println("State turn off");
}

void colorChange(int colorSet[5]) {
  ledR = colorSet[0];
  ledG = colorSet[1];
  ledB = colorSet[2];
  ledW = colorSet[3];
  ledUpdate = 1;
}


void screenChange(int arg_cnt, char **args) {
  screenPage = cmdStr2Num(args[1],10);
  if (args[2] == "tt") { Serial.print("It sees text.");}
}

