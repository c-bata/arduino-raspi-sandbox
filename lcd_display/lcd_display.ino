#include <LiquidCrystal.h>

//         Syntax : LiquidCrystal(rs, rw, enable, d4, d5, d6, d7) 
LiquidCrystal lcd = LiquidCrystal(12, 11, 10,     5,  4,  3,  2);  // 配線  

void setup(){
  lcd.begin(16, 2);                                   // 液晶の 行数、列数 を設定
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HELLO 1234567890"); 
}

void loop(){
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
}
