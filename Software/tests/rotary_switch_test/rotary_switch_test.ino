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

//pins connected to the rotary switch
const int RS_1 = 13;
const int RS_2 = 14;
const int RS_3 = 15;
const int RS_4 = 16;
const int RS_5 = 17;

int prev_state = 0;

void setup(){
  pinMode(RS_1, INPUT);
  pinMode(RS_2, INPUT);
  pinMode(RS_3, INPUT);
  pinMode(RS_4, INPUT);
  pinMode(RS_5, INPUT);
}


void loop(){

  get_rot_state();
  delay(250);
}

int get_rot_state(){
  // put your main code here, to run repeatedly:
  
  for(int i = RS_1; i <= RS_5; i++){
    switch(i){
    case RS_2: 
        pinMode(RS_1, OUTPUT);
        pinMode(RS_2, INPUT);
        pinMode(RS_3, OUTPUT);
        pinMode(RS_4, OUTPUT);
        pinMode(RS_5, OUTPUT);
         
        digitalWrite(RS_1, HIGH);
        
        if(digitalRead(RS_2)){
          
          //Serial.println("State_3");
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
        
        digitalWrite(RS_2, HIGH);
        
        if(digitalRead(RS_3)){
          Serial.println("State_2");  
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
        
        digitalWrite(RS_3, HIGH);
        if(digitalRead(RS_4)){        

          Serial.println("State_1");
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
          Serial.println("State_0");
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
