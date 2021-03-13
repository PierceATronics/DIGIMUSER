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

        boolean begin(short _amplification);

        virtual void update(void);

    private:

        uint32_t *amplification;
        audio_block_t *inputQueueArray[1];

};
