# wireless_sensor_measurement

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE, CSN

const byte rxAddr[6] = "00001";

#define NUM_CHANNELS  1

typedef struct {
  long int td;               //4 bytes
  int data[ NUM_CHANNELS ];  //2 x 6 = 12 bytes
} SRF24_Data;

SRF24_Data  RData;
SRF24_Data* pSRData = &RData;



void setup()
{
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();
}

void loop()
{
  //const char text[] = "Hello World";
//  radio.write(&text, sizeof(text));
pSRData->td = millis();
pSRData->data[0]=analogRead(A0);
pSRData->data[1]=analogRead(A1);
pSRData->data[2]=analogRead(A2);
pSRData->data[3]=analogRead(A3);
pSRData->data[4]=analogRead(A4);
pSRData->data[5]=analogRead(A5);
pSRData->data[6]=analogRead(A6);
pSRData->data[7]=analogRead(A7);

  //long int t = millis();
  radio.write(pSRData, sizeof(SRF24_Data));
  delay(100);
