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
#pragma once
#include "Arduino.h"
#include "AudioStream.h"
#include <Audio.h>

union short_and_uint32_t{
  short short_data;
  uint32_t uint32_t_data;
};

class AmplifyEffect : public AudioStream{

    public:

        //Default constructor
        AmplifyEffect(void) :  AudioStream(1, inputQueueArray) {}

        //Call to set the initial amplification
        boolean begin(float _amplification);

        virtual void update(void);

        //Set the amplification dynamically
        boolean set_amplification(float _amplification);

        //convert an int16 (2's comp) to float, the output float is in range [-1.0, 1.0];
        float int16_to_float_normalized(int16_t a);

        //convert a float to int16 (2's comp).
        int16_t float_to_int16(float a);  

    private:

        float amplification;
        audio_block_t *inputQueueArray[1];

};
