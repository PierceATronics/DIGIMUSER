#include <math.h>
#include "Distortion.h"

//in = input signal from ADC
//a = value to be modified by pot, in this case the gain

float Distortion_Effect::begin()//run (float in, float a)
{
	return (1.0);

}

void Distortion_Effect::update(void)
{
	audio_block_t* block;

	block = receiveWritable(); //allocate(); is used on Teensy Example

	if (block) {
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
			//creating the effect

			float audio_sample = this->int16_to_float_normalized(block->data[i]);
			dist = (audio_sample / fabsf(audio_sample)) * (1 - expf((audio_sample / fabsf(audio_sample)) * a * audio_sample));
			//applying effect to the incoming adc data
			block->data[i] = this->float_to_int16(dist);

		}

		Distortion_Effect::transmit(block);

		Distortion_Effect::release(block);
	}

}


boolean Distortion_Effect::setGain(float _gain) {
	//function to set _gain to work with dist <1, 11>
	this->a = _gain;
	return EXIT_SUCCESS;
}

//both of these are stolen from Pierce's Amplify code
float Distortion_Effect::int16_to_float_normalized(int16_t a) {

	float b = (float)a / 32767.0;
	return(b);

}

//input float must be in range [-1.0, 1.0]
int16_t Distortion_Effect::float_to_int16(float a) {

	if (a > 1.0) a = 1.0;
	else if (a < -1.0) a = -1.0;
	int16_t b = (int16_t)(a * 32767.0);
	return(b);
}

/*
float dist::run(float in, float a)
{

	return (in / fabsf(in)) * (1 - expf((in / fabsf(in)) * a * in));

}*/
