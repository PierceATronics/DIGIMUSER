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
#include "Effects.h"

/* CHOOSE THE INPUT DEVICE
 *  INPUT_DEVICE 0 ==> CS5343 ADC
 *  INPUT_DEVICE 1 ==> USB (make sure to change USB Type to Audio under Tools -> USB Typ)e  
 */
#define INPUT_DEVICE 0

const int pot1_pin = A5;
AudioOutputI2S     cs4344_dac;

#if INPUT_DEVICE == 0
  AudioInputI2S      input_device;
#else
  AudioInputUSB      input_device;
#endif

//  Initialize the reverb effect.
Reverb reverb;

//Connect the output of the ADC to the input of the digital amplifier fx
AudioConnection   connection_1(input_device, 0, reverb, 0);
//Connect the output of the amplifier fx to the input of the DAC.
AudioConnection   connection_2(reverb, 0, cs4344_dac, 0);

void setup(){

  AudioMemory(50);

  //Resolution to read the potentiometer
  analogReadResolution(12);
}


void loop(){
  //float pot1_val = float(analogRead(pot1_pin)) / 4096.0;

  //Sample the potentiometer and cast into a 16-bits (15 fractional).
  int16_t pot1_val = (int16_t)(analogRead(pot1_pin) << 3);
  reverb.set_attenuation_factor(pot1_val);
  delay(100);
  
}
