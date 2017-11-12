//Tempurature Functions 
//Assign ONE_WIRE_BUS



#include <OneWire.h>
#include <DallasTemperature.h>

const int ONE_WIRE_BUS = 12; //Data wire pin
float temp;
int tNeg = 0; //0 is positive 1 means negative temp

OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); //// Pass our oneWire reference to Dallas Temperature.

void tempUpdate() { //Update temp and display
  sensors.requestTemperatures(); //Get temp reading

  if (tempUnit == "F") {//Set to Fahrenheit
    temp = sensors.getTempFByIndex(0);
  }//Set temp from first sensor
  else if (tempUnit == "C") { //Set to Celsius if C or something else
    temp = sensors.getTempCByIndex(0);
  }//Set temp from first sensor


  if (temp < 0) {
    tNeg = 1;  //If negative temp (like error) make it positive so it will fit on the display.
    temp = temp * -1;
  } else {
    tNeg = 0;
  }
}
