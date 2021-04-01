#pragma once

#include <Arduino.h>
#include "AudioStream.h"
//#include <Audio.h>

class Distortion_Effect : public AudioStream
{

public:
	Distortion_Effect(void) : AudioStream(1, inputQueueArray) {} //x(2) = number of inputs your object will support

	float begin();
	virtual void update(void);	//the library will call your update function every 128 samples, or about every 2.0 ms

	boolean setGain(float _gain);

	//convert an int16 (2's comp) to float, the output float is in range [-1.0, 1.0];
	float int16_to_float_normalized(int16_t a);

	//convert a float to int16 (2's comp).
	int16_t float_to_int16(float a);

	//float run(float in, float a);	//function used to apply effect

private:

	float dist;
	float a = 0;
	audio_block_t* inputQueueArray[1]; //the array, x = number of inputs your object will support

};
