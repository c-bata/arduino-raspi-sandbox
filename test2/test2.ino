byte val=0;
int led = 13; 

void setup() { 
        pinMode(led, OUTPUT); 
        Serial.begin(9600);
}


void loop() {
        if(Serial.available() > 0){ 

                val = Serial.read();
                Serial.print(val); //for debug

                if(val == '1'){
                        digitalWrite(led,HIGH);
                        delay(1000);
                }
                else if(val == 'a'){   
                        digitalWrite(led,HIGH);
                        delay(1000);
                }
                else if(val == '0')
                {   
                        digitalWrite(led,LOW);
                        delay(1000);
                }
        }   
}
