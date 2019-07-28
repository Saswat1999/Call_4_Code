#include <RadioHead.h>
#include <radio_config_Si4460.h>
#include <RHGenericDriver.h>
#include <RHGenericSPI.h>
#include <RHHardwareSPI.h>
#include <RHSPIDriver.h>
#include <RH_RF95.h>
#include <SPI.h>
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {0, 9, 3, 4}; 
byte colPins[COLS] = {5, 6, 7, 8}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

 char sensor_string[]="000#000#0";
// Singleton instance of the radio driver
RH_RF95 SX1278;
int i=0;


void setup()
{
    Serial.begin(9600);
    while (!Serial) ; // Wait for serial port to be available
   
    if (!SX1278.init())
        Serial.println("Notice:init failed");
    
    // Defaults init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
}


void loop()
{
  char customKey = customKeypad.getKey();
  if(customKey == '*')
  {
    i=0;
    Serial.println("Sending to SX1278_server");
    Serial.println(sensor_string);
    Serial.print(sizeof(sensor_string));
    // Send a message to SX1278_server
    SX1278.send(sensor_string, sizeof(sensor_string));
    Serial.println("mark0");
   // SX1278.waitPacketSent();
    Serial.println("mark1");
    // Now wait for a reply
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    Serial.println("mark2");
    
  }
  if(customKey == 'A' || customKey == 'B' || customKey == 'C' || customKey == 'D' || customKey == '0'  || customKey == '1' || customKey == '2' || customKey == '3' || customKey == '4' || customKey == '5' || customKey == '6'|| customKey == '7' || customKey == '8' ||customKey == '9' || customKey == '#')
    {
        sensor_string[i]= customKey;
        i=i+1;
    }
}
  

 
