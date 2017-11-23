//Original Code from http://forum.arduino.cc/index.php/topic,22301.0.html
//Author: Coding Badly
//Added some slight modification to work

float RTCtemp() {
  //temp registers (11h-12h) get updated automatically every 64s
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x11);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 2);
  int temp3231;
  
  if(Wire.available()) {
  int  tMSB = Wire.read(); //2's complement int portion
  int  tLSB = Wire.read(); //fraction portion
  
    temp3231 = ((((short)tMSB << 8) | (short)tLSB) >> 6) / 4.0;
    temp3231 = (temp3231 * 1.8) + 32.0; // Convert Celcius to Fahrenheit
  return temp3231;
  
  }
  else {
    //oh noes, no data!
  }
  
return temp3231;
}
