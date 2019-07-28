/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
int in3=2;
void setup() {
  pinMode(in3,OUTPUT);
  pinMode(1,OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  
  if (radio.available()) {
    digitalWrite(1,LOW);
    int temp = 0;
    radio.read(&temp, sizeof(temp));
    Serial.println(temp);
    if(temp == 1)
    {
      Serial.print("Hello");
      digitalWrite(1,HIGH);
      digitalWrite(in3, HIGH);
    }
    if(temp == 0)
    {
      digitalWrite(in3,LOW);
          }
  }
}
