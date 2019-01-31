//Oh Yeah, we are gonna get some wifi in here. (Once I have the hardware)
/*
 * V5 - Temp
 */


//Some Supporting functions

void sendTemp() {
  Blynk.virtualWrite(V5,temp);
}

//Send all the data we want to access

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

BLYNK_WRITE(V20) { //Water Change
  waterChangeTrigger = param.asInt();
}


#define serialBypass false

#if !serialCommands && !serialBypass
  #error "Wifi requires that serial commands be enabled for wifi configuration. To bypass define serialBypass true."
#endif
