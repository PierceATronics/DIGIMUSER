//This header file will define the I2S input and output classes


#ifndef i2s_h_
#define i2s_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "DMAChannel.h"


class OutI2S : public AudioStream
{
public:
	OutI2S(void) : AudioStream(2, inputQueueArray) { begin(); }
	virtual void update(void);
	void begin(void);
	friend class AudioInputI2S;

protected:
	OutI2S(int dummy): AudioStream(2, inputQueueArray) {} // to be used only inside OutI2Sslave !!
	static void config_i2s(void);
	static audio_block_t *block_left_1st;
	static audio_block_t *block_right_1st;
	static bool update_responsibility;
	static DMAChannel dma;
	static void isr(void);
private:
	static audio_block_t *block_left_2nd;
	static audio_block_t *block_right_2nd;
	static uint16_t block_left_offset;
	static uint16_t block_right_offset;
	audio_block_t *inputQueueArray[2];
};
#endif
////////////////////////////////////////////////
/////Input I2S goes here