//Oh Yeah, we are gonna get some wifi in here. (Once I have the hardware)

char mySSID;
char myPassword;


//Some Supporting functions

#if serialCommands
  void wifiSSID(_ssid) {
    mySSID = _ssid; //Set SSID
    configSave(); //Save the config
  }

  void wifiPass(_password) {
    myPassword = _password; //Set password
    configSave(); //Save the config
  }

  cmdAdd("ssid",wifiSSID);
  cmdAdd("wifipass",wifiPass);

#else
  #warning "Serial Commands are required to setup wifi."
#endif
