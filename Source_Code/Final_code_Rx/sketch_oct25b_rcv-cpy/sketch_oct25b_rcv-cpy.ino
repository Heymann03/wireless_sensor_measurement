#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

byte package[32];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setRetries(10, 15);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.println("***Starting to receive***");
}
void loop() {
  
  char text[16] = "";
  float var;
  if (radio.available()) {
    radio.read(&text, sizeof(text));
    radio.read( package, sizeof( package ) );
    memcpy(  &var, package, sizeof( var ) );
    //decode
    
    
    Serial.println(text);
    delay(100);
    Serial.println( var );
   
//    char text[32] = "";
 //  radio.read(&text, sizeof(text));
//    int x ;
//    radio.read(&x, sizeof(x));
//    Serial.println(x);
//    
  //Serial.println(text);
  delay(1000);
  }
}
