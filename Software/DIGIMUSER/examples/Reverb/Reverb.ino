#include "Reverb.h"
#include <Audio.h>

AudioOutputI2S     cs4344_dac;
AudioInputI2S      cs5343_adc;
Reverb reverb;

//Connect the output of the ADC to the input of the digital amplifier fx
AudioConnection   connection_1(cs5343_adc, 0, reverb, 0);
//Connect the output of the amplifier fx to the input of the DAC.
AudioConnection   connection_2(reverb, 0, cs4344_dac, 0);

void setup(){

  AudioMemory(30);
}


void loop(){
  
}
