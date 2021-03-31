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
 
#include "Reverb.h"

void Reverb::update(void){

    audio_block_t *x;
    audio_block_t *delayed;
    
    x = receiveWritable();
    if(x){

        //delayed = this->delayed_blocks[this->delayed_block_pos];
        
        for(int i=0; i < AUDIO_BLOCK_SAMPLES; i++){
            
            int32_t accum = 0;
            
            //Iterate through each IIR comb filter.
            for(int j=0; j < 4; j++){
              
              // Get the delayed block corresponding to the IIR comb filters delay
              int delay_index = this->delayed_block_pos + this->delay_amount_offsets[j];
              if(delay_index >= TOTAL_NUM_DELAYED_BLOCKS){ delay_index = delay_index - TOTAL_NUM_DELAYED_BLOCKS; }
              delayed = this->delayed_blocks[delay_index];
              
              //Performs y[n] = C * x[n] - g * y[n - M]
              int32_t mult1 = (int32_t)(x->data[i]) * (int32_t)(this->C[j]);
              int32_t mult2 = (int32_t)(delayed->data[i]) * (int32_t)(this->g[j]);

              //Scale down the summation...the shorter delays get more attenuation. 
              //Through trial and error, I found this sounds really nice!
              accum = ((mult1 + mult2) >> (5-j)) + accum;
            }

            //Store the result back in x to be sent to DAC
            x->data[i] = (int16_t)(accum >> 15);
        }

        //Save the current y audio block to be used for delay.
        _copy_audio_block_t(x, this->delayed_blocks[this->delayed_block_pos]);

        //  Update the position index of which delayed block the system is at
        if(this->delayed_block_pos < TOTAL_NUM_DELAYED_BLOCKS - 1)
            this->delayed_block_pos++;
        else
            this->delayed_block_pos = 0;

        Reverb::transmit(x);
        Reverb::release(x);
    }

}

Reverb::Reverb() : Reverb::AudioStream(1, input_queue_array){

    //Allocate the memory for the delayed blocks.
    _init_delayed_blocks();

    //Delay Amounts
    this->delay_amounts[0] = M_DELAY_1 / AUDIO_BLOCK_SAMPLES;
    this->delay_amounts[1] = M_DELAY_2 / AUDIO_BLOCK_SAMPLES;
    this->delay_amounts[2] = M_DELAY_3 / AUDIO_BLOCK_SAMPLES;
    this->delay_amounts[3] = M_DELAY_4 / AUDIO_BLOCK_SAMPLES;

    for(int j=0; j < 4; j++){
      this->delay_amount_offsets[j] = this->delay_amounts[3] - this->delay_amounts[j];
    }
    
}


void Reverb::_init_delayed_blocks(){

    for(int j=0; j < TOTAL_NUM_DELAYED_BLOCKS; j++){
        this->delayed_blocks[j] = (audio_block_t*) malloc(sizeof(audio_block_t));
    }

}

void Reverb::_copy_audio_block_t(audio_block_t *src, audio_block_t *dst){

    for(int i=0; i < AUDIO_BLOCK_SAMPLES; i++){
        dst->data[i] = src->data[i];
    }

}

void Reverb::set_attenuation_factor(int16_t _atten){
  for(int i=0; i<4; i++){
    this->g[i] = _atten;
  }
}

Reverb::~Reverb(){

    //Free up the memory
    for(int j=0; j < TOTAL_NUM_DELAYED_BLOCKS; j++){
        free(this->delayed_blocks[j]);
    }
    
}
