# Aquarium-Controller
4 Channel led controller and aquarium info display.

Can be used without the display and temperature probe as just an led controller. (Version 1.3-dev)

This is a project for my aquirium. It is a 4 channel (RGBW) controller and thermometer.
I am currently running this on a Mega 2560.

Fritzing picture is for my current circut design.

<<<<<<< HEAD
Libraries Used:
	#include <TimeLib.h>
	#include <Wire.h>
	#include <SPI.h>
	#include <Adafruit_GFX.h>
	#include <Adafruit_SSD1306.h>
	#include <EEPROM.h>
	#include <AnalogButtons.h>
=======
Libraries Used:  
	#include <TimeLib.h>  
	#include <Wire.h>  
	#include <SPI.h>  
	#include <Adafruit_GFX.h>  
	#include <Adafruit_SSD1306.h>  
	#include <EEPROM.h>  
	#include <AnalogButtons.h>  
>>>>>>> d3005a52e5b197f21ff2b5ca76ac30d6b6c6337c

Features:
  
  LED Controller
    
    Color Setting  
    On/off timer  
    Fade timer (With RTC support)  
    
  Display
    
    Temperature display
	
	Show max and minimum temperature recorded

  Other
	
	Controllable via serial monitor

Hardware Used

	x1 Arduino Mega 2560
	x4 IRLB8743PBF
	x4 10Kohm Resistors
	x1 DS18B20 (Waterproof)
	x1 I2C OLED SSD1306 (128x64)
	x1 Whatever Case (I will be 3d printing one after internal hardware is final.)
	(More to be listed)
	
Time Keeping Hardware
	DS3231
	DS1307
	GPS++ compatible hardware (Mega Only)
	
Commands:

	led <val> <val2> | <val> 0=Red 1=Green 2=Blue 3=White 4=Brightness <val2> 0-255 (Set individually)
	led <val> <val2> <val3> <val4> <val5> | <val>Red <val2>Green <val3>Blue <val4>Brightness [0-255] (Set all at once)
	
	ledpower | Turn leds on and off
	ledpowernow | Turn leds on and off instantly
	
	screen <val> | Change screen display

Usage Info:

	Set values under "//Pin Connections", "//Colors", and "//Various Configs".
	
Just some functions

        drawHBar(x,y,height,width,percentage) This uses the Adafruit graphics library
