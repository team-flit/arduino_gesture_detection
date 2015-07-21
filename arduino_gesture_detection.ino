#define THRESHOLD 200
#define LEFT      4
#define RIGHT     6

AccelerationReading previousAccel;

void setup() {
  Bean.setLed(0, 0, 0);
  previousAccel = Bean.getAcceleration();
}

void loop() {
  if ( !Bean.getConnectionState() ) return;

  AccelerationReading currentAccel = Bean.getAcceleration();

  int accelDifference = getAccelDifference(previousAccel, currentAccel);
  previousAccel = currentAccel;

  if ( accelDifference > THRESHOLD ) {
    int dir = readGesture(100);
    //    if (dir) Bean.setScratchNumber(1, dir);
    if ( dir ) {
      uint8_t buffer[1];
      buffer[0] = dir;
      Bean.setScratchData(1, buffer, 1);
    }
  } else {
  Bean.sleep(50);
  }
}

int readGesture (int time) {
  int x = 0;
  int y = 0;
  int z = 0;
  int direction = 0;

  for ( int i = 0; i < 10; i++ ) {
    AccelerationReading accel = Bean.getAcceleration();
    String stringToPrint = String();
    x += accel.xAxis;
    y += accel.yAxis;
    z += accel.zAxis;
    Bean.sleep(time);
  }
  String stringToPrint = String();
  stringToPrint = stringToPrint + "X: " + x + "\tY: " + y + "\tZ: " + z;
  if ( x < -500 && y > 0 && z > 2000 ) {
    direction = LEFT; // LEFT
  } else if ( x > 500 && x < 1500 && y > 0 && z < 500 ) {
    direction = RIGHT; // RIGHT
  }
  //  else {
  //    direction = "Unknown:" + stringToPrint;
  //  }
  return direction;
}

// This function calculates the difference between two acceleration readings
int getAccelDifference(AccelerationReading readingOne, AccelerationReading readingTwo) {
  int deltaX = abs(readingTwo.xAxis - readingOne.xAxis);
  int deltaY = abs(readingTwo.yAxis - readingOne.yAxis);
  int deltaZ = abs(readingTwo.zAxis - readingOne.zAxis);
  // Return the magnitude
  return deltaX + deltaY + deltaZ;
}
