#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include<Wire.h>

float Rg = 0.0f;
float Vin = 5.0f;
float Vout = 0.0f;
float Rref = 677000;
float analogInput = 0.0;      //define analog input check for kind of addressing it takes

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

byte package[32];

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

 //unsigned long Time1 = 0;
 //unsigned long Time2 = 0;
void setup() {
  // put your setup code here, to run once:
    //analogReadResolution(10);  
    Serial.begin(9600);
    radio.begin();
    radio.setRetries(10, 15);
    radio.setDataRate(RF24_250KBPS);
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();

    // setting up OLED
    
   pinMode(analogInput, INPUT);
   display.begin(SSD1306_SWITCHCAPVCC, 0X3C);//INTIALIZE WITH THE I2C ADDR 0X3C (FOR THE 128X32)
   display.clearDisplay();//clear the buffer
   display.setTextSize(2);//text display voltmeter
   display.setTextColor(WHITE);
   display.setCursor(0,0);
   display.print("W S M\n");
   display.display();
   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.print("Rg = \n");
   display.display();
   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.print("Vout = ");
   display.display();
   Serial.println(" Starting Measurement "); 
}

void loop() {
  // put your main code here, to run repeatedly:
  // code for calculating variable resistance using voltage follower
  float analogInput=analogRead(A1);
  float Vout = (Vin * analogInput)/4096; // 1024 for arduino uno, converting 5v into digital values
  float Rg = (Rref* ((Vin/Vout)-1));//formula for calculating variable resistance 

  
    Serial.println("***starting to send***");//print before copying and transmiting
    
    memcpy( package, &Rg,  sizeof( Rg ) );//copy data in the form of a package 
    radio.write(package, sizeof(package));// write the pacakage into the channel 

   //Time1 = millis();
   //Serial.println(Time1);
  // code for running cotinuous values on OLED
  display.setTextSize(1); //text display voltmeter
  display.setTextColor(WHITE, BLACK);
  display.setCursor(50,16);
  display.print(Rg);
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(50, 24);
  display.print(Vout);
  display.display();
  Serial.println(Vout);
  Serial.println(Rg);
  //Time2 = millis();
  //Serial.println(Time2);
  delay(1000);
}
