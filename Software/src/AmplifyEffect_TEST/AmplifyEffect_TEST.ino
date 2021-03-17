//////////////////////////////////////////////////////////////////////////////////
// Company: DIGIMUSER(Team 15)
// Engineer: David Pierce Walker-Howell
// 
// Create Date: 03/14/2021
// Design Name: 
// Module Name: AmplifyEffect_TEST
// Project Name: Vocal Effects Processor
// Target Devices: Teensy 4.0
// 
// Description: 
// 
//  This code implements a simple amplification effect using the provide Audio
//  library flow structure (i.e. using AudioStreams and AudioConnections).
// 
//
// Additional Comments:
//     This example performs the amplification by converting the 16-bit twos complement
//     to floats.
// 
//////////////////////////////////////////////////////////////////////////////////
#include "AmplifyEffect.h"
#include <Audio.h>

const int led_pin = 13;
const int pot1_pin = A5;

AudioOutputI2S    cs4344_dac;
AudioInputI2S     cs5343_adc;
AmplifyEffect     amplifier;

//Connect the output of the ADC to the input of the digital amplifier fx
AudioConnection   connection_1(cs5343_adc, 0, amplifier, 0);
//Connect the output of the amplifier fx to the input of the DAC.
AudioConnection   connection_2(amplifier, 0, cs4344_dac, 0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);

  //samples per audio block
  AudioMemory(8);

  //Initialize the amplifier amplification.
  amplifier.begin(1.0);
  
  //Resolution to read the potentiometer
  analogReadResolution(12);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //Get normalized potentiometer value -> Set a the amplification.
  float pot1_val = float(analogRead(pot1_pin)) / 4096.0;
  amplifier.set_amplification(2.0 * pot1_val);
  
  //Print for debug
  Serial.println(pot1_val);
  digitalWrite(led_pin, HIGH);
  delay(50);
  digitalWrite(led_pin, LOW);
  delay(50);
  
}
