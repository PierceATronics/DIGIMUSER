#include <math.h>
#include "Tremolo.h"

//in = input signal from ADC
//a = value to be modified by pot, in this case the mix used in y

#define PI 3.14159265358979323846

float tremolo::run(float in, float a)
{
	//need to increase each time to increment through the sine wave
	index = index + 1;

	//effect
	tremo = (1 + (a * sinhf(40 * PI * index)));

	//applying effect to the incoming adc data
	return y = tremo * in;

}