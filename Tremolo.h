#include "AudioSteam.h"

#ifndef TREMOLO_H
#define TREMOLO_H


class tremolo : public AudioStream
{

private:
	float index;	//time index of the sine wave
	float tremo;	//the effect 
	float y;	//the final value after mixing z with the input
	audio_block_t *inputQueueArray[2]; //the array, x = number of inputs your object will support

public:
	AudioEffectTemplate() : AudioStream(2, inputQueueArray); //x(2) = number of inputs your object will support
															//inputQueueArray = an array of audio block pointters used for the inputs
	virtual void update(void); //the library will call your update function every 128 samples, or about every 2.0 ms
	float run(float in, float a);	//function used to apply effect

};


#endif
