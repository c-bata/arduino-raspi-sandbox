int val = 0;  
  
void setup() {  
  Serial.begin(9600);  
}  
  
void loop() {  
  val = analogRead(0);  
    
  // valを0～255の範囲に正規化してP5に送る  
  Serial.write(map(val, 0, 1023, 0, 255));    
  delay(100);  
}  
