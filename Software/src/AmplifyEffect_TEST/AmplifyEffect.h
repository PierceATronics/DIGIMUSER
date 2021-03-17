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
