const int xInput = A0;
const int yInput = A1;
const int zInput = A2;
const int buttonPin = 2;
bool stable = true;
bool play = true;
bool stopp = true;
bool pause = true;
bool speedup = true;

// Raw Ranges:
// initialize to mid-range and allow calibration to
// find the minimum and maximum for each axis
int xRawMin = 512;
int xRawMax = 512;

int yRawMin = 512;
int yRawMax = 512;

int zRawMin = 512;
int zRawMax = 512;

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
  if (digitalRead(buttonPin) == LOW)
  {
    AutoCalibrate(xRaw, yRaw, zRaw);
  }
  else
  {
    Test(xRaw, yRaw, zRaw);

    // Convert raw values to 'milli-Gs"
    //    long xScaled = map(xRaw, xRawMin, xRawMax, -1000, 1000);
    //    long yScaled = map(yRaw, yRawMin, yRawMax, -1000, 1000);
    //    long zScaled = map(zRaw, zRawMin, zRawMax, -1000, 1000);
    //
    //    // re-scale to fractional Gs
    //    float xAccel = xScaled / 1000.0;
    //    float yAccel = yScaled / 1000.0;
    //    float zAccel = zScaled / 1000.0;
    //
    ////    Serial.print(" :: ");
    ////    Serial.print(xAccel);
    ////    Serial.print("G, ");
    ////    Serial.print(yAccel);
    ////    Serial.print("G, ");
    ////    Serial.print(zAccel);
    ////    Serial.println("G");
    //
    delay(10);
  }
}

//
// Read "sampleSize" samples and report the average
//
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


void Test(int xRaw, int yRaw, int zRaw)
{
  if (yRaw < 410 && pause)
  {
    Serial.println("pause");
    stable = true;
    play = true;
    stopp = true;
    pause = false;
    speedup = true;
  }
  if (yRaw > 600 && speedup)
  {
    Serial.println("fast");
    stable = true;
    play = true;
    stopp = true;
    pause = true;
    speedup = false;

  }
  if (zRaw < 450 && stopp)
  {
    Serial.println("stop");
    stable = true;
    play = true;
    stopp = false;
    pause = true;
    speedup = true;

  }
  if (zRaw > 640 && play)
  {
    Serial.println("play");
    stable = true;
    play = false;
    stopp = true;
    pause = true;
    speedup = true;

  }
  if (stable) {
    if (xRaw < 420 )
    {
      Serial.println("next one");
      stable = false;
      play = true;
      stopp = true;
      pause = true;
      speedup = true;

    }
    if (xRaw > 600)
    {
      Serial.println("last one");
      stable = false;
      play = true;
      stopp = true;
      pause = true;
      speedup = true;

    }
  }
}


void AutoCalibrate(int xRaw, int yRaw, int zRaw)
{
  Serial.println("Calibrate");
  if (xRaw < xRawMin)
  {
    xRawMin = xRaw;
  }
  if (xRaw > xRawMax)
  {
    xRawMax = xRaw;
  }

  if (yRaw < yRawMin)
  {
    yRawMin = yRaw;
  }
  if (yRaw > yRawMax)
  {
    yRawMax = yRaw;
  }

  if (zRaw < zRawMin)
  {
    zRawMin = zRaw;
  }
  if (zRaw > zRawMax)
  {
    zRawMax = zRaw;
  }
}
