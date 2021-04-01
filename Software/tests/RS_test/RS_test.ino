//Test code for rotary switch


//pins connected to the rotary switch
int RS_1 = 14;
int RS_2 = 15;
int RS_3 = 16;
int RS_4 = 17;

void setup() {
  

  Serial.begin(38400);
  
  pinMode(RS_1, INPUT_PULLDOWN);
  pinMode(RS_2, INPUT_PULLDOWN);
  pinMode(RS_3, INPUT_PULLDOWN);
  pinMode(RS_4, INPUT_PULLDOWN);
  
  //pinMode(13, OUTPUT);pinMode(2, OUTPUT);pinMode(3, OUTPUT);pinMode(4, OUTPUT);//led declarations

}

void loop() {
  // put your main code here, to run repeatedly:

for(int i = 14; i < 18; i++){
    switch(i){
    case 14: 
         pinMode(14, OUTPUT);
         pinMode(15, INPUT_PULLDOWN);
         pinMode(16, OUTPUT);
         pinMode(17, OUTPUT);
         
        digitalWrite(14, HIGH); //drives PIN14 high
        
        if(digitalRead(15)){        //checks to see if PIN15 is high
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          
          Serial.println("State_0");
            //output = 0; //effect selected is tremo
            
        }
        break;
    case 15: 
        pinMode(14, OUTPUT);
         pinMode(15, OUTPUT);
         pinMode(16, INPUT_PULLDOWN);
         pinMode(17, OUTPUT);
        
        digitalWrite(14, HIGH); //drives PIN14 high
        
        if(digitalRead(16)){        //checks to see if PIN16 is high
          
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);
          
          Serial.println("State_1");
            // = 1; //effect selected is dist
        }
        break;
    case 16: 
        pinMode(14, OUTPUT);
         pinMode(15, OUTPUT);
         pinMode(16, OUTPUT);
         pinMode(17, INPUT_PULLDOWN);
        
        digitalWrite(14, HIGH);//drives PIN14 high
        if(digitalRead(17)){        //checks to see if PIN17 is high
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);

          Serial.println("State_2");
            //output = 2; //effect selected is flanger
        }
        break;
        delay(50);
        /*
    17: 
        pinMode(PIN14, OUTPUT);
         pinMode(PIN15, OUTPUT);
         pinMode(PIN16, OUTPUT);
         pinMode(PIN17, INPUT);
        digitalWrite(PIN17, HIGH); //drive PIN17 high
        if(digitalRead(PIN14){        //checks to see if PIN 14 is high
            output = 3; //effect selected is <effect name>
            Serial.println("State_3");
        }
        break;
        */
    }
}
}
