#include <Bounce.h>

int pinDo = 13;
int pinRe = 12;
int pinMi = 11;
int pinFa = 10;
int pinSo = 9;
int pinLa = 8;
int pinTi = 7;
int pinDo2 = 6;
int pinRe2 = 5;
int state[9];
 
Bounce Do = Bounce( pinDo,20 );
Bounce Re = Bounce( pinRe,20 );
Bounce Mi = Bounce( pinMi,20 );
Bounce Fa = Bounce( pinFa,20 );
Bounce So = Bounce( pinSo,20 );
Bounce La = Bounce( pinLa,20 );
Bounce Ti = Bounce( pinTi,20 );
Bounce Do2 = Bounce( pinDo2,20 );
Bounce Re2 = Bounce( pinRe2,20 );
 
void setup() {
  pinMode(pinDo, INPUT);
  pinMode(pinRe, INPUT);
  pinMode(pinMi, INPUT);
  pinMode(pinFa, INPUT);
  pinMode(pinSo, INPUT);
  pinMode(pinLa, INPUT);
  pinMode(pinTi, INPUT);
  pinMode(pinDo2, INPUT);
  pinMode(pinRe2, INPUT);
 
  Serial.begin(31250); 
}
 
void loop(){
 
  Do.update ();
  if ((Do.read() == HIGH)&&(state[0] == 0)) {
    noteOn(144,60,127);
    state[0] = 1;
  }
  if ((Do.read() == HIGH)&&(state[0] == 1)) {
  }
  if ((Do.read() == LOW)&&(state[0] == 1)) {
    noteOn(128,60,127);
    state[0] = 0;
  }
  if ((Do.read() == LOW)&&(state[0] == 0)) {
  }
 
  Re.update ();
  if ((Re.read() == HIGH)&&(state[1] == 0)) {
    noteOn(144,62,127);
    state[1] = 1;
  }
  if ((Re.read() == HIGH)&&(state[1] == 1)) {
  }
  if ((Re.read() == LOW)&&(state[1] == 1)) {
    noteOn(128,62,127);
    state[1] = 0;
  }
  if ((Re.read() == LOW)&&(state[1] == 0)) {
  }
 
  Mi.update ();
  if ((Mi.read() == HIGH)&&(state[2] == 0)) {
    noteOn(144,64,127);
    state[2] = 1;
  }
  if ((Mi.read() == HIGH)&&(state[2] == 1)) {
  }
  if ((Mi.read() == LOW)&&(state[2] == 1)) {
    noteOn(128,64,127);
    state[2] = 0;
  }
  if ((Mi.read() == LOW)&&(state[2] == 0)) {
  }
 
  Fa.update ();
  if ((Fa.read() == HIGH)&&(state[3] == 0)) {
    noteOn(144,65,127);
    state[3] = 1;
  }
  if ((Fa.read() == HIGH)&&(state[3] == 1)) {
  }
  if ((Fa.read() == LOW)&&(state[3] == 1)) {
    noteOn(128,65,127);
    state[3] = 0;
  }
  if ((Fa.read() == LOW)&&(state[3] == 0)) {
  }
 
  So.update ();
  if ((So.read() == HIGH)&&(state[4] == 0)) {
    noteOn(144,67,127);
    state[4] = 1;
  }
  if ((So.read() == HIGH)&&(state[4] == 1)) {
  }
  if ((So.read() == LOW)&&(state[4] == 1)) {
    noteOn(128,67,127);
    state[4] = 0;
  }
  if ((So.read() == LOW)&&(state[4] == 0)) {
  }
 
  La.update ();
  if ((La.read() == HIGH)&&(state[5] == 0)) {
    noteOn(144,69,127);
    state[5] = 1;
  }
  if ((La.read() == HIGH)&&(state[5] == 1)) {
  }
  if ((La.read() == LOW)&&(state[5] == 1)) {
    noteOn(128,69,127);
    state[5] = 0;
  }
  if ((La.read() == LOW)&&(state[5] == 0)) {
  }
 
  Ti.update ();
  if ((Ti.read() == HIGH)&&(state[6] == 0)) {
    noteOn(144,71,127);
    state[6] = 1;
  }
  if ((Ti.read() == HIGH)&&(state[6] == 1)) {
  }
  if ((Ti.read() == LOW)&&(state[6] == 1)) {
    noteOn(128,71,127);
    state[6] = 0;
  }
  if ((Ti.read() == LOW)&&(state[6] == 0)) {
  }
 
  Do2.update ();
  if ((Do2.read() == HIGH)&&(state[7] == 0)) {
    noteOn(144,72,127);
    state[7] = 1;
  }
  if ((Do2.read() == HIGH)&&(state[7] == 1)) {
  }
  if ((Do2.read() == LOW)&&(state[7] == 1)) {
    noteOn(128,72,127);
    state[7] = 0;
  }
  if ((Do2.read() == LOW)&&(state[7] == 0)) {
  }
 
  Re2.update ();
  if ((Re2.read() == HIGH)&&(state[8] == 0)) {
    noteOn(144,74,127);
    state[8] = 1;
  }
  if ((Re2.read() == HIGH)&&(state[8] == 1)) {
  }
  if ((Re2.read() == LOW)&&(state[8] == 1)) {
    noteOn(128,74,127);
    state[8] = 0;
  }
  if ((Re2.read() == LOW)&&(state[8] == 0)) {
  }
}
d
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
