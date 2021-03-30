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
//
//  may not be necessary with DAC, it has own startup Power-Up sequence
//  when MCLK is applied. Ramp-up(~250/420ms)is then initiated until complete.
//  when LRCK, SDIN and SCLK recieve valid signls, 2000 sample periods must pass
//  untill audio can begin to output.
//  These properties must be checked with th ADC as well.//
//
//////Includes go here//////////

#include "AudioStream.h" //contains AudioStream and AudioConnection classes
//#include <Audio.h>
#include "DIGILib.h"


///////  ADC/DAC objects  ////////
InI2S                      input;
OutI2S                     output;

////////Audio Effect objects////////
AudioEffectFlange          effect1;
AudioEffectFlange          effect2;
AudioEffectFlange          effect3;

AudioMixer4                mainMixer;
Tremolo_Effect						T_effect;
//Flanger_Effect            F_effect;
Distortion_Effect         D_effect;

/////////  Audio Streaming  objects  /////////

//Enable For main passtroguh
//AudioConnection          C1(input, 0, output, 0);
//AudioConnection          C2(input, 1, output, 1);//

//AudioConnection            c1(input, 0, T_effect, 0);//Tremulo
//AudioConnection            c1(input, 0, F_effect, 0);//flanger
AudioConnection            c2(input, 0, D_effect, 0);//Distortion

//AudioConnection            c4(effect1, 0, mainMixer, 2);
//AudioConnection            c5(effect2, 0, mainMixer, 1);
//AudioConnection            c6(effect3, 0, mainMixer, 0);

//AudioConnection            c7(mainMixer, 0, output, 0);

//AudioConnection            c9(T_effect, 0, output, 0);
//AudioConnection            c10(F_effect, 0, output, 0);
AudioConnection            c11(D_effect, 0, output, 0);

DIGIMUSER mux;


//defines for the flanger effect
//short l_delayline[12];
//int phase = 0;//

void setup(void)
{

  Serial.begin(9600);//debugging purposes
  while(!Serial);//busy while until serial.available is true
  delay(3000);

   // put your setup code here, to run once:

//library
   mux.dSetup();

  AudioMemory(24);//must change according to the memory amt necessary, one block

  //AudioNoInterrupts();

  //AudioInterrupts();

//begin fcn for flange
  //effect1.begin(l_delayline,12,3,3,0.5);
  //effect3.begin(l_delayline,12,3,3,0.5);
//effect2.begin(l_delayline,12,3,3,0.5);

D_effect.begin();
//T_effect.begin();//tremulo
}


void loop(void)
{

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
  //Serial.print("10 bit value: ");
  //Serial.print(gain);
  //delay(200);

//Tremolo and Flanger range 0.0-1.0
//Distortion range: 0-12
   float pot1_val = float(map(gain, 0,1023,1.0,24.0));//float( gain / 1023.0);//changed to 1.0 to avoid disabling stream

   Serial.printf("unmodified value: %f  ", gain);
   Serial.printf("pot 1 value: %f\n   ", pot1_val);
   
   delay(300);

  //T_effect.setGain(pot1_val);
  D_effect.setGain(pot1_val);


  /////////////////////

/*  if(gain > 512)
  {
    //effect1.voices(3,3,0.5);
    mainMixer.gain(2,1);
  }
  else
  {
    mainMixer.gain(2,0);
  }
  */

  //Serial.println(gainf);


}
