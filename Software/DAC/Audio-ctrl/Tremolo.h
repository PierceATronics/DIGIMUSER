#pragma once

//#ifndef TREMOLO_H
//#define TREMOLO_H
#include <Arduino.h>
#include "AudioStream.h"
//#include <Audio.h>



class Tremolo_Effect : public AudioStream{

public:
	Tremolo_Effect(void) : AudioStream(1, inputQueueArray){} //x(2) = number of inputs your object will support
															//inputQueueArray = an array of audio block pointters used for the inputs
	float begin();	//function used to apply effect
	virtual void update(void); //the library will call your update function every 128 samples, or about every 2.0 ms
	
	boolean setGain(float _gain);
	
	//convert an int16 (2's comp) to float, the output float is in range [-1.0, 1.0];
	float int16_to_float_normalized(int16_t a);

	//convert a float to int16 (2's comp).
	int16_t float_to_int16(float a); 


private:
	float index;	//time index of the sine wave
	float tremo;	//the effect 
	float y;	//the final value after mixing z with the input
	audio_block_t *inputQueueArray[1]; //the array, x = number of inputs your object will support


};


//#endif
