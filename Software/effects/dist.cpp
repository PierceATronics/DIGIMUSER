#include <math.h>
#include <dist.h>

//in = input signal from ADC
//a = value to be modified by pot, in this case the gain

float dist::run(float in, float a) 
{

	return (in / fabsf(in)) * (1 - expf((in / fabsf(in)) * a * in));

}