//Config stuff overflow

float fadeStep = 5; //Increase/Decrease per step (Will be properly set based on fadeTime
boolean enableTimer = true; //Disable or enable timer
int crossFade = 5; //Crossfade time in seconds per step

//Enable or disable serial commands
#define serialCommands true //Disable to save sram and flash space
#define serialBypass true 

//Enable/disable Temperature
#define tempEnable true
#define ambientAir false //Is there a second DS18b20 for air temp? (Not coded)

const int tempTime = 10; //Temp update interval in seconds 0-255

//Enable/disable Screen
#define screenEnable true

//Choose a screen
#define screenOLED false
#define screenTFT true

//TFT Settings
int tft_brightness = 20; //0-255 Controls a pwm pin
const int tft_pin = 2; //Backlight Pin
const int tftRotation = 1; //Rotate the TFT

//OLED Settings
#define oled_width 128
#define oled_height 64
const int displayAddress = 0x3c; //Display i2c address (Woking with my ebay oled)



//Enable WIFI (We are using Blynk
#define wifiEnable true
#define BLYNK_PRINT Serial //Get feedback from Blynk via Serial
int connectTimeout = 15; //Timeout to limit reconnection attempts by blynk. (Doesn't count initial connection)


//ESP Serial and Baud
#define espSerial Serial3
#define espBaud 9600

//Blynk server and port
#define blynk_server "blynk.mrcory.net"
//#define blynk_ip IPAddress(192,168,254,1)
#define blynk_port 8080 //8442 if using Blynk Cloud

//Disable or Enable Temperature warning
#define tempWarnEnable false

//Disable or Enable Water Fill
//Requires wifi to trigger. Some setup work to allow code to work without wifi is included.
#define waterFillEnable true

#if tempWarnEnable //If above is true, this will be included in the program.
//Add aditional functions to be run when temperature warning has been triggered.
//Maybe a light or a buzzer or a siren
void additionalWarn() {
  //Fill in here
}
#endif

#if waterFillEnable //If water fill is enabled define these
#define waterFill A2 //Water control pin
#define waterSenseLo 10 //Water sensor pin
#define waterSenseHi A9 //Upper water sensor
const int senseMode = 1; //1 for single sensor (Upper) 2 for dual sensor mode (Upper and lower)

#define pumpControl A1 //Pump control pin

unsigned long drainTime = 360; //seconds to drain timeout
unsigned long fillTime = 900; //seconds to fill timeout
#endif
