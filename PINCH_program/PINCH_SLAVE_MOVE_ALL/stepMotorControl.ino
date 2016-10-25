#include "Setting.h"

void steppingMotorControl(int mode){
  switch(mode){
    case STOP:
      digitalWrite(atTinyControlPin[0],LOW);
      break;
    case CLOCKWISE:
      digitalWrite(atTinyControlPin[0],HIGH);
      digitalWrite(atTinyControlPin[1],LOW);
      break;
    case ANTCLOCKWISE:
      digitalWrite(atTinyControlPin[0],HIGH);
      digitalWrite(atTinyControlPin[1],HIGH);
      break;
  }
}
