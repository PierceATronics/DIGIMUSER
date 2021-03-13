#include "AmplifyEffect.h"
#include <Audio.h>

int led_pin = 13;

AudioOutputI2S    cs4344_dac;
//AudioInputI2S     cs5343_adc;
AmplifyEffect     amplifier;
AudioSynthWaveformSine test_sine_wave;


AudioConnection     connection_1(test_sine_wave, 0, amplifier, 0);
//Connect the output of the ADC to the input of the digital amplifier fx
//AudioConnection   connection_1(cs5343_adc, 0, amplifier, 0);
//Connect the output of the amplifier fx to the input of the DAC.
AudioConnection   connection_2(amplifier, 0, cs4344_dac, 0);

const int16_t amplification = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
  AudioMemory(8);
  
  amplifier.begin(amplification);
  
  //Setup the test signal
  test_sine_wave.amplitude(0.5);
  test_sine_wave.frequency(440);
  test_sine_wave.phase(180);
  //AudioProcessorUsageMaxReset();
  //AudioMemoryUsageMaxReset();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(led_pin, HIGH);
  delay(500);
  digitalWrite(led_pin, LOW);
  delay(500);

}
