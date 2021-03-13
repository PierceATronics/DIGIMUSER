//#include "Arduino.h"
#include "AmplifyEffect.h"


boolean AmplifyEffect::begin(short _amplification){
    
    amplification = (uint32_t*) _amplification;
    boolean success;

    return(success);
}

//Called by ISR each time a new audio block is sampled.
//WRITE YOUR EFFECT IN HERE!
void AmplifyEffect::update(void){
    
    audio_block_t *block;
    short *audio_data;

    //Copy the input block from the connected source
    block = receiveWritable(0);
    
    audio_data = block->data;
    
    
    //d is used to read the audio data shorts in unin32_t, to be used by DSP library.
    uint32_t *d;
    uint32_t a, out;
    short_and_uint32_t su;
    
    for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++){
        su.short_data = block->data[i];
        //d = (uint32_t *) su.uint32_t_data;
        //a = *d;

        //the inputs for the DSP library require unsigned 32-bit integers
        //This multiplication step will only multiply the MSBS ([31:16]).
        out = multiply_16tx16t(su.uint32_t_data, *amplification);
        short *p = (short *) out;
        block->data[i] = *p;
    }
    
    //MUST TRANSMIT AND RELEASE BEFORE RETURNING
    transmit(block);
    release(block);
    return;
}
