#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>

#include "../lib/notes.h"

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
  CircuitPlayground.strip.begin();
  CircuitPlayground.strip.setBrightness(50);
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
  /* 
  Star Wars theme
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
  */

  // change this to make the song slower or faster
  int tempo = 108;

  // change this to whichever pin you want to use
  int buzzer = 11;

  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[] = {
    
    // Dart Vader theme (Imperial March) - Star wars 
    // Score available at https://musescore.com/user/202909/scores/1141521
    // The tenor saxophone part was used
    
    NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8,//1
    NOTE_F5,2, NOTE_C6,2,
    NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
    NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
    NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2
    
  };

  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 1) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    CircuitPlayground.playTone(melody[thisNote], noteDuration);
  }
}

void send_message(char *arr) {
  CircuitPlayground.setPixelColor(1, 0, 0, 0);
  CircuitPlayground.setPixelColor(2, 0, 0, 0);
  CircuitPlayground.setPixelColor(3, 0, 0, 0);
  CircuitPlayground.setPixelColor(4, 0, 0, 0);
  CircuitPlayground.setPixelColor(5, 0, 0, 0);
  CircuitPlayground.setPixelColor(6, 0, 0, 0);
  CircuitPlayground.setPixelColor(7, 0, 0, 0);
  CircuitPlayground.setPixelColor(8, 0, 0, 0);
  CircuitPlayground.setPixelColor(9, 0, 0, 0);
  CircuitPlayground.setPixelColor(10, 0, 0, 0);

  char c1 = arr[0];
  char c2 = arr[1];
  char c3 = arr[2];

  if (c1 == 'X' && c2 == 'Y' && c3 == 'Z'){
    CircuitPlayground.setPixelColor(1, 0, 255, 0);
  }
    else if (c1 == 'Z' && c2 == 'X' && c3 == 'Z'){
    CircuitPlayground.setPixelColor(2, 0, 255, 0);
  } 
    else if (c1 == 'Y' && c2 == 'Z' && c3 == 'Y'){
    CircuitPlayground.setPixelColor(3, 0, 255, 0);
  } 
    else if (c1 == 'Z' && c2 == 'X' && c3 == 'Y'){
    CircuitPlayground.setPixelColor(4, 0, 255, 0);
  } 
    else if (c1 == 'X' && c2 == 'Z' && c3 == 'X'){
    CircuitPlayground.setPixelColor(5, 0, 255, 0);
  } 
    else if (c1 == 'Z' && c2 == 'Y' && c3 == 'Y'){
    CircuitPlayground.setPixelColor(6, 0, 255, 0);
  } 
    else if (c1 == 'Y' && c2 == 'X' && c3 == 'Z'){
    CircuitPlayground.setPixelColor(7, 0, 255, 0);
  } 
    else if (c1 == 'Y' && c2 == 'Y' && c3 == 'X'){
    CircuitPlayground.setPixelColor(8, 0, 255, 0);
  } 
    else if (c1 == 'X' && c2 == 'Z' && c3 == 'Z'){
    CircuitPlayground.setPixelColor(9, 0, 255, 0);
  } 
    else if (c1 == 'X' && c2 == 'X' && c3 == 'X'){
    CircuitPlayground.setPixelColor(0, 0, 255, 0);
  }  
  else {
    CircuitPlayground.setPixelColor(1, 255, 0, 0);
    CircuitPlayground.setPixelColor(2, 255, 0, 0);
    CircuitPlayground.setPixelColor(3, 255, 0, 0);
    CircuitPlayground.setPixelColor(4, 255, 0, 0);
    CircuitPlayground.setPixelColor(5, 255, 0, 0);
    CircuitPlayground.setPixelColor(6, 255, 0, 0);
    CircuitPlayground.setPixelColor(7, 255, 0, 0);
    CircuitPlayground.setPixelColor(8, 255, 0, 0);
    CircuitPlayground.setPixelColor(9, 255, 0, 0);
    CircuitPlayground.setPixelColor(10, 255, 0, 0);
  }
}

void resetLEDs() {
  CircuitPlayground.setPixelColor(1, 0, 0, 0);
  CircuitPlayground.setPixelColor(2, 0, 0, 0);
  CircuitPlayground.setPixelColor(3, 0, 0, 0);
  CircuitPlayground.setPixelColor(4, 0, 0, 0);
  CircuitPlayground.setPixelColor(5, 0, 0, 0);
  CircuitPlayground.setPixelColor(6, 0, 0, 0);
  CircuitPlayground.setPixelColor(7, 0, 0, 0);
  CircuitPlayground.setPixelColor(8, 0, 0, 0);
  CircuitPlayground.setPixelColor(9, 0, 0, 0);
  CircuitPlayground.setPixelColor(0, 0, 0, 0);
}

void loop() {
  bool needToClassify = false;

  xSum=0;
  ySum=0;
  zSum=0;

  while (CircuitPlayground.leftButton()) {
    resetLEDs();
    // Make sure board is in the proper orientation
    if (abs(CircuitPlayground.motionZ()) -9.8 > 1) {

    }
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

  while (CUR_STRING_IDX > 2) {
    while (CircuitPlayground.leftButton()) {
      CUR_STRING_IDX = 0;
      send_message(CUR_STRING);
      messageSentTone();
      break;
    }
    while (CircuitPlayground.rightButton()) {
      playResetTone();
      CUR_STRING_IDX = 0;
      break;
    }
  }

  if (CircuitPlayground.rightButton()) { // reset button hit
    resetLEDs();
    CUR_STRING_IDX = 0;
    playResetTone();
  }

}
