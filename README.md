# Aquarium-Controller
4 Channel led controller and aquarium info display.

This is a project for my aquirium. It is a 4 channel (RGBW) controller and thermometer.
I am currently running this on a Mega 2560.

Fritzing picture is for my current circut design.

Features:
  
  LED Controller
    
    Color Setting
    
    On/off timer
    
    Fade timer (With RTC support)
    
  Display
    
    Temperature display

  Other
	
	Controllable via serial monitor

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

	ledr <val> | 0-255
	ledg <val> | 0-255
	ledb <val> | 0-255
	ledw <val> | 0-255
	(Broken) colorset <R val> <G val> <B val> <W val> <Brightness val> <LED State <val> | 0-255, 0-255, 0-255, 0-255, 0-255, 0-1

Usage Info:

	Set values under "//Pin Connections", "//Colors", and "//Various Configs".
	
