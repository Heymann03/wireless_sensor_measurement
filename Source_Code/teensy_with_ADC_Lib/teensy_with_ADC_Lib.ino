#include <ADC.h>
#define MAX_AVG   200

float Rg = 0.0f;
float Vin = 3.3f;
float Vout = 0.0f;
float Rref = 677000.0f;

int _count = 0;
float Ravg = 0;
float longsize = 1024;
bool _available_avg = false;

float values[ MAX_AVG ];

ADC *adc = new ADC(); // adc object;

void setup()
{
  pinMode(A1, INPUT);
  
  adc->setReference(ADC_REFERENCE::REF_3V3, ADC_0);
  adc->setAveraging(32); // set number of averages
  adc->setResolution(16); // set bits of resolution
  adc->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_LOW_SPEED);
  adc->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED);
  
  Serial.begin(38400);
  delay( 5000 );

}
void loop()                     
{
  float Analoginput = ( (float) adc->analogRead( A1, ADC_0 ) );
  
  float Vout = (Vin * ( (float)Analoginput))/( (float) adc->getMaxValue(ADC_0));
  float Rg = (Rref * ((Vin / Vout) - 1));

  if( _count++ < MAX_AVG )
  {
    values[ _count++ ] = Analoginput;
  }
  else
  {
    _count = 0;
    _available_avg = true;
  }

  if( _available_avg )
  {
    float Vavg = 0;
    for( int i = 0; i < MAX_AVG; i++ )
      Vavg = Vavg + values[ i ];

    Serial.println( (Vavg/MAX_AVG) );
  }

  delay(10);
}
