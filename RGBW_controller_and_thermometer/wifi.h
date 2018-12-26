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
  Blynk.virtualWrite(V14,ledC[0]); //R
  Blynk.virtualWrite(V11,ledC[1]); //G
  Blynk.virtualWrite(V12,ledC[2]); //B
  Blynk.virtualWrite(V13,ledC[3]); //W
  Blynk.virtualWrite(V13,ledC[4]); //Bright

  Blynk.virtualWrite(V15,ledTarget[0]);
  
}

BLYNK_WRITE(V1)
{
  ledHold = param.asInt();

}

BLYNK_WRITE(V10) {
  if (ledHold == true) {
    ledTarget[0] = param[0].asInt();
    ledTarget[1] = param[1].asInt();
    ledTarget[2] = param[2].asInt();
  }
}




#define serialBypass false

#if !serialCommands && !serialBypass
  #error "Wifi requires that serial commands be enabled for wifi configuration. To bypass define serialBypass true."
#endif
