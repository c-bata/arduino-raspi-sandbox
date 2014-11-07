int ir_in = 9;
int ir_out = 13;
unsigned int data[512] = {};

int last = 0;
unsigned long us = micros();

// セットアップ
void setup() {
  Serial.begin(57600);        // シリアル通信速度の設定
  pinMode(ir_in, INPUT);  // 入出力ピンの設定
  pinMode(ir_out, OUTPUT);
}

// dataからリモコン信号を送信
void sendSignal() {
  for (int cnt = 0; cnt < 512; cnt++) {
    unsigned long len = data[cnt]*10;  // dataは10us単位でON/OFF時間を記録している
    if (len == 0) break;      // 0なら終端。
    unsigned long us = micros();
    do {
      digitalWrite(ir_out, 1 - (cnt&1)); // iが偶数なら赤外線ON、奇数なら0のOFFのまま
      delayMicroseconds(8);  // キャリア周波数38kHzでON/OFFするよう時間調整
      digitalWrite(ir_out, 0);
      delayMicroseconds(7);
    } while (long(us + len - micros()) > 0); // 送信時間に達するまでループ
  }
  Serial.print("OK\n");
}

// シリアルからの受信をチェック
void checkSerial() {
  if (Serial.available() > 0) {
    if (Serial.read() == ' ') {  // スペース受信で入力開始
      Serial.print(">");
      unsigned int x = 0;
      int i = 0;
      int len = 0;
      while (1) {
        while (Serial.available() == 0) {} // 次のバイトが来るまで無限ループで待つ
        int a = Serial.read();
        if (a >= '0' && a <= '9') {    // 0～9を受信なら
          len++;
          x *= 10;
          x += a - '0';
        } else if (len) {    // 数値を受信済み、かつ数値以外が来たら
          data[i++] = x; // 受信した数値をdataに記憶
          Serial.print(i);
          Serial.print(":");
          Serial.print(x);
          Serial.print("\t");
          if (x == 0 || i >= 512) { // 0受信で赤外線送信開始
            sendSignal();
            break;
          }
          x = 0;
          len = 0;
        }
      }
    }
  }
}

void loop() {
  unsigned int val;
  unsigned int cnt = 0;
  
  // Wait for incoming IR signal
  while ((val = digitalRead(ir_in)) == last) {  // パルスが切り替わるまで待機
    if (++cnt >= 30000) {  // 30000回ループで信号が終了したとみなす
      if (cnt == 30000)  
        Serial.print("\n");
      else
        checkSerial();   // シリアル通信が来ているかチェック
      cnt = 30000;
    }
  }

  unsigned long us2 = micros();
  Serial.print((us2-us)/10, DEC);   // 赤外線のON/OFFが続いた時間を10us単位で送信
  Serial.print(" ");
  last = val;
  us = us2;
}
