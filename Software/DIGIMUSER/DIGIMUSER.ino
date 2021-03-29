#include "Effects.h"

const int pot1_pin = A5;

AudioOutputI2S     cs4344_dac;
AudioInputI2S      cs5343_adc;
Reverb reverb;

//Connect the output of the ADC to the input of the digital amplifier fx
AudioConnection   connection_1(cs5343_adc, 0, reverb, 0);
//Connect the output of the amplifier fx to the input of the DAC.
AudioConnection   connection_2(reverb, 0, cs4344_dac, 0);

void setup(){

  AudioMemory(30);

  //Resolution to read the potentiometer
  analogReadResolution(12);
}


void loop(){
  float pot1_val = float(analogRead(pot1_pin)) / 4096.0;
  
}
