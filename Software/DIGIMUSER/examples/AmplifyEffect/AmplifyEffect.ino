/*
MIT License

Copyright (c) 2020 David Walker-Howell

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
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
