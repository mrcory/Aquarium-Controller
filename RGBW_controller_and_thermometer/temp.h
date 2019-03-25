 //Temperature Functions 

#include <OneWire.h>
#include <DallasTemperature.h>

float temp;
float tempHi; //Max temp recorded
float tempLo; //Lowest temp recorded
boolean tNeg = false; //0 is positive 1 means negative temp
boolean tempWarn = false;

OneWire oneWire(tempPin); // Create OneWire instance for temp sensor
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

void tempUpdate() { //Update temp and display
  sensors.requestTemperatures(); //Get temp reading

  if (tempUnit == 'F') {//Set to Fahrenheit
    temp = sensors.getTempFByIndex(0);
  }//Set temp from first sensor
  else if (tempUnit == 'C') { //Set to Celsius if C or something else
    temp = sensors.getTempCByIndex(0);
  }//Set temp from first sensor

  //Figure low and high
  if (tempHi <= temp && temp < 100) {
    tempHi = temp;
    }
  if (tempLo > temp && temp > 0) {
    tempLo = temp;
    }

  tNeg = isNegative(temp); //If negative temp make it positive so it will fit on the display.

  if (isNegative(temp)) {
    temp = temp * -1;
  }

  #if tempWarnEnable
    if (temp > tempWarnHi || temp < tempWarnLo) {
      tempWarn = true;
      additionalWarn(); //Run additional temp warning commands
    } else {
      tempWarn = false();
    }
  #endif
}

  void tempRngRst() {
    tempHi = temp;
    tempLo = temp;
  }

void tempSetup() { //Do all temp setup in one function
  sensors.begin(); //Start sensor lib
  tempUpdate(); //Update temp
  tempRngRst(); //Reset temp min/max range
  #if serialCommands
    cmdAdd("temprst",tempRngRst);
    
  #endif
}
