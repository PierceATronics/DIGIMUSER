#ifndef TREMOLO_H
#define TREMOLO_H

class tremolo
{

private:
	float index;	//time index of the sine wave
	float tremo;	//the effect 
	float y;	//the final value after mixing z with the input

public:
	float run(float in, float a);	//function used to apply effect

};


#endif
