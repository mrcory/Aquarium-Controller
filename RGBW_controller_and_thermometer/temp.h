//Tempurature Functions 
//Assign ONE_WIRE_BUS



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
  if (tempHi <= temp) {
    tempHi = temp;
    }
  if (tempLo >= temp) {
    tempLo = temp;
    }

  if (temp < 0) {
    tNeg = true;  //If negative temp make it positive so it will fit on the display.
    temp = temp * -1;
  } else {
    tNeg = false;
  }

  if (tempHi >= tempWarnHi || tempLo <= tempWarnLo) {
    tempWarn = true;
  }

}

  void tempRngRst() {
    tempHi = temp;
    tempLo = temp;
  }

