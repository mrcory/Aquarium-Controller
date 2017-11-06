//Tempurature Functions
//Assign ONE_WIRE_BUS

#define tempEnabled true

#include <OneWire.h>
#include <DallasTemperature.h>

const int ONE_WIRE_BUS = 12; //Data wire pin
float temp;

OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); //// Pass our oneWire reference to Dallas Temperature.

void tempUpdate() { //Update temp and display
  sensors.requestTemperatures(); //Get temp reading
  temp = sensors.getTempFByIndex(0); //Set temp from first sensor

  /*Display
  display.clearDisplay(); //Clean the Screen
  display.setCursor(5,5); //Set cursor location
  display.setTextSize(5); //Make it large
  display.print("Temperature: ");
  display.print(temp);
  display.print("°F");
  display.setTextSize(1); //Now, turn it back down*/
}
