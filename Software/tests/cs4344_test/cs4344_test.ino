//////////////////////////////////////////////////////////////////////////////////
// Company: DIGIMUSER(Team 15)
// Engineer: David Pierce Walker-Howell
// 
// Create Date: 03/01/2021
// Design Name: 
// Module Name: cs4344_test
// Project Name: Vocal Effects Processor
// Target Devices: Teensy 4.0
// 
// Description: 
// This code is used to test that the CS4344 DAC IC works. Validation is successful
// if the DAC outputs a 440Hz sine-wave.
// 
//
// Additional Comments:
//     This test uses the provide Teensyduino Audio library. The resolution used
//     is thus 16-bits for the DAC. 
// 
//////////////////////////////////////////////////////////////////////////////////
#include <Audio.h>

int led_pin = 13;

AudioOutputI2S    cs4344_dac;
AudioSynthWaveformSine    test_sine_wave;

//Output the test signal to the first channel of the DAC.
AudioConnection           patch_cord(test_sine_wave, 0, cs4344_dac, 0);

void setup(){

  //Setup the led pin to blink
  pinMode(led_pin, OUTPUT);
  
  AudioMemory(10);

  //Setup the test signal
  test_sine_wave.amplitude(1.0);
  test_sine_wave.frequency(440);
  test_sine_wave.phase(180);
}

void loop(){
  digitalWrite(led_pin, HIGH);
  delay(500);
  digitalWrite(led_pin, LOW);
  delay(500);
}
