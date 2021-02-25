//object definition

#include "AudioStream.h"

//create new object class that inherits lib functionality from AudioStream
class AudioEffectTempl : public AudioStream
{

public:
	//: initializes AS constructor
	AudioEffectTempl() : AudioStream(1, inputQueueArray);//(# of inputs to support, arrayof audio block pointersfor inputs )
	virtual void update(void);//gets called avery 128 samples

private:
	audio_block_t *inputQueueArray[1];//

};


//update()
//must perform all objects audio processing:

//audio_block_t
//data[]: array of 16 bit integers representing the audio
//32-bit aligned in memory, therefore pairs can be fetched by type casting the address to 32bit data

//myblock pointer
//myblock->data[0] to access first audio samples
//data[] 