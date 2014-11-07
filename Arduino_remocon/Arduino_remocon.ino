//緑色LED:6 , 赤色LED:7 , スピーカー:8 , リモコン受信モジュール:9 , その他はlcdディスプレイ
//温度センサ:a0 , cdsセル:a1



////////////////変数の宣言//////////////////////
int ir_out = 13;
int led = 6;

//冷房
unsigned int dr[] = {384,186,51,46,48,137,51,46,47,141,48,46,47,138,51,46,47,138,51,46,47,138,51,46,47,138,51,138,51,43,44,148,51,39,51,137,51,142,50,134,51,137,51,43,54,43,47,137,52,137,51,43,43,53,51,43,47,42,51,137,52,46,50,43,47,47,47,138,51,42,51,141,51,43,48,42,51,46,48,42,42,54,51,134,51,42,52,45,48,42,54,134,49,48,48,43,51,46,48,141,51,42,48,42,51,42,51,42,51,137,55,42,48,46,48,42,56,38,51,46,51,43,51,42,48,42,56,38,56,38,51,46,45,48,40,54,48,137,56,38,51,46,51,43,50,40,56,41,53,37,52,42,42,54,51,43,50,39,56,37,56,132,44,54,51,42,50,39,56,38,51,42,56,41,45,49,51,42,52,38,56,38,56,133,54,43,47,138,56,132,56,132,43,145,52,137,56,42,51,42,51,42,52,132,56,38,56,41,48,46,50,0};
//暖房
unsigned int dd[] = {380,189,47,46,47,141,47,46,48,141,48,46,47,141,48,46,47,141,48,46,48,140,48,46,48,140,48,141,48,46,48,141,48,46,48,141,48,140,48,140,48,140,48,46,48,46,47,140,48,140,48,46,48,46,48,45,48,46,48,140,48,46,48,46,48,46,48,140,48,46,48,140,48,46,48,46,47,46,52,41,47,46,48,140,48,46,48,46,47,46,48,141,47,141,48,45,48,46,47,140,48,46,48,46,47,46,48,46,48,141,48,46,48,46,48,46,48,45,48,46,47,46,48,46,48,46,48,46,48,46,47,46,48,46,48,46,47,140,48,46,47,46,48,46,47,46,48,46,48,46,48,46,47,46,47,46,47,46,48,46,48,141,48,46,48,46,48,46,47,46,47,47,47,46,47,46,47,46,47,46,47,46,48,141,48,46,47,142,47,141,47,141,47,142,47,142,47,46,48,47,46,46,47,141,48,142,47,46,47,48,46,0};
//除湿
unsigned int dj[] = {380,188,48,46,47,141,47,46,47,141,47,46,48,141,48,46,48,140,48,46,48,140,48,46,48,141,48,140,48,45,48,136,53,45,48,140,48,140,48,140,48,140,48,45,53,40,48,140,48,140,54,43,46,48,46,45,48,45,49,140,48,45,49,45,48,48,46,45,48,48,46,45,49,45,48,45,49,48,45,48,46,45,48,140,49,48,50,40,48,48,46,139,49,140,48,48,46,48,46,139,49,139,49,45,49,45,48,48,46,140,49,48,46,48,45,48,45,48,46,44,49,45,49,48,46,45,49,48,45,45,49,48,45,48,46,48,45,140,49,48,46,48,45,48,45,48,46,48,46,48,46,48,45,48,46,48,45,48,46,48,45,140,49,48,45,48,46,48,46,48,46,47,46,48,46,48,46,48,46,48,46,48,46,139,49,48,46,139,50,139,49,139,49,140,49,139,49,48,45,48,46,48,46,48,46,48,45,140,49,48,46,0};
//停止
unsigned int dt[] = {380,188,48,45,48,140,48,46,48,140,48,46,48,140,48,46,48,140,48,46,48,140,48,46,48,140,48,141,47,46,48,141,48,46,48,140,48,141,48,141,48,140,48,46,48,46,47,141,48,140,48,46,47,46,48,46,47,46,48,140,48,45,48,47,47,45,48,141,48,45,48,141,48,46,48,46,47,46,48,46,48,46,48,141,48,46,48,47,47,45,48,46,48,140,48,46,48,46,47,141,48,46,48,46,47,46,48,45,48,140,48,46,48,46,47,45,48,46,48,45,48,46,48,45,48,46,48,46,48,45,48,46,48,45,48,46,48,140,48,45,48,46,48,46,48,46,48,46,48,45,48,45,48,46,48,46,47,46,48,46,47,140,48,46,48,45,48,46,48,45,48,46,48,46,48,46,48,46,48,46,48,46,48,140,48,46,48,140,48,141,48,140,48,140,48,141,48,45,48,46,48,46,48,46,48,140,48,46,48,46,47,0};
//温度を上げる
unsigned int du[] = {374,197,39,54,40,149,40,52,42,146,45,49,41,150,42,52,36,149,42,52,41,147,42,54,36,152,39,149,36,57,37,152,37,60,34,155,36,152,34,150,42,150,39,52,44,54,36,147,42,150,36,58,36,57,39,52,42,55,36,152,36,57,39,54,42,52,42,49,49,142,40,152,36,55,39,54,37,56,42,52,40,54,39,147,42,56,36,55,36,55,39,152,39,147,39,58,37,53,41,149,42,53,40,52,38,54,42,52,42,144,42,54,37,55,44,55,34,60,34,54,42,57,36,55,36,57,36,60,36,52,44,55,36,55,36,57,36,152,39,52,42,54,39,54,42,55,34,58,36,54,42,60,34,52,42,54,39,57,34,60,34,150,44,54,37,54,39,151,37,55,39,57,34,62,31,58,38,57,37,54,36,55,44,149,34,57,39,154,34,150,36,152,39,152,33,152,39,55,41,55,36,54,34,62,36,60,35,151,34,60,34,0};
//温度を下げる
unsigned int ds[] = {374,192,42,54,36,152,38,54,37,150,39,56,40,154,32,54,39,152,36,55,41,150,36,57,42,149,33,155,34,57,36,155,34,57,41,146,42,150,36,152,44,148,33,60,31,60,41,148,39,152,36,57,34,54,40,54,39,64,29,154,32,60,39,54,37,54,38,152,37,52,41,152,34,57,39,54,37,58,32,63,35,58,33,152,39,55,39,64,30,58,30,163,34,147,42,52,34,71,28,156,32,63,26,62,36,58,34,59,34,156,32,59,30,62,38,57,32,63,35,156,32,59,32,68,20,63,39,56,38,60,33,60,36,55,34,154,34,60,34,66,28,59,31,62,36,66,28,58,32,65,24,75,26,56,34,68,28,67,24,168,26,57,31,67,30,154,34,59,32,61,30,66,28,65,21,72,26,66,30,73,23,161,24,263,26,158,29,158,31,164,24,166,28,56,29,64,30,60,33,170,24,159,26,157,30,64,35,0};


//int last = 0;なにこれ？
//リモコン信号を送信する時に使用する変数
unsigned long us = micros();

//pcから文字列が送られてきていないときは、strにnを格納
int str=0;

//温度表示用の変数
int ans , temp , tv ;

//////////////////// 自作関数 //////////////////////
// セットアップ
void setup() {
  Serial.begin(9600);
  
  pinMode(ir_out, OUTPUT);
  pinMode(led, OUTPUT);
}
 
// dataからリモコン信号を送信
void sendSignal(unsigned int data[256]) {
  int dataSize = sizeof(data) / sizeof(data[0]);
  for (int cnt = 0; cnt < dataSize; cnt++) {
    unsigned long len = data[cnt]*10;  // dataは10us単位でON/OFF時間を記録している
    unsigned long us = micros();
    do {
      digitalWrite(ir_out, 1 - (cnt&1)); // cntが偶数なら赤外線ON、奇数ならOFFのまま
      delayMicroseconds(8);  // キャリア周波数38kHzでON/OFFするよう時間調整
      digitalWrite(ir_out, 0);
      delayMicroseconds(7);
    } while (long(us + len - micros()) > 0); // 送信時間に達するまでループ
  }
}

//温度センサから温度を取得
void temperature(){
  ans = analogRead(0) ;              // アナログ０番ピンからセンサー値を読込む
  tv  = map(ans,0,1023,0,5000) ;     // センサー値を電圧に変換する
  temp = map(tv,300,1600,-30,100) ;  // 電圧から温度に変換する
  Serial.println(temp) ;             // 値をパソコン(ＩＤＥ)に送る
}


////////////////メインのループ//////////////////
void loop() {
  
  digitalWrite(led, LOW);
  str=0;
  
  if(Serial.available()>0){
    str =Serial.read();
  
     switch(str){
       case 1:
         sendSignal(dr);
         digitalWrite(led, HIGH);
         break;
       case 2:
         sendSignal(dd);
         digitalWrite(led, HIGH);
         break;
       case 3:
         sendSignal(dj);
         digitalWrite(led, HIGH);
         break;
       case 4:
         sendSignal(dt);
         digitalWrite(led, HIGH);
         break;
       case 5:
         sendSignal(du);
         digitalWrite(led, HIGH);
         break;
       case 6:
         sendSignal(ds);
         digitalWrite(led, HIGH);
         break;
       default:
         break;
     }
   }
           sendSignal(dr);
  //温度センサから温度を取得
  temperature();
  
  delay(3000);                       //３秒ごとにループ

}
