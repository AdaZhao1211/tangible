int num;
bool read = true;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  num = digitalRead(2);
  if(num == 1 && read){
    Serial.write(49);
    read = false;

  }
  if(num == 0){
    read = true;
  }
  //Serial.write(0);

  delay(1);
}
