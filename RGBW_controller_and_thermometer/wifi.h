//Oh Yeah, we are gonna get some wifi in here. (Once I have the hardware)
//V5 - Temp


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

//Blynk timer functions
BlynkTimer temperature; //We will be pushing the current temperature so that it can be logged in a graph

void sendTemp() {
  Blynk.virtualWrite(V5,temp);
}
