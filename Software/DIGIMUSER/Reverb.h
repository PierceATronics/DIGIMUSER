#pragma once
#include "Arduino.h"
#include "AudioStream.h"
#include <Audio.h>

//Should be M_DELAY / AUDIO_BLOCK_SAMPLES
#ifndef M_DELAY
  #define M_DELAY 2048
#endif
#ifndef NUM_DELAYED_BLOCKS
  #define NUM_DELAYED_BLOCKS 16
#endif
class Reverb : public AudioStream {

    public:

        //Default Constructor
        Reverb();

        ~Reverb();
        boolean begin();

        virtual void update(void);

    private:

        audio_block_t *input_queue_array[1];

        //Holds the delayed samples for reverb.
        //Set using malloc in constructor;
        audio_block_t *delayed_blocks[NUM_DELAYED_BLOCKS];
        int delayed_block_pos = 0;

        //Assuming 15-fractional bits
        int16_t C = 0x2000; //0.25
        int16_t g = 0x6000; //0.75

        //Allocates the memory for delay blocks.
        void _init_delayed_blocks();

        //Helper function to copy audio_blocks
        void _copy_audio_block_t(audio_block_t *src, audio_block_t *dst);

};
