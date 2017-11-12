void colorSet(int arg_cnt, char **args) {
  if (arg_cnt >= 7) {
    ledC[0] = cmdStr2Num(args[1], 10);
    ledC[1] = cmdStr2Num(args[2], 10);
    ledC[2] = cmdStr2Num(args[3], 10);
    ledC[3] = cmdStr2Num(args[4], 10);
    ledP = cmdStr2Num(args[5], 10);
    ledState = cmdStr2Num(args[6], 10);
  }
}

void ledPower() {
  int oldPage = screenPage; //Store old page location
  if (ledState == 0) {ledState = 1;} else {ledState = 0;} //Chang between on and off
  ledUpdate = 1; //There has been a change, update analogWrite
  screenPage = 2; //Chang page to "LED ON(OFF)"
  displayUpdate(); Alarm.delay(1000); //Update and display for 1 second
  screenPage = oldPage; //Restore old page location
}

void colorChange(int colorSet[5]) {
  ledC[0] = colorSet[0];
  ledC[1] = colorSet[1];
  ledC[2] = colorSet[2];
  ledC[3] = colorSet[3];
  ledUpdate = 1;
}

void screenChange(int arg_cnt, char **args) {
  screenPage = cmdStr2Num(args[1],10);
  Serial.print(args[1]);
}

void ledChange(int arg_cnt, char **args) {
  if (arg_cnt == 3) {ledC[cmdStr2Num(args[1],10)] = cmdStr2Num(args[2],10);} //If 3 arguments, adjust single led channel
  if (arg_cnt >= 6) {for(int i = 0; i < 5; i++) {ledC[i] = cmdStr2Num(args[i+1],10);}}
  //if (arg_cnt >= 6) {ledC[4] = cmdStr2Num(args[6],10);}
}

