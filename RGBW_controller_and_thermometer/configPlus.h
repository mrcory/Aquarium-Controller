//Config stuff overflow

float fadeStep = 5; //Increase/Decrease per step (Will be properly set based on fadeTime
boolean enableTimer = true; //Disable or enable timer
int crossFade = 5; //Crossfade time in seconds per step

//Enable or disable serial commands
#define serialCommands true //Disable to save sram and flash space

//Enable/disable Temperature
#define tempEnable true
#define ambientAir false //Is there a second DS18b20 for air temp?

//Enable/disable Screen
#define screenEnable true

//Choose a screen
#define screenOLED false
#define screenTFT true

//TFT Settings
int tft_brightness = 20; //0-255 Controls a pwm pin
int tft_pin = 2; //Backlight Pin
const int tftRotation = 3; //Rotate the TFT

//OLED Settings
#define oled_width 128
#define oled_height 64
const int displayAddress = 0x3c; //Display i2c address (Woking with my ebay oled)



//Enable WIFI (We are using Blynk
#define wifiEnable true



//ESP Serial and Baud
#define espSerial Serial3
#define espBaud 115200

//Blynk server and port
#define blynk_server "blynk.mrcory.net"
//#define blynk_ip IPAddress(192,168,254,1)
#define blynk_port 8080 //8442 if using Blynk Cloud

//Disable or Enable Temperature warning
#define tempWarnEnable true

//Disable or Enable Water Fill
#define waterFillEnable true

#if tempWarnEnable //If above is true, this will be included in the program.
//Add aditional functions to be run when temperature warning has been triggered.
//Maybe a light or a buzzer or a siren
void additionalWarn() {
  //Fill in here
}
#endif

#if waterFillEnable //If water fill is enabled define these
int waterPin = A1; //Water control pin
int waterSense = A2; //Water sensor pin
int waterSense2 = A3; //Upper water sensor

int pumpControl = A4; //Pump control pin

int waterTimeMin = 0;
int waterTimeMax = 1000;
#endif
