int incomingByte = 0;  

void setup(){
	Serial.begin(9600);
	pinMode(13,OUTPUT);
	digitalWrite(13,LOW);
}
void loop(){

	while(Serial.available()>0){
		incomingByte = Serial.read();
		if(incomingByte<(int)'1') continue;
		if(incomingByte>(int)'9') continue;
		Serial.write(incomingByte);
		incomingByte=incomingByte-(int)'0';
		while(incomingByte>0){
			digitalWrite(13,HIGH);
			delay(250);
			digitalWrite(13,LOW);
			delay(250);	
			incomingByte--;	
		}
	}
}
