/*
MIT License

Copyright (c) 2020 David Walker-Howell

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#include "Effects.h"

/* CHOOSE THE INPUT DEVICE
 *  INPUT_DEVICE 0 ==> CS5343 ADC
 *  INPUT_DEVICE 1 ==> USB (make sure to change USB Type to Audio under Tools -> USB Typ)e  
 */
#define INPUT_DEVICE 1

const int pot1_pin = A5;

//pins connected to the rotary switch
const int RS_1 = 13;
const int RS_2 = 14;
const int RS_3 = 15;
const int RS_4 = 16;
const int RS_5 = 17;


int prev_state;



AudioOutputI2S     cs4344_dac;

#if INPUT_DEVICE == 0
  AudioInputI2S      input_device;
#else
  AudioInputUSB      input_device;
#endif  

//  Initialize the reverb effect.
Reverb                    reverb;
Tremolo_Effect            tremolo;
Distortion_Effect         distortion;
Flanger_Effect            flanger;

//Mixer for establishing which effect is output
AudioMixer4               mixer;

//Connect the output of the ADC to the input of the digital amplifier fx
AudioConnection   connection_reverb(input_device, 0, reverb, 0);
AudioConnection   connection_tremolo(input_device, 0, tremolo, 0);
AudioConnection   connection_distortion(input_device, 0, distortion, 0);
AudioConnection   connection_flanger(input_device, 0, flanger, 0);
//AudioConnection   connection_passthrough(input_device, 0, mixer, 3);

//Connect the output of the amplifier fx to the input of the DAC.
AudioConnection   connection_mixer_reverb(reverb, 0, mixer, 0);
AudioConnection   connection_mixer_tremolo(tremolo, 0, mixer, 1);
AudioConnection   connection_mixer_distortion(distortion, 0, mixer, 2);
AudioConnection   connection_mixer_flanger(flanger, 0, mixer, 3);

//Connect the mixer output to the cs4344 dac
AudioConnection   connection_dac(mixer, 0, cs4344_dac, 0);

void setup(){

  Serial.begin(115200);
  AudioMemory(100);

  pinMode(RS_1, INPUT);
  pinMode(RS_2, INPUT);
  pinMode(RS_3, INPUT);
  pinMode(RS_4, INPUT);
  pinMode(RS_5, INPUT);

  //Resolution to read the potentiometer
  analogReadResolution(12);
  mixer.gain(0, 1);
  mixer.gain(1, 0);
}


void loop(){

  //Sample the potentiometer and cast into a 16-bits (15 fractional).
  int16_t pot1_val = (int16_t)(analogRead(pot1_pin) << 3);
  float pot1_val_float = (float)pot1_val / 32767.0;
  reverb.set_attenuation_factor(pot1_val);
  tremolo.setGain(pot1_val_float);
  distortion.setGain(map(pot1_val, 0,32767 ,24.0,75.0));
  //flanger.setGain(pot1_val_float);//map(pot1_val, 0,32767 ,24.0,100.0)

  int state = get_rot_state();
  Serial.println(state);

  switch(state){
    case 0:
      mixer.gain(0, 4.0);
      mixer.gain(1, 0);
      mixer.gain(2, 0);
      //mixer.gain(3, 0);
      break;
    
    case 1:
      mixer.gain(0, 0);
      mixer.gain(1, 1.0);
      mixer.gain(2, 0);
      //mixer.gain(3, 0);
      //mixer.gain(3, 0);
      break;

    case 2:
      mixer.gain(0, 0);
      mixer.gain(1, 0);
      mixer.gain(2, 0.1);
      mixer.gain(3, 0);
      //mixer.gain(3, 0);
      break;

    case 3:
      mixer.gain(0, 0);
      mixer.gain(1, 0);
      mixer.gain(2, 0);
      //mixer.gain(3, 1.0);
      //mixer.gain(3, 1.0);
      break;
        
  }
  delay(10);
}

int get_rot_state(){
  // put your main code here, to run repeatedly:
  int state = prev_state;
  for(int i = RS_1; i <= RS_5; i++){
    switch(i){
    case RS_2: 
        pinMode(RS_1, OUTPUT);
        pinMode(RS_2, INPUT);
        pinMode(RS_3, OUTPUT);
        pinMode(RS_4, OUTPUT);
        pinMode(RS_5, OUTPUT);
         
        digitalWrite(RS_1, HIGH); //drives PIN14 high
        
        if(digitalRead(RS_2)){        //checks to see if PIN15 is high
          
          //Serial.println("State_0");
          //output = 0; //effect selected is tremo
          prev_state = 3;
          return(3);  
        }
        digitalWrite(RS_1, LOW);
        delay(5);
        break;
    case RS_3: 
        pinMode(RS_1, OUTPUT);
        pinMode(RS_2, OUTPUT);
        pinMode(RS_3, INPUT);
        pinMode(RS_4, OUTPUT);
        pinMode(RS_5, OUTPUT);
        
        digitalWrite(RS_2, HIGH); //drives PIN14 high
        
        if(digitalRead(RS_3)){        //checks to see if PIN16 is high
          
          //Serial.println("State_1");
            // = 1; //effect selected is dist
            prev_state = 2;
            return(2);
        }
        digitalWrite(RS_2, LOW);
        delay(5);
        break;
    case RS_4: 
        pinMode(RS_1, OUTPUT);
        pinMode(RS_2, OUTPUT);
        pinMode(RS_3, OUTPUT);
        pinMode(RS_4, INPUT);
        pinMode(RS_5, OUTPUT);
        
        digitalWrite(RS_3, HIGH);//drives PIN14 high
        if(digitalRead(RS_4)){        //checks to see if PIN17 is high

            //Serial.println("State_2");
            //output = 2; //effect selected is flanger
            prev_state = 1;
            return(1);
        }
        digitalWrite(RS_3, LOW);
        delay(5);
        break;
        
        
   case RS_5: 
        pinMode(RS_1, OUTPUT);
        pinMode(RS_2, OUTPUT);
        pinMode(RS_3, OUTPUT);
        pinMode(RS_4, OUTPUT);
        pinMode(RS_5, INPUT);
        
        digitalWrite(RS_4, HIGH); //drive PIN17 high
        
        if(digitalRead(RS_5)){        //checks to see if PIN 14 is high
            //Serial.println("State_3");
            prev_state = 0;
            return(0);
        }
        digitalWrite(RS_4, LOW);
        delay(5);
        break;
        
    }
}

return(prev_state);
}
