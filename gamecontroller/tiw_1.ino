#include <Mouse.h>
#include <Keyboard.h>

const int spacebar = 7;
int state;
int prevstate = 0;

const int up = 11;
int upstate;
int prevupstate = 0;

const int left = 2;
int leftstate;
int prevleftstate = 0;

const int down = 4;
int downstate;
int prevdownstate = 0;

const int right = 9;
int rightstate;
int prevrightstate = 0;

const int clic = 6;
const int x = A0;
const int y = A1;
int xread;
int yread;
int prevmo = 0;
int mo;

void setup() {
  // put your setup code here, to run once:
  pinMode(spacebar, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(clic, INPUT);
  digitalWrite(clic, HIGH);
  Serial.begin(9600);
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  xread = analogRead(x);
  yread = analogRead(y);
  xread = map(xread, 0, 1000, -5, 5);
  yread = map(yread, 0, 1000, 5, -5);
  Mouse.move(xread, yread, 0);
  mo = digitalRead(clic);
  Serial.println(mo);
  if (prevmo != mo) {
    if (mo == 0) {
      //Serial.println("click");
      
      Mouse.press(MOUSE_LEFT);;
    }else{
      //Serial.println("release");
      Mouse.release(MOUSE_LEFT);                    
    }
    prevmo = mo;
  }
  //Serial.println(digitalRead(clic));
  state = digitalRead(spacebar);
  if (prevstate != state) {
    if (state == 0) {
      Keyboard.press(' ');
    }else{
      Keyboard.releaseAll();                                
    }
  }
  prevstate = state;
  upstate = digitalRead(up);
   if (prevupstate != upstate) {
    if (upstate == 0) {
      Keyboard.press('w');
    }else{
      Keyboard.releaseAll();
    }
  }
  prevupstate = upstate;
  //left
  leftstate = digitalRead(left);
   if (prevleftstate != leftstate) {
    if (leftstate == 0) {
      Keyboard.press('a');
    }else{
      Keyboard.releaseAll();
    }
  }
  prevleftstate = leftstate;
  //right
  rightstate = digitalRead(right);
   if (prevrightstate != rightstate) {
    if (rightstate == 0) {
      Keyboard.press('d');
    }else{
      Keyboard.releaseAll();
    }
  }
  prevrightstate = rightstate;
  //down
  downstate = digitalRead(down);
   if (prevdownstate != downstate) {
    if (downstate == 0) {
      Keyboard.press('s');
    }else{
      Keyboard.releaseAll();
    }
  }
  prevdownstate = downstate;
}
