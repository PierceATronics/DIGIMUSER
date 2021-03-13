#include "AmplifyEffect.h"

int led_pin = 13;

AudioOutputI2S    cs4344_dac;
AudioInputI2S     cs5343_adc;
AmplifyEffect     amplifier;


//Connect the output of the ADC to the input of the digital amplifier fx
AudioConnection   connection_1(cs5343_adc, 0, amplifier, 0);
//Connect the output of the amplifier fx to the input of the DAC.
AudioConnection   connection_2(amplifier, 0, cs4344_dac, 0);

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
  AudioMemory(10);

}

void loop() {
  // put your main code here, to run repeatedly:

  

}
