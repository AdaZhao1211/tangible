const int xInput = A0;
const int yInput = A1;
const int zInput = A2;
const int buttonPin = 2;
bool stable = true; // for x axis
bool play = true;
bool stopp = true;
bool pause = true;
bool speedup = true;
int timer = 500; //500 ms to react
unsigned long timerecord;
int state = -1;
int randomCount = 0;
unsigned long rtimerecord;
unsigned long record;
boolean dorecord = true;

// Take multiple samples to reduce noise
const int sampleSize = 10;
int turnaround = 0;

void setup()
{
  //analogReference(EXTERNAL);
  Serial1.begin(9600);
  while (!Serial1);
}

void loop()
{
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);
  int zRaw = ReadAxis(zInput);
  //Serial1.write(xRaw);
  Test(xRaw, yRaw, zRaw);
  delay(50);
}

int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
    reading += analogRead(axisPin);
  }
  return reading / sampleSize;
}

void setTrue() {
  stable = true;
  play = true;
  stopp = true;
  pause = true;;
  speedup = true;
}

void Test(int xRaw, int yRaw, int zRaw)
{
  //Serial1.writeln(zRaw);
  if (zRaw > 405 && pause)
  {
    if (state != 5) {
      if (turnaround == 3) {
        Serial1.write(54);
        state = -1;
        turnaround = 0;
      }
      if (state != 1) {
        timerecord = millis();
        state = 1;
        turnaround ++;
      }
      if (millis() - timerecord > timer) {
        Serial1.write(50);
        setTrue();
        pause = false;
        turnaround = 0;
      }
    }

  }
  if (zRaw < 290 && speedup)
  {
    if (state != 5) {
      if (turnaround == 3) {
        Serial1.write(54);
        state = -1;
        turnaround = 0;
      }
      if (state != 2) {
        timerecord = millis();
        state = 2;
        turnaround ++;
      }
      if (millis() - timerecord > timer) {
        Serial1.write(53);
        setTrue();
        speedup = false;
        turnaround = 0;
      }
    }
  }
  if (yRaw > 380  && stopp)
  {
    if (state != 5) {
      if (turnaround == 3) {
        Serial1.write(54);
        state = -1;
        turnaround = 0;
      }
      if (state != 3) {
        timerecord = millis();
        state = 3;
        turnaround ++;

      }
      if (millis() - timerecord > timer) {
        Serial1.write(55);
        setTrue();
        stopp = false;
        turnaround = 0;
      }
    }
  }
  if ( yRaw < 260 && play)
  {
    if (state != 5) {
      if (turnaround == 3) {
        Serial1.write(54);
        state = -1;
        turnaround = 0;
      }
      if (state != 4) {
        timerecord = millis();
        state = 4;
        turnaround ++;
      }
      if (millis() - timerecord > timer) {
        Serial1.write(49);
        setTrue();
        play = false;
        turnaround = 0;
      }
    }
  }

  if (stable) {
    if (xRaw < 280 && xRaw > 250 )
    {
      Serial1.write(52);
      ////Serial1.write(state);
      setTrue();
      stable = false;

    }
    if (xRaw > 380 && xRaw < 410)
    {
      Serial1.write(51);
      ////Serial1.write(state);
      setTrue();
      stable = false;
    }
  }
}
