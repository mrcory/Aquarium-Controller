/*
 * V5 - Temp
 * 
 * v30 - Fill Timeout
 * v31 - Drain Timeout
 * v35 - Report waterSenseHi
 * v36 - Trigger water Fill
 */

//Feedback
void wifiFeedback() {
  Serial.print(F("SSID: ")); Serial.println(mySSID);
  Serial.print(F("Pass: ")); Serial.println(wifiPassword);
  Serial.print(F("Token: ")); Serial.println(blynkToken);
}

//Some Supporting functions

void sendBlynk() {
  #if tempEnable
    Blynk.virtualWrite(V5,temp);
  #endif


  Blynk.virtualWrite(V41,DST);
  Blynk.virtualWrite(V43,tft_brightness);

#if waterFillEnable
  Blynk.virtualWrite(V31,convFillTime);
  Blynk.virtualWrite(V33,convDrainTime);
  Blynk.virtualWrite(V35,analogRead(waterSenseHi));
#endif
  
}



//Receive all the data we want

void sendData() {
  
}

BLYNK_WRITE(V1)
{
  ledHold = param.asInt();

}

//Values for manual LED control
BLYNK_WRITE(V10) { //R
    ledWifi[0] = param.asInt();
}

BLYNK_WRITE(V11) { //G
  ledWifi[1] = param.asInt();
}

BLYNK_WRITE(V12) {//B
  ledWifi[2] = param.asInt();
}

BLYNK_WRITE(V13) { //W
  ledWifi[3] = param.asInt();
}

BLYNK_WRITE(V14) { //Brightness
  ledWifi[4] = param.asInt();
}

  BLYNK_WRITE(V40) {
    DST = param.asInt();
  }

#if waterFillEnable
  BLYNK_WRITE(V20) { //Water Change
    waterChangeTrigger = param.asInt();
  }

  BLYNK_WRITE(V30) {
    newFillTime = param.asInt();
  }

  BLYNK_WRITE(V32) {
    newDrainTime = param.asInt();
  }

  //BLYNK_WRITE(V42) {
  //  tft_brightness = param.asInt();
  //}

  BLYNK_WRITE(V36) {
    waterStage = param.asInt();
  }
#endif


#if !serialCommands && !serialBypass
  #error "Wifi requires that serial commands be enabled for wifi configuration. To bypass define serialBypass true in configPlus.h"
#endif
