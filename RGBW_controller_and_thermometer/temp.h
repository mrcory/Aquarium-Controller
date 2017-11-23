//Tempurature Functions 
//Assign ONE_WIRE_BUS



#include <OneWire.h>
#include <DallasTemperature.h>

float temp;
float tempHi; //Max temp recorded
float tempLo; //Lowest temp recorded
int tNeg = 0; //0 is positive 1 means negative temp
String tempWarn;

OneWire oneWire(tempPin); // Create OneWire instance for temp sensor
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.



void tempUpdate() { //Update temp and display
  sensors.requestTemperatures(); //Get temp reading
  airTemp = RTCtemp(); //Get air temp from the RTC

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
    tNeg = 1;  //If negative temp make it positive so it will fit on the display.
    temp = temp * -1;
  } else {
    tNeg = 0;
  }

    //Check if temp out of safe range
    if (temp >= tempWarnHi) { 
      tempWarn = "Hi";
    }
    if (temp <= tempWarnLo) {
      tempWarn = "Lo";
    } 
}

  void tempRngRst() {
    tempHi = temp;
    tempLo = temp;
  }


