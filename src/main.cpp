#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>

/*
  The idea is to decompose the motion into three sub movements. Each submovement is identified
  by the axis that experiences the most acceleration during that movement. Once we have three 
  movements, that is our message.

  NOTE: board must be held as flat as possible, with buttons facing up
*/


int xSum, ySum, zSum;

char CUR_STRING[3];
int CUR_STRING_IDX = 0;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void playResetTone() {
  CircuitPlayground.playTone(900, 500);
}

void playXTone() {
  CircuitPlayground.playTone(500, 100);
}

void playYTone() {
  CircuitPlayground.playTone(500, 50);
  delay(60);
  CircuitPlayground.playTone(500, 50);
}

void playZTone() {
  CircuitPlayground.playTone(500, 33);
  delay(40);
  CircuitPlayground.playTone(500, 33);
  delay(40);
  CircuitPlayground.playTone(500, 33);
}

void messageSentTone() {
  delay(90);
  CircuitPlayground.playTone(200, 80);
  delay(90);
  CircuitPlayground.playTone(500, 80);
  delay(90);
  CircuitPlayground.playTone(900, 80);
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
      CUR_STRING[CUR_STRING_IDX] = 'X';
      playXTone();
    } else if (ySum >= xSum && ySum >= zSum) {
      CUR_STRING[CUR_STRING_IDX] = 'Y';
      playYTone();
    } else if (zSum >= xSum && zSum >= ySum) {
      CUR_STRING[CUR_STRING_IDX] = 'Z';
      playZTone();
    }
    needToClassify = false;
    CUR_STRING_IDX += 1;
  };

  if (CUR_STRING_IDX > 2) {
    Serial.print("Your string is: ");
    Serial.print(CUR_STRING[0]);
    Serial.print(CUR_STRING[1]);
    Serial.println(CUR_STRING[2]);
    CUR_STRING_IDX = 0;
    messageSentTone();
  }

  if (CircuitPlayground.rightButton()) { // reset button hit
    CUR_STRING_IDX = 0;
    playResetTone();
  }

}
