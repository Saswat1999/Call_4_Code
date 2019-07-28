/// 
///                 Arduino      SX1278_Lora
///                 GND----------GND   (ground in)
///                 3V3----------3.3V  (3.3V in)
/// interrupt 0 pin D2-----------DIO0  (interrupt request out)
///          SS pin D10----------NSS   (CS chip select in)
///         SCK pin D13----------SCK   (SPI clock in)
///        MOSI pin D11----------MOSI  (SPI Data in)
///        MISO pin D12----------MISO  (SPI Data out)
/// 

#include <SPI.h>
#include <RH_RF95.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Singleton instance of the radio driver
RH_RF95 SX1278;



void setup()
{
    Serial.begin(9600);
    while (!Serial) ; // Wait for serial port to be available
    if (!SX1278.init())
        Serial.println("init failed");lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
   lcd.setCursor(0,0);
     lcd.print("LCD ON");
    // Defaults init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
}

void loop()
{
    if (SX1278.available())
    {
        // Should be a message for us now
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);
        if (SX1278.recv(buf, &len))
        {
            //RH_RF95::printBuffer("request: ", buf, len);
            lcd.clear();
            lcd.setCursor(0,0);
            Serial.print("Receive Message: ");
            lcd.print("Receive Message: ");
            lcd.setCursor(0,1);
            lcd.print((char*)buf);
            //Serial.print("RSSI: ");
            //Serial.println(SX1278.lastRssi(), DEC);
            // Send a reply
        }
        else
        {
            Serial.println("recv failed");
        }
    }
}
