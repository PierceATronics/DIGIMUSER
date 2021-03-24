//////////////////////////////////////////////////////////////////////////////////
// Company: DIGIMUSER(Team 15)
// Engineer: Angel Martinez
// 
// Create Date: 01/26/2021 11:16:44 PM
// Design Name: 
// Module Name: Audio_ctrl
// Project Name: Vocal Effects Processor
// Target Devices: 
// 
// Description: 
// This is the code for audio sampling,i2s data transmission 
// for the A/D and D/A, and clock generation. 
// Testing environment includes Teensy 4.0 and PmodI2S2 
// 
// 
// Revision:
// Revision 0.01 - File Created
// Revision 0.10 - Added the DAC i2s library
// Revision 0.20 - Added the ADC i2s library
// Revision 0.30 - DigiLib library created
//
// Additional Comments:
//     References B.Dorr Simple DSPFramework
//     Paul Stoffregen(BasedG0D) Teensy files: 
//        Audio.h - just a linker for all . h files
//        output_i2s.cpp/.h (audiostream.cpp/.h)
//        input_i2s.h
//      Note: library files are written for 16 bit
// 
//////////////////////////////////////////////////////////////////////////////////



// The software will be completed in several steps:
//  1. Enable DAC i2s - test with simple sine wave
//  2. Enable ADC - Send audio, reflect it through serial monitor 
//  3. Save captured data to memory(DMA)
//  4. Audio passthrough from ADC to DAC 
//

// Initial Checks
//  -Tested with PassThroughStereo - only played through L in headphone
//  -Tested with ToneSweep
//  -Hardware setup completed, running successfully 

//      PIN SETUP
//   D/A    |   A/D
//  23-MCLK1  | 23-MCLK1
//  21-BCLK1  | 21-BCLK1(SCLK)
//  20-LRCLK  | 20-LRCLK
//   8-SDIN   |  9-SDOUT* Use of pins 8 & 9 are working as of 2/16    
//    GND   |   GND
//    VCC   |   VCC(3.3V)

//////Includes go here//////////

#include "AudioStream.h" //contains AudioStream and AudioConnection classes
//#include <Audio.h>
#include "DIGILib.h"

//////////Testing Objects////////////
// Create the library objects 
// AudioSynthWaveformSine   sine2;//
// AudioSynthWaveformSine   sine1;//
// AudioSynthWaveform       waveform1;  
// sine wave audio tone generatrion here
// AudioSynthToneSweep tones;
/////////////////////////////////////

InI2S                      input;   
OutI2S                     output;

AudioEffectFlange          effect1;
AudioEffectFlange          effect2;
AudioEffectFlange          effect3;
//TremuloEffect            effect1;
//FlangerEffect            effect2;
//DistortionEffect         effect3;
AudioMixer4                mainMixer;
Tremolo_Effect						T_effect;

//Enable for DAC testing
//AudioConnection          C1(sine2, 0, output, 0);//(AudioStream &source, unsigned char sourceOutput,AudioStream &destination, unsigned char destinationInput
//AudioConnection          C2(sine1, 0, output, 1);//


//Enable For main passtroguh 
//AudioConnection          C1(input, 0, output, 0);
//AudioConnection          C2(input, 1, output, 1);//


//For effects passthrough
AudioConnection            c1(input, 0, T_effect, 0);
AudioConnection            c2(input, 0, effect2, 0);
AudioConnection            c3(input, 0, effect3, 0);

AudioConnection            c4(effect1, 0, mainMixer, 2);
AudioConnection            c5(effect2, 0, mainMixer, 1);
AudioConnection            c6(effect3, 0, mainMixer, 0);

AudioConnection            c7(mainMixer, 0, output, 0);
AudioConnection            c8(mainMixer, 0, output, 1);
AudioConnection            c9(T_effect, 0, output, 1);

DIGIMUSER mux;



short l_delayline[12];
int phase = 0;//

void setup(void)
{

  Serial.begin(9600);//debugging purposes
  while(!Serial);//busy while until serial.available is true
  delay(3000);

 
  //can also be a function DACSetup();
  //may not be necessary with DAC, it has own startup Power-Up sequence
  //when MCLK is applied. Ramp-up(~250/420ms)is then initiated until complete.
  //when LRCK, SDIN and SCLK recieve valid signls, 2000 sample periods must pass
  //untill audio can begin to output. 
  //These properties must be checked with th ADC as well. 
  
   // put your setup code here, to run once:
   
   mux.dSetup();
   
  AudioMemory(24);//must change according to the memory amt necessary, one block
  //while (!Serial);
  //waveform1.pulseWidth(0.5);
  //waveform1.begin(0.4, 220, WAVEFORM_PULSE);

  
  //AudioNoInterrupts();
  //sine1.frequency(550);
  //sine2.frequency(550);
 /// sine1.amplitude(1.0);
 // sine2.amplitude(1.0);
  //AudioInterrupts();

//begin fcn for flange
  effect1.begin(l_delayline,12,3,3,0.5);
  //effect3.begin(l_delayline,12,3,3,0.5);
//effect2.begin(l_delayline,12,3,3,0.5);


//T_effect.begin();
}


void loop(void)
{
  /*phase+=10;
  if (phase==360) phase=0;
  AudioNoInterrupts();
  sine2.phase(phase);
  AudioInterrupts();
  delay(250);
  */
  //can change to flaot
  float gain = mux.getGain();
  //Serial.print("Gain is ");
  //Serial.println(gain);
  //delay(1000);
  //mainMixer.gain(0,0);
  //mainMixer.gain(1,0);
  //mainMixer.gain(2,0);
  //mainMixer.gain(3,0);
  ///////////////////////
  
  //0-1023
  analogReadResolution(10);
  Serial.print("10 bit value: ");
  Serial.print(gain);
  delay(200);
  
  
  /////////////////////
  
  
  if(gain > 512)
  {
    effect1.voices(3,3,0.5);
    mainMixer.gain(2,1);
  }
  else
  {
    mainMixer.gain(2,0);
  }
  
  //Serial.println(gainf);
  
  
}
