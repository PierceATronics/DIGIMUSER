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

//These are the number of samples to delay for each iir comb filter
//t_delay = M / fs
#define M_DELAY_1   2048
#define M_DELAY_2   2944
#define M_DELAY_3   3968
#define M_DELAY_4   5120

//Used to allocate memory to save delayed audio samples in audio_block_t blocks.
#define TOTAL_NUM_DELAYED_BLOCKS  (M_DELAY_4/AUDIO_BLOCK_SAMPLES)


class Reverb : public AudioStream {

    public:

        //Default Constructor
        Reverb();

        ~Reverb();
        boolean begin();

        virtual void update(void);

        //Control the attenuation factor g for the IIR Comb filters.
        void set_attenuation_factor(int16_t _atten);

    private:

        audio_block_t *input_queue_array[1];

        //Holds the delayed audio samples for reverb.
        //Set using malloc in constructor;
        audio_block_t *delayed_blocks[TOTAL_NUM_DELAYED_BLOCKS];
        
        int delayed_block_pos = 0;
        int delay_amounts[4];
        int delay_amount_offsets[4];

        //Assuming 15-fractional bits
        int16_t C[4] = {0x2000, 0x2000, 0x2000, 0x2000}; //0.25
        int16_t g[4] = {0x4000, 0x4000, 0x4000, 0x4000}; //0.50 (attenuation factors);

        //Allocates the memory for delay blocks.
        void _init_delayed_blocks();

        //Helper function to copy audio_blocks
        void _copy_audio_block_t(audio_block_t *src, audio_block_t *dst);

};
