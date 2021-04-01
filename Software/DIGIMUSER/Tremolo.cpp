#include <math.h>
#include "Tremolo.h"

//in = input signal from ADC
//a = value to be modified by pot, in this case the mix used in y


//#define PI 3.14159265358979323846

//float a = 0.75;//0-1 DEPTH

float Tremolo_Effect::begin()//run (float in, float a)
{
	return (1.0);

}

void Tremolo_Effect::update(void)
{
	audio_block_t* block;

	block = receiveWritable(); //allocate(); is used on Teensy Example

	if (block) {
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
			//creating the effect

			if(this->index < (Fs/Fc))//Fs/Fc = 44100/5
			{
				this->index +=1;
			}
			else{
				this->index = 0;
			}

			// a = intensity, i = index of the sine wave
			tremo = (1.0 + (this->a * sinf((2.0 * PI *index * (Fc/Fs))))); // 40.0 = frequency 0-20Hz range
			//tremo = (1.0 + (a * sinf((2.0 * PI *index)*10 * i))); // 40.0 = frequency 0-20Hz range

			//tremo = (1-a)+a * sin()
			float audio_sample = this->int16_to_float_normalized(block->data[i]);
			//applying effect to the incoming adc data
			block->data[i] = this->float_to_int16((tremo )* audio_sample);//.25
		}


	Tremolo_Effect::transmit(block);

	Tremolo_Effect::release(block);
	}
}


boolean Tremolo_Effect::setGain(float _gain){
	this->a = _gain;
	return EXIT_SUCCESS;
}


//both of these are stolen from Pierce's Amplify code
float Tremolo_Effect::int16_to_float_normalized(int16_t a) {

	float b = (float)a / 32767.0;
	return(b);

}

//input float must be in range [-1.0, 1.0]
int16_t Tremolo_Effect::float_to_int16(float a) {

	if (a > 1.0) a = 1.0;
	else if (a < -1.0) a = -1.0;
	int16_t b = (int16_t)(a * 32767.0);
	return(b);
}
