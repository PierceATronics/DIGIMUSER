//#include "Arduino.h"
#include "AmplifyEffect.h"


boolean AmplifyEffect::begin(float _amplification){
    
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

    //Only transmit if block exists....REQUIRED!
    if(block){
      
      //Amplify each sample in the audio buffer by scalar multiplication.
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++){
          //Perform effect using floats
          float audio_sample = this->int16_to_float_normalized(block->data[i]);
          block->data[i] = this->float_to_int16(amplification * audio_sample);
      }
      
      //MUST TRANSMIT AND RELEASE BEFORE RETURNING
      AmplifyEffect::transmit(block);
      AmplifyEffect::release(block);
    }
    
}

//TODO: Set a maximum amplification.
boolean AmplifyEffect::set_amplification(float _amplification){
  this->amplification = _amplification;
  return(true);

}

float AmplifyEffect::int16_to_float_normalized(int16_t a){

  float b = (float)a / 32767.0;
  return(b);

}

//input float must be in range [-1.0, 1.0]
int16_t AmplifyEffect::float_to_int16(float a){

  if(a > 1.0) a = 1.0;
  else if(a < -1.0) a = -1.0;
  int16_t b = (int16_t) (a * 32767.0);
  return(b);
}
