# Arduino Aquarium Controller
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




Commands:

	ledr <val> | 0-255
	ledg <val> | 0-255
	ledb <val> | 0-255
	ledw <val> | 0-255
	colorset <R val> <G val> <B val> <W val> <Brightness val> <LED State <val> | 0-255, 0-255, 0-255, 0-255, 0-255, 0-1

Usage Info:

	Set values under "//Pin Connections", "//Colors", and "//Various Configs".
	
