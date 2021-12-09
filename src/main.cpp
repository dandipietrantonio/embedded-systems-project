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

int xSum, ySum, zSum;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void classifyMovement() {
  unsigned long long int xSum, ySum, zSum;
  for (int i = 0; i < NUM_READINGS_FOR_CUR_MOVEMENT; i++) {
    XYZ curReading = CUR_MOVEMENT_ARR[i];
    float curX = curReading.x;
    float curY = curReading.y;
    float curZ = curReading.z - 9.8; // to account for gravity

    xSum += (int) (abs(curX) * 10);
    ySum += (int) (abs(curY) * 10);
    zSum += (int) ((abs(curZ) - 9.8) * 10);
  }

  if (xSum >= ySum && xSum >= zSum) {
    Serial.println("X is max!");
  } else if (ySum >= xSum && ySum >= zSum) {
    Serial.println("Y is max!");
  } else if (zSum >= xSum && zSum >= ySum) {
    Serial.println("Z is max!");
  }
}

void tooManyReadingsError(){
  Serial.println("ERROR: You took too long, you only have 3 seconds to record your movement");
}

void loop() {
  bool needToClassify = false;

  xSum=0;
  ySum=0;
  zSum=0;

  while (CircuitPlayground.leftButton()) {
    Serial.println("Button is pressed");
    needToClassify = true;
    xSum += (int) abs((CircuitPlayground.motionX() * 100));
    ySum += (int) abs((CircuitPlayground.motionY() * 100));
    zSum += (int) abs(((CircuitPlayground.motionZ()- 9.8) * 100));
    delay(5);
  }
  
  if (needToClassify) {
    Serial.print("XSUM:");
    Serial.println(xSum);
    Serial.print("ySUM:");
    Serial.println(ySum);
    Serial.print("zSUM:");
    Serial.println(zSum);
    if (xSum >= ySum && xSum >= zSum) {
      Serial.println("X is max!");
    } else if (ySum >= xSum && ySum >= zSum) {
      Serial.println("Y is max!");
    } else if (zSum >= xSum && zSum >= ySum) {
      Serial.println("Z is max!");
    }
    needToClassify = false;
  };

}
