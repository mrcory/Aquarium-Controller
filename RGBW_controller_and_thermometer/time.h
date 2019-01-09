//Moved time stuff from ino

#if ds3231 || ds1307 //If ds3231 or ds1307 being used, create proper timeUpdate function
  DateTime timeNow;
    void updateTimeNow() {
      timeNow = RTC.now();
      setTime((timeNow.hour() + utcOffset),timeNow.minute(),timeNow.second(),timeNow.month(),timeNow.day(),timeNow.year());
      if (DST) {adjustTime(3600);} //Adjust time for DST
    }
#elif gpsRtc
  TinyGPSPlus GPS; //If using GPS for time decare as RTC
    void updateTimeNow() {
      if (GPS.time.isValid() == 1) {
        int _utcAdjust = GPS.time.hour() + utcOffset;
        if (DST) {_utcAdjust++;} //Adjust time for DST
        if (isNegative(_utcAdjust)) {_utcAdjust = (_utcAdjust + 24);}
        setTime(_utcAdjust,GPS.time.minute(),GPS.time.second(),GPS.date.month(),GPS.date.day(),GPS.date.year());
        
        Serial.print("GPS Time: ");
        Serial.print(GPS.time.hour());
        Serial.print(":");
        Serial.print(GPS.time.minute());
        Serial.print(":");
        Serial.println(GPS.time.second());
  
        Serial.print("Arduino Time: ");
        Serial.print(hour());
        Serial.print(":");
        Serial.print(minute());
        Serial.print(":");
        Serial.println(second());
      } else {
        Serial.println(F("GPS Time not valid!"));
      }
    }
#elif blynkRtc

#else
  #error "No RTC defined. Check config.h"
    
#endif
