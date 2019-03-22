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
#define screenEnable false

//Choose a screen
#define screenOLED false
#define screenTFT false

//TFT Settings
int tft_brightness = 20; //0-255 Controls a pwm pin
int tft_pin = 2; //Backlight Pin
const int tftRotation = 1; //Rotate the TFT

//OLED Settings
#define oled_width 128
#define oled_height 64
const int displayAddress = 0x3c; //Display i2c address (Woking with my ebay oled)



//Enable WIFI (We are using Blynk
#define wifiEnable true
#define BLYNK_PRINT Serial //Get feedback from Blynk via Serial



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
//Requires wifi to trigger. Some setup work to allow code to work without wifi is included.
#define waterFillEnable false

#if tempWarnEnable //If above is true, this will be included in the program.
//Add aditional functions to be run when temperature warning has been triggered.
//Maybe a light or a buzzer or a siren
void additionalWarn() {
  //Fill in here
}
#endif

#if waterFillEnable //If water fill is enabled define these
#define waterFill A1 //Water control pin
#define waterSenseLo A2 //Water sensor pin
#define waterSenseHi A3 //Upper water sensor
static byte senseMode = 1 //1 for single sensor (Upper) 2 for dual sensor mode (Upper and lower)

#define pumpControl A4 //Pump control pin

#define waterTimeMin 0
#define waterTimeMax 1000
#endif
