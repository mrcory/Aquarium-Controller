//Debug Function
void debugFunc() {
  if (debugLVL > 0) {
    if (debugLVL == 1) { //Debug information Set 1
      Serial.println();
      Serial.print(hour());
      Serial.print(":");
      Serial.print(minute());
      Serial.print(":");
      Serial.print(second());
      Serial.print(" ");
      Serial.print("Power State: ");
      Serial.print(ledState);
      Serial.println(" ");
    }
  
    if (debugLVL == 2) { //Debug Info lvl 2
      Serial.print("Red "); Serial.print(map(ledR, 0, 255, 0, ledP));
      Serial.print(" Green "); Serial.print(map(ledG, 0, 255, 0, ledP));
      Serial.print(" Blue "); Serial.print(map(ledB, 0, 255, 0, ledP));
      Serial.print(" White "); Serial.print(map(ledW, 0, 255, 0, ledP));
      Serial.print(" Power "); Serial.println(ledP);
    }
  
    if (debugLVL == 3) {
      Serial.print("Fade Steps ");
      Serial.print(fadeStep);
      Serial.print(" Temp ");
      Serial.println(temp);
    }

}
}

void debugUpdate(int arg_cnt, char **args) { //Update debug value in serial monitor
  debugLVL = cmdStr2Num(args[1], 10);
  Serial.print("Debug changed to ");
  Serial.println(debugLVL);

}
