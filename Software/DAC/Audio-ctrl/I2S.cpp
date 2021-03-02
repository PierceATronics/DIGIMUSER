//includes definitions for I2S input and output



//Notes created by Angel
//in order to increas the data size, change i2s_tx_buffer and the contentsd of isr() to handle 24 bitset
//and possible the size of audio blocks fromAudioStream.h
//1 block = i2s_tx_buffer/2

#include <Arduino.h>
#include "I2S.h"
#include "memcpy_audio.h"
#include "imxrt_hw.h"//processor for teensy 4.0
//#include "DIGILib.h"
bool debugg = false;

audio_block_t * InI2S::block_left = NULL;
audio_block_t * InI2S::block_right = NULL;

audio_block_t * OutI2S::block_left_1st = NULL;
audio_block_t * OutI2S::block_right_1st = NULL;
audio_block_t * OutI2S::block_left_2nd = NULL;
audio_block_t * OutI2S::block_right_2nd = NULL;

uint16_t InI2S::block_offset = 0;

uint16_t  OutI2S::block_left_offset = 0;
uint16_t  OutI2S::block_right_offset = 0;

bool InI2S::update_responsibility = false;
bool OutI2S::update_responsibility = false;

DMAChannel InI2S::dma(false);
DMAChannel OutI2S::dma(false);
DMAMEM __attribute__((aligned(32))) static uint32_t i2s_tx_buffer[AUDIO_BLOCK_SAMPLES];
DMAMEM __attribute__((aligned(32))) static uint32_t i2s_rx_buffer[AUDIO_BLOCK_SAMPLES];


//output
void OutI2S::begin(void)
{
	dma.begin(true); // Allocate the DMA channel first

	block_left_1st = NULL;
	block_right_1st = NULL;

	config_i2s(); //turns on audio clk and sets up the I2s hardware

	CORE_PIN7_CONFIG  = 3;  //1:TX_DATA0
	
	//initiate DMA params
	dma.TCD->SADDR = i2s_tx_buffer;
	dma.TCD->SOFF = 2;
	dma.TCD->ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
	dma.TCD->NBYTES_MLNO = 2;
	dma.TCD->SLAST = -sizeof(i2s_tx_buffer);
	dma.TCD->DOFF = 0;
	dma.TCD->CITER_ELINKNO = sizeof(i2s_tx_buffer) / 2;
	dma.TCD->DLASTSGA = 0;
	dma.TCD->BITER_ELINKNO = sizeof(i2s_tx_buffer) / 2;
	dma.TCD->CSR = DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;
	dma.TCD->DADDR = (void *)((uint32_t)&I2S1_TDR0 + 2);
	dma.triggerAtHardwareEvent(DMAMUX_SOURCE_SAI1_TX);//service I2S hardware requests
	dma.enable();

	I2S1_RCSR |= I2S_RCSR_RE | I2S_RCSR_BCE;
	I2S1_TCSR = I2S_TCSR_TE | I2S_TCSR_BCE | I2S_TCSR_FRDE;

	update_responsibility = update_setup();
	dma.attachInterrupt(isr);//runs isr() when DMA controller needs more data to be copied into i2s_tx_buffer array
}


void OutI2S::isr(void)
{

	int16_t *dest;
	audio_block_t *blockL, *blockR;
	uint32_t saddr, offsetL, offsetR;

	saddr = (uint32_t)(dma.TCD->SADDR);
	dma.clearInterrupt();
	
	//block to figure which half of the buffer is used by the DMA,
	//then copues block of audio data into other half of i2s_tx_buffer
	if (saddr < (uint32_t)i2s_tx_buffer + sizeof(i2s_tx_buffer) / 2) {
		// DMA is transmitting the first half of the buffer
		// so we must fill the second half
		dest = (int16_t *)&i2s_tx_buffer[AUDIO_BLOCK_SAMPLES/2];
		if (OutI2S::update_responsibility) AudioStream::update_all();
	} else {
		// DMA is transmitting the second half of the buffer
		// so we must fill the first half
		dest = (int16_t *)i2s_tx_buffer;
	}
	
	
	blockL = OutI2S::block_left_1st;
	blockR = OutI2S::block_right_1st;
	offsetL = OutI2S::block_left_offset;
	offsetR = OutI2S::block_right_offset;

	if (blockL && blockR) {
		memcpy_tointerleaveLR(dest, blockL->data + offsetL, blockR->data + offsetR);
		offsetL += AUDIO_BLOCK_SAMPLES / 2;
		offsetR += AUDIO_BLOCK_SAMPLES / 2;
	} else if (blockL) {
		memcpy_tointerleaveL(dest, blockL->data + offsetL);
		offsetL += AUDIO_BLOCK_SAMPLES / 2;
	} else if (blockR) {
		memcpy_tointerleaveR(dest, blockR->data + offsetR);
		offsetR += AUDIO_BLOCK_SAMPLES / 2;
	} else {
		memset(dest,0,AUDIO_BLOCK_SAMPLES * 2);
	}

	arm_dcache_flush_delete(dest, sizeof(i2s_tx_buffer) / 2 );

	if (offsetL < AUDIO_BLOCK_SAMPLES) {
		OutI2S::block_left_offset = offsetL;
	} else {
		OutI2S::block_left_offset = 0;
		AudioStream::release(blockL);
		OutI2S::block_left_1st = OutI2S::block_left_2nd;
		OutI2S::block_left_2nd = NULL;
	}
	if (offsetR < AUDIO_BLOCK_SAMPLES) {
		OutI2S::block_right_offset = offsetR;
	} else {
		OutI2S::block_right_offset = 0;
		AudioStream::release(blockR);
		OutI2S::block_right_1st = OutI2S::block_right_2nd;
		OutI2S::block_right_2nd = NULL;
	}


}




void OutI2S::update(void)
{
	// null audio device: discard all incoming data
	//if (!active) return;
	//audio_block_t *block = receiveReadOnly();
	//if (block) release(block);

	audio_block_t *block;
	block = receiveReadOnly(0); // input 0 = left channel
	if (block) {
		__disable_irq();
		if (block_left_1st == NULL) {
			block_left_1st = block;
			block_left_offset = 0;
			__enable_irq();
		} else if (block_left_2nd == NULL) {
			block_left_2nd = block;
			__enable_irq();
		} else {
			audio_block_t *tmp = block_left_1st;
			block_left_1st = block_left_2nd;
			block_left_2nd = block;
			block_left_offset = 0;
			__enable_irq();
			release(tmp);
		}
	}
	block = receiveReadOnly(1); // input 1 = right channel
	if (block) {
		__disable_irq();
		if (block_right_1st == NULL) {
			block_right_1st = block;
			block_right_offset = 0;
			__enable_irq();
		} else if (block_right_2nd == NULL) {
			block_right_2nd = block;
			__enable_irq();
		} else {
			audio_block_t *tmp = block_right_1st;
			block_right_1st = block_right_2nd;
			block_right_2nd = block;
			block_right_offset = 0;
			__enable_irq();
			release(tmp);
		}
	}
}

//F_CPU defines go here


void OutI2S::config_i2s(void)
{
	//this fcn sets up the clock and audio sample rates
		//can use the actual sample frequency Fs
	if(debugg) Serial.println("Configuring I2S");

	
	CCM_CCGR5 |= CCM_CCGR5_SAI1(CCM_CCGR_ON);

	// if either transmitter or receiver is enabled, do nothing
	if (I2S1_TCSR & I2S_TCSR_TE) return;
	if (I2S1_RCSR & I2S_RCSR_RE) return;
	
	
//PLL:
	int fs = AUDIO_SAMPLE_RATE_EXACT;//defined in AudioStream.h
	// PLL between 27*24 = 648MHz und 54*24=1296MHz
	int n1 = 4; //SAI prescaler 4 => (n1*n2) = multiple of 4
	int n2 = 1 + (24000000 * 27) / (fs * 256 * n1);

	double C = ((double)fs * 256 * n1 * n2) / 24000000;
	int c0 = C;
	int c2 = 10000;
	int c1 = C * c2 - (c0 * c2);
	set_audioClock(c0, c1, c2);

	// clear SAI1_CLK register locations
	CCM_CSCMR1 = (CCM_CSCMR1 & ~(CCM_CSCMR1_SAI1_CLK_SEL_MASK))
		   | CCM_CSCMR1_SAI1_CLK_SEL(2); // &0x03 // (0,1,2): PLL3PFD0, PLL5, PLL4
	CCM_CS1CDR = (CCM_CS1CDR & ~(CCM_CS1CDR_SAI1_CLK_PRED_MASK | CCM_CS1CDR_SAI1_CLK_PODF_MASK))
		   | CCM_CS1CDR_SAI1_CLK_PRED(n1-1) // &0x07
		   | CCM_CS1CDR_SAI1_CLK_PODF(n2-1); // &0x3f

	// Select MCLK
	IOMUXC_GPR_GPR1 = (IOMUXC_GPR_GPR1
		& ~(IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL_MASK))
		| (IOMUXC_GPR_GPR1_SAI1_MCLK_DIR | IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL(0));

	//configure pins
	CORE_PIN23_CONFIG = 3;  //1:MCLK
	CORE_PIN21_CONFIG = 3;  //1:RX_BCLK
	CORE_PIN20_CONFIG = 3;  //1:RX_SYNC//LRCLK

	if(debugg) Serial.println("pins configured");

	int rsync = 0;
	int tsync = 1;

	//configure transmitter
	I2S1_TMR = 0;
	//I2S1_TCSR = (1<<25); //Reset
	I2S1_TCR1 = I2S_TCR1_RFW(1);
	I2S1_TCR2 = I2S_TCR2_SYNC(tsync) | I2S_TCR2_BCP // sync=0; tx is async;
		    | (I2S_TCR2_BCD | I2S_TCR2_DIV((1)) | I2S_TCR2_MSEL(1));
	I2S1_TCR3 = I2S_TCR3_TCE;
	I2S1_TCR4 = I2S_TCR4_FRSZ((2-1)) | I2S_TCR4_SYWD((32-1)) | I2S_TCR4_MF
		    | I2S_TCR4_FSD | I2S_TCR4_FSE | I2S_TCR4_FSP;
	I2S1_TCR5 = I2S_TCR5_WNW((32-1)) | I2S_TCR5_W0W((32-1)) | I2S_TCR5_FBT((32-1));//for 24 bit, change 15 to 

	if(debugg) Serial.println("transmitter configured");
	//configure receiver
	I2S1_RMR = 0;
	//I2S1_RCSR = (1<<25); //Reset
	I2S1_RCR1 = I2S_RCR1_RFW(1);//synced to transmitter clock
	I2S1_RCR2 = I2S_RCR2_SYNC(rsync) | I2S_RCR2_BCP  // sync=0; rx is async;
		    | (I2S_RCR2_BCD | I2S_RCR2_DIV((1)) | I2S_RCR2_MSEL(1));
	I2S1_RCR3 = I2S_RCR3_RCE;
	I2S1_RCR4 = I2S_RCR4_FRSZ((2-1)) | I2S_RCR4_SYWD((32-1)) | I2S_RCR4_MF
		    | I2S_RCR4_FSE | I2S_RCR4_FSP | I2S_RCR4_FSD;
	I2S1_RCR5 = I2S_RCR5_WNW((32-1)) | I2S_RCR5_W0W((32-1)) | I2S_RCR5_FBT((32-1));
	
	if(debugg) Serial.println("receiver configured.");
	if(debugg) Serial.println("I2S Configuration Complete");


}

	
/////////////////////////////////////
//Input
void InI2S::begin(void)
{
	dma.begin(true); // Allocate the DMA channel first
	
	OutI2S::config_i2s();
	
	CORE_PIN8_CONFIG  = 3;  //1:RX_DATA0
	IOMUXC_SAI1_RX_DATA0_SELECT_INPUT = 2;

	dma.TCD->SADDR = (void *)((uint32_t)&I2S1_RDR0 + 2);
	dma.TCD->SOFF = 0;
	dma.TCD->ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
	dma.TCD->NBYTES_MLNO = 2;
	dma.TCD->SLAST = 0;
	dma.TCD->DADDR = i2s_rx_buffer;
	dma.TCD->DOFF = 2;
	dma.TCD->CITER_ELINKNO = sizeof(i2s_rx_buffer) / 2;
	dma.TCD->DLASTSGA = -sizeof(i2s_rx_buffer);
	dma.TCD->BITER_ELINKNO = sizeof(i2s_rx_buffer) / 2;
	dma.TCD->CSR = DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;
	dma.triggerAtHardwareEvent(DMAMUX_SOURCE_SAI1_RX);

	I2S1_RCSR = I2S_RCSR_RE | I2S_RCSR_BCE | I2S_RCSR_FRDE | I2S_RCSR_FR;
//#endif
	update_responsibility = update_setup();
	dma.enable();
	dma.attachInterrupt(isr);
}


void InI2S::isr(void)
{
	uint32_t daddr, offset;
	const int16_t *src, *end;
	int16_t *dest_left, *dest_right;
	audio_block_t *left, *right;
	
	daddr = (uint32_t)(dma.TCD->DADDR);
	dma.clearInterrupt();
	
	if (daddr < (uint32_t)i2s_rx_buffer + sizeof(i2s_rx_buffer) / 2) {
		// DMA is receiving to the first half of the buffer
		// need to remove data from the second half
		src = (int16_t *)&i2s_rx_buffer[AUDIO_BLOCK_SAMPLES/2];
		end = (int16_t *)&i2s_rx_buffer[AUDIO_BLOCK_SAMPLES];
		if (InI2S::update_responsibility) AudioStream::update_all();
	} else {
		// DMA is receiving to the second half of the buffer
		// need to remove data from the first half
		src = (int16_t *)&i2s_rx_buffer[0];
		end = (int16_t *)&i2s_rx_buffer[AUDIO_BLOCK_SAMPLES/2];
	}
	left = InI2S::block_left;
	right = InI2S::block_right;
	if (left != NULL && right != NULL) {
		offset = InI2S::block_offset;
		if (offset <= AUDIO_BLOCK_SAMPLES/2) {
			dest_left = &(left->data[offset]);
			dest_right = &(right->data[offset]);
			InI2S::block_offset = offset + AUDIO_BLOCK_SAMPLES/2;
			arm_dcache_delete((void*)src, sizeof(i2s_rx_buffer) / 2);
			do {
				*dest_left++ = *src++;
				*dest_right++ = *src++;
			} while (src < end);
		}
	}

}
	
	
void InI2S::update(void)
{
	audio_block_t *new_left=NULL, *new_right=NULL, *out_left=NULL, *out_right=NULL;

	// allocate 2 new blocks, but if one fails, allocate neither
	new_left = allocate();
	if (new_left != NULL) {
		new_right = allocate();
		if (new_right == NULL) {
			release(new_left);
			new_left = NULL;
		}
	}
	__disable_irq();
	if (block_offset >= AUDIO_BLOCK_SAMPLES) {
		// the DMA filled 2 blocks, so grab them and get the
		// 2 new blocks to the DMA, as quickly as possible
		out_left = block_left;
		block_left = new_left;
		out_right = block_right;
		block_right = new_right;
		block_offset = 0;
		__enable_irq();
		// then transmit the DMA's former blocks
		transmit(out_left, 0);
		release(out_left);
		transmit(out_right, 1);
		release(out_right);
		//if(debugg) Serial.print(".");
	} else if (new_left != NULL) {
		// the DMA didn't fill blocks, but we allocated blocks
		if (block_left == NULL) {
			// the DMA doesn't have any blocks to fill, so
			// give it the ones we just allocated
			block_left = new_left;
			block_right = new_right;
			block_offset = 0;
			__enable_irq();
		} else {
			// the DMA already has blocks, doesn't need these
			__enable_irq();
			release(new_left);
			release(new_right);
		}
	} else {
		// The DMA didn't fill blocks, and we could not allocate
		// memory... the system is likely starving for memory!
		// Sadly, there's nothing we can do.
		__enable_irq();
	}
}
	
	
	
	
