#include <ADC.h>
#define MAX_AVG   100

float Rg = 0.0f;
float Vin = 5.0f;
float Vout = 0.0f;
float Rref = 677000.0f;

int _count = 0;
float Ravg = 0;
float longsize = 1024;

ADC *adc = new ADC(); // adc object;

  void setup()
{                
  Serial.begin(38400);
  analogReadResolution(16);
}


float Vavg = 0;

void loop()                     
{
  
//Serial.println(); 
long Analoginput = analogRead(A1);
//Serial.println(Analoginput);
float Vout = (Vin * ( (float)Analoginput))/longsize;
//Serial.println(Vout);
float Rg = (Rref * ((Vin / Vout) - 1));

  if( _count++ > MAX_AVG )
  {
    Serial.println( Vavg );
    _count = 0;
    Vavg = 0;
  }
  else
  {
    Vavg = Vavg + (Vout)/MAX_AVG ;
  }
  
  //Serial.println(Rg);
  
  delay(1);
}
