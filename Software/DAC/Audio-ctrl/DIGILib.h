/*
*
* This library was Designed and compiled by the 
* DIGIMUSER project Team 15 for Senior Design
* at SDSU Fall/Spring '21 
*
* This will contain all the necesarry files for the project
* which includes the nesessary drivers for the CS5343 and CS4344,
* the libraries for the vocal effects, and the required teensy audio
* setup libraries.  
*
*/


#ifndef DIGILib_h_
#define DIGILib_h_

#include "DMAChannel.h"


//Using a potentiometer:
//in order to use a pot for some efect such as gain,
//AudioNoInterrupts() must be used, make changes to the objects, 
//then update the library with AUdioInterrupts()


#include "I2S.h"
//#include "tremulo.h"
//#include "flanger.h"
#include "dist.h"





//Class to define pins
class DIGIMUSER 
{ 
public: 
	//DIGIMUSER();
	void dSetup(void);//{
	//i2s, for adc, potentiometer, rotary switch	
	//list 
	int potentiometer1;//for gain
	int potentiometer2;//tentative
	int RotSwitch;
	
	void doSomething();
	
};
#endif//DIGILIB_H_
/*
class Effect_trem constructor method will be in rtheir respective headers
dSetup();

*/