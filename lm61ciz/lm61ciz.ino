void setup() {
     Serial.begin(57600) ;      // パソコン(ArduinoIDE)とシリアル通信の準備を行う
}
void loop() {
     int ans , temp , tv ;

     ans = analogRead(0) ;              // アナログ０番ピンからセンサー値を読込む
     tv  = map(ans,0,1023,0,5000) ;     // センサー値を電圧に変換する
     temp = map(tv,300,1600,-30,100) ;  // 電圧から温度に変換する
     Serial.println(temp) ;             // 値をパソコン(ＩＤＥ)に送る
     delay(1000) ;                      // １秒毎に繰り返す
}
