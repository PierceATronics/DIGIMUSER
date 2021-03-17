#include <math.h>
#include "Tremolo.h"

//in = input signal from ADC
//a = value to be modified by pot, in this case the mix used in y

#define PI 3.14159265358979323846

float tremolo::run(float in, float a)
{
	
	

}
void tremolo::update(void) 
{
	audio_block_t* block;

	block = receiveWriteable(); //allocate(); is used on Teensy Example
	
	if (block) {
		for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
			//creating the effect
			tremo = (1 + (a * sinhf(40 * PI * i))); // a = intensity, i = index of the sine wave
			float audio_sample = this->int16_to_float_normalized(block->data[i]);
			//applying effect to the incoming adc data
			block->data[i] = this->float_to_int16(tremo * audio_sample);
		}
	}
		

	tremolo::transmit(block);
	tremolo::release(block);


}



//both of these are stolen from Pierce's Amplify code
float tremolo::int16_to_float_normalized(int16_t a) {

	float b = (float)a / 32767.0;
	return(b);

}

//input float must be in range [-1.0, 1.0]
int16_t tremolo::float_to_int16(float a) {

	if (a > 1.0) a = 1.0;
	else if (a < -1.0) a = -1.0;
	int16_t b = (int16_t)(a * 32767.0);
	return(b);
}