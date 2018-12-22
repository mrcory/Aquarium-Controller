//Oh Yeah, we are gonna get some wifi in here. (Once I have the hardware)
/*
 * V5 - Temp
 */


//Some Supporting functions

#if serialCommands



  void wifiSSID(int arg_cnt, char **args) {
    mySSID = args[1]; //Set SSID
    configSave(); //Save the config
  }

  void wifiPass(int arg_cnt, char **args) {
    wifiPassword = args[1]; //Set password
    configSave(); //Save the config
  }

  void blynkSet(int arg_cnt, char **args){
    blynkToken = args[1]; //Set Blynk server token
    configSave(); //Save the config
  }



#else
  #warning "Serial Commands are required to setup wifi."
#endif


void sendTemp() {
  Blynk.virtualWrite(V5,temp);
}

//Send all the data we want to access

void sendData() {
  Blynk.virtualWrite(V10,ledC[0]); //R
  Blynk.virtualWrite(V11,ledC[1]); //G
  Blynk.virtualWrite(V12,ledC[2]); //B
  Blynk.virtualWrite(V13,ledC[3]); //W
  Blynk.virtualWrite(V13,ledC[4]); //Bright

  
}

BLYNK_WRITE(V1)
{
  ledHold = param.asInt();
}
