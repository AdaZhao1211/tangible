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

void setup()
{
  analogReference(EXTERNAL);
  Serial.begin(9600);
}

void loop()
{
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);
  int zRaw = ReadAxis(zInput);
  ////Serial.println(xRaw);
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

  if (zRaw > 640 && pause)
  {
    if (state != 5) {
      if (state != 1) {
        timerecord = millis();
        state = 1;
      }
      if (millis() - timerecord > timer) {
        Serial.write(50);
        setTrue();
        pause = false;
      }
    }

  }
  if (zRaw < 450 && speedup)
  {
    if (state != 5) {
      if (state != 2) {
        timerecord = millis();
        state = 2;
      }
      if (millis() - timerecord > timer) {
        Serial.write(53);
        setTrue();
        speedup = false;
      }
    }
  }
  if (yRaw > 600  && stopp)
  {
    if (state != 5) {
      if (state != 3) {
        timerecord = millis();
        state = 3;
      }
      if (millis() - timerecord > timer) {
        Serial.write(55);
        setTrue();
        stopp = false;
      }
    }
  }
  if ( yRaw < 410 && play)
  {
    if (state != 5) {
      if (state != 4) {
        timerecord = millis();
        state = 4;
      }
      if (millis() - timerecord > timer) {
        Serial.write(49);
        setTrue();
        play = false;
      }
    }
  }


  if (stable) {
    if (state == 5) {
      if (xRaw < 400 || xRaw > 620) {
        randomCount ++;
      }
      if (millis() - rtimerecord > timer) {
        //the end of random recording
        if (randomCount > 3) {
          Serial.write(54);
        }
        state = 6;
        setTrue();
        stable = false;
        delay(1000);
      }
    } else {
      if (xRaw < 400 || xRaw > 620) {
        //random process start
        if (state != 6) {
          //start recording shaking
          rtimerecord = millis();
          state = 5;
          randomCount = 0;
          dorecord = true;
          //Serial.println("start recording");
          randomCount ++;
        }
      } else {
        //last or next
        if (xRaw < 411 && xRaw > 407 )
        {
          Serial.write(52);
          ////Serial.println(state);
          setTrue();
          stable = false;

        }
        if (xRaw > 609 && xRaw < 613)
        {
          Serial.write(51);
          ////Serial.println(state);
          setTrue();
          stable = false;
        }
      }
    }// end of state != 5 but stable
  }// end of stable
}
