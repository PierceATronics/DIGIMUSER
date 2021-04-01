#pragma once

//#ifndef FLANGER_H
//#define FLANGER_H
#include <Arduino.h>
#include "AudioStream.h"
//#include <Audio.h>



class Flanger_Effect : public AudioStream{

public:
	Flanger_Effect(void) : AudioStream(1, inputQueueArray){} //x(2) = number of inputs your object will support
															//inputQueueArray = an array of audio block pointters used for the inputs
	float begin();	//function used to apply effect
	virtual void update(void); //the library will call your update function every 128 samples, or about every 2.0 ms

	boolean setGain(float _gain);

	//convert an int16 (2's comp) to float, the output float is in range [-1.0, 1.0];
	float int16_to_float_normalized(int16_t a);

	//convert a float to int16 (2's comp).
	int16_t float_to_int16(float a);


private:

	float index = 0;	//time index of the sine wave
	float flange;	//the effect
	float y;	//the final value after mixing z with the input
	//int index = 0;
	float a = 0;

	float Fc = 15.0;
	float Fs = 44100.0;
	audio_block_t *inputQueueArray[1]; //the array, x = number of inputs your object will support


};
