# Aquarium-Controller
4 Channel led controller and aquarium info display.

This is a project for my aquirium. It is a 4 channel (RGBW) controller and thermometer.
I am currently running this on a Mega 2560.

Fritzing picture is for my current circut design.



Features:
  
  LED Controller  
  
    Color Setting (Individual colors for 1st and 2nd timer set)  
    On/Off Timer (Single timer or split timers)  
    Fade timer (With RTC support)
    
  Display
    
    Temperature display  
    Show max and minimum temperature recorded

  Other  
  
    Controllable via serial monitor  
    Supports DS1307, DS3231 or TinuGPS++ for time keeping.

Hardware Used

	x1 Arduino Mega 2560  
	x4 IRLB8743PBF  
	x4 10Kohm Resistors  
	x1 DS3231 RTC  
	x1 DS18B20 (Waterproof)  
	x1 I2C OLED SSD1306 (128x64)  
	x1 Whatever Case (I will be 3d printing one after internal hardware is final.)  
	(More to be listed)  
	


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
