#include <FlexiTimer2.h>
#include <Servo.h>
#include <Wire.h>

#define WIRE_SLAVE_ADDRESS 6

// PINCH flag statement
#define NONE 0
#define DETECT_CLOTH 1
#define PINCH_OPENED 2
#define INSIDE_CLOTH 3
#define MOVE 4
#define RELEASE_FLAG 5
#define RELEASE 6
#define INITIALIZE 7

// stepping motor statement 
#define STOP 0
#define CLOCKWISE 1
#define ANTCLOCKWISE 2

// servo degree setting
#define SERVO_OPEN 70
#define SERVO_CLOSE 180

// time between open to close (about 30ms * PINCH_OPEN_TIME)
#define PINCH_OPEN_TIME 50;
// between release to close 
#define PINCH_RELEASE_TIME 300;
#define PINCH_FINISH_TIME 300;
// pin asign
int photoReflecterPin[2] = {0,1};
int servoPin = 2;

Servo myServo;
int pinchState = NONE;
int openTimer, releaseTimer, finishTimer;

int atTinyControlPin[2] = {10,11};

int curtainPin = 2;


void setup() {
  // init
  Serial.begin(9600);
  
  myServo.attach(servoPin);
    
  // servo check
  myServo.write(SERVO_OPEN);
  delay(500);
  myServo.write(SERVO_CLOSE);
    
  openTimer = PINCH_OPEN_TIME;
  releaseTimer = PINCH_RELEASE_TIME;
  finishTimer = PINCH_FINISH_TIME;
  
  pinMode(atTinyControlPin[0], OUTPUT);
  pinMode(atTinyControlPin[1], OUTPUT);

  Wire.begin(WIRE_SLAVE_ADDRESS);
  Wire.onRequest(returnSensorNum);
  Wire.onReceive(setSensorValue);
  
  delay(100);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
//  Serial.print(pinchState);
//  Serial.print(" : ");
//  Serial.print(analogRead(photoReflecterPin[0]));
//  Serial.print(" , ");
//  Serial.println(analogRead(photoReflecterPin[1]));
  
  Serial.print(releaseTimer);
  
//  if((pinchState == NONE) && analogRead(photoReflecterPin[0]) > 300){
//    pinchState = DETECT_CLOTH;
//  }
  if(pinchState == DETECT_CLOTH){
    openTimer--;
    if(openTimer < 0){
      pinchState = PINCH_OPENED;
      openTimer = PINCH_OPEN_TIME;
    }
  }
//  if((pinchState == PINCH_OPENED) && analogRead(photoReflecterPin[1]) > 300){
//    pinchState = INSIDE_CLOTH;
//  }
  
//  if(pinchState == INSIDE_CLOTH){
//    //stepping_motor
////    steppingMotorControl(ANTCLOCKWISE);
////    pinchState = MOVE;
//    
//    //u_sonic
////    int input = analogRead(u_sonicPinReceive);
////    if(input >=600 || input <= 400){
////      for(int i = 0; i < 4; i++){
////        pinch_state_flag = RELEASE;
////      }
////    }
//  }
  if(pinchState == RELEASE_FLAG){
    releaseTimer--;
    if(releaseTimer < 0){
//      pinchState = NONE;
      pinchState = RELEASE;
      releaseTimer = PINCH_RELEASE_TIME;
    }
  }
  
  if(pinchState == RELEASE){
    finishTimer--;
    if(finishTimer < 0){
//      pinchState = NONE;
      pinchState = NONE;
      finishTimer = PINCH_FINISH_TIME;
      steppingMotorControl(STOP);
    }
  }
  
  switch(pinchState){
    case NONE: myServo.write(SERVO_CLOSE); break;
    case DETECT_CLOTH: myServo.write(SERVO_OPEN); break;
    case INSIDE_CLOTH: myServo.write(SERVO_CLOSE); break;
    case MOVE: myServo.write(SERVO_CLOSE); break;
//    case RELEASE: myServo.write(SERVO_OPEN);  break;  
    case RELEASE_FLAG: myServo.write(SERVO_CLOSE); break;
    case RELEASE: myServo.write(SERVO_OPEN);  break;
    case INITIALIZE: initialize(); break;
  }
  
  // Serial monitoring
//  Serial.println(analogRead(photoReflecterPin[0]));
////  Serial.print(" , ");
//  Serial.println(analogRead(photoReflecterPin[1]));
//  Serial.print(" , ");
//  Serial.println(flag);
  delay(30);
//  Serial.println(pinch_state_flag[0]);
}

///////////////////////////////////////////////////////////////////////////////////////////////

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

void returnSensorNum(){
  char sendData[3];
//  sendData[0] = (char)(pinchState);
  sendData[0] = (unsigned char)(analogRead(photoReflecterPin[0])/4);
  sendData[1] = (unsigned char)(analogRead(photoReflecterPin[1])/4);
  
  switch(pinchState){
    case NONE:
      sendData[2] = 'n';
      break;
    case DETECT_CLOTH:
      sendData[2] = 'd';
      break;
    case PINCH_OPENED:
      sendData[2] = 'p';
      break;
    case INSIDE_CLOTH:
      sendData[2] = 'i';
      break;
    case MOVE:
      sendData[2] = 'm';
      break;
    case RELEASE_FLAG:
      sendData[2] = 'f';
      break;
    case RELEASE:
      sendData[2] = 'r';
      break;
  }
  
//  sendData[2] = (char)(pinchState);
  
//  Serial.print("state");
//  Serial.println(pinchState);
////  Serial.print(" ");
//Serial.print("photo1");
//  Serial.println(analogRead(photoReflecterPin[0])/4);
////  Serial.print(" ");
//Serial.print("photo2");
//  Serial.println(analogRead(photoReflecterPin[1])/4);
//  Serial.print(" ");

  Wire.write(sendData);
}

void setSensorValue(int a){
  char c;
  while(Wire.available()){
    c = Wire.read(); // 1バイト受信
  }
  Serial.println(c);
  if(c == 'c'){
    steppingMotorControl(CLOCKWISE);
//    pinchState = MOVE;
  }
  else if(c == 'a'){
    steppingMotorControl(ANTCLOCKWISE);
//    pinchState = MOVE;
  }
  
  switch(c){
    case 'n':
      pinchState = NONE;
      break;
    case 'd':
      pinchState = DETECT_CLOTH;
      break;
    case 'p':
      pinchState = PINCH_OPENED;
      break;
    case 'i':
      pinchState = INSIDE_CLOTH;
      break;
    case 'm':
      pinchState = MOVE;
      break;
    case 'f':
      pinchState = RELEASE_FLAG;
      break;
    case 'r':
      pinchState = RELEASE;
      break;
    case 's':
      pinchState = INITIALIZE;
      break;
  }
}

void initialize(){
  // servo check
  myServo.write(SERVO_OPEN);
  delay(500);
  myServo.write(SERVO_CLOSE);
    
  openTimer = PINCH_OPEN_TIME;
  releaseTimer = PINCH_RELEASE_TIME;
  finishTimer = PINCH_FINISH_TIME;
  
  pinchState = NONE;
  
  steppingMotorControl(NONE);
}  

