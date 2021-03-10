//////////////////////////////////////////////////////////////////////////////////
// Company: DIGIMUSER(Team 15)
// Engineer: David Pierce Walker-Howell
// 
// Create Date: 03/01/2021
// Design Name: 
// Module Name: cs5343_test
// Project Name: Vocal Effects Processor
// Target Devices: Teensy 4.0
// 
// Description: 
// This code is used to test that the CS5343 ADC is functional. This test expects
// the CS4344 to have already been completed successfully (see cs4344_test.ino). The
// test is performed by passing the input signal from the ADC to the output of the 
// DAC.
// 
//
// Additional Comments:
//     This test uses the provide Teensyduino Audio library. The resolution used
//     is thus 16-bits. 
// 
//////////////////////////////////////////////////////////////////////////////////
#include <Audio.h>

int led_pin = 13;

AudioOutputI2S    cs4344_dac;
AudioInputI2S     cs5343_adc;

//Connect channel 1 of the ADC to output to channel 1 of the DAC.
AudioConnection   patch_cord(cs5343_adc, 0, cs4344_dac, 0);

void setup(){

  //Setup the led pin to blink
  pinMode(led_pin, OUTPUT);

  AudioMemory(10);
  
}

void loop(){
  digitalWrite(led_pin, HIGH);
  delay(500);
  digitalWrite(led_pin, LOW);
  delay(500);
}
