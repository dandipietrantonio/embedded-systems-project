#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>

/*
  The idea is to decompose the motion into three sub movements. Each submovement is identified
  by the axis that experiences the most acceleration during that movement. Once we have three 
  movements, that is our message.

  NOTE: board must be held as flat as possible, with buttons facing up
*/

struct XYZ {
  float x;
  float y;
  float z;
};

int CUR_MOVEMENT= 1; // the current motion we're on
XYZ CUR_MOVEMENT_ARR[100]; // you have two seconds to make your movement
int NUM_READINGS_FOR_CUR_MOVEMENT=0;

float X,Y,Z; // current accelerometer reading

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void classifyMovement() {
  int xSum, ySum, zSum;
  for (int i = 0; i < NUM_READINGS_FOR_CUR_MOVEMENT; i++) {
    XYZ curReading = CUR_MOVEMENT_ARR[i];
    float curX = curReading.x;
    float curY = curReading.y;
    float curZ = curReading.z - 9.8; // to account for gravity

    xSum += curX > 0 ? curX : -1 * curX;
    ySum += curY > 0 ? curY : -1 * curY;
    zSum += curZ > 0 ? curZ : -1 * curZ;
  }

  if (xSum >= ySum && xSum >= zSum) {
    Serial.println("X is max!");
  } else if (ySum >= xSum && ySum >= zSum) {
    Serial.println("Y is max!");
  } else if (zSum >= xSum && zSum >= ySum) {
    Serial.println("Y is max!");
  }
}

void tooManyReadingsError(){
  Serial.println("ERROR: You took too long, you only have 3 seconds to record your movement");
}

void loop() {
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();

  bool needToClassify = false;
  while (CircuitPlayground.leftButton()) {
    Serial.println("Button is pressed");
    needToClassify = true;
    if (NUM_READINGS_FOR_CUR_MOVEMENT == 100) {
      tooManyReadingsError();
    } else {
      XYZ curReading;
      curReading.x = CircuitPlayground.motionX();
      curReading.y = CircuitPlayground.motionY();
      curReading.z = CircuitPlayground.motionZ();
      CUR_MOVEMENT_ARR[NUM_READINGS_FOR_CUR_MOVEMENT] = curReading;

      NUM_READINGS_FOR_CUR_MOVEMENT += 1;
    }
  }
  
  if (needToClassify) {
    classifyMovement();
    NUM_READINGS_FOR_CUR_MOVEMENT = 0;
  };

  delay(20);
}
