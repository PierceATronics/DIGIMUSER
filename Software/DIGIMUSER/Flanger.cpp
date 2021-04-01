#include <math.h>
#include "Flanger.h"


float Flanger_Effect::begin()//run (float in, float a)
{
	return (1.0);

}

void Flanger_Effect::update(void)
{

  audio_block_t* block;

  block = receiveWritable(); //allocate(); is used on Teensy Example

  if (block) {
    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {




    }
  Flanger_Effect::transmit(block);

  Flanger_Effect::release(block);
  }

}


boolean Flanger_Effect::setGain(float _gain){
	this->a = _gain;
	return EXIT_SUCCESS;
}


float Flanger_Effect::int16_to_float_normalized(int16_t a) {

	float b = (float)a / 32767.0;
	return(b);

}

//input float must be in range [-1.0, 1.0]
int16_t Flanger_Effect::float_to_int16(float a) {

	if (a > 1.0) a = 1.0;
	else if (a < -1.0) a = -1.0;
	int16_t b = (int16_t)(a * 32767.0);
	return(b);
}
