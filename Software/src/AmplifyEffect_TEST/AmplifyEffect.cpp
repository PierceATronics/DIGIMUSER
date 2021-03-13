//#include "Arduino.h"
#include "AmplifyEffect.h"


boolean AmplifyEffect::begin(int16_t _amplification){
    
    amplification = _amplification;
    boolean success = true;
    return(success);
}


//Called by ISR each time a new audio block is sampled.
//WRITE YOUR EFFECT IN HERE!
void AmplifyEffect::update(void){
    
    audio_block_t * block;
    //Copy the input block from the connected source
    block = receiveWritable();
    
    if(block){

      //Amplify each sample in the audio buffer by scalar multiplication.
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++){
          
          block->data[i] = (int16_t)(amplification * block->data[i]);
      }
      
      //Only transmit if block exists....REQUIRED!
      
      //MUST TRANSMIT AND RELEASE BEFORE RETURNING
      AmplifyEffect::transmit(block);
      AmplifyEffect::release(block);
      }
    
}
