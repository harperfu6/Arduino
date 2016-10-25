#include <FlexiTimer2.h>
#include <Servo.h>
#include <Wire.h>
#include "Setting.h"

Servo myServo;
int pinchState;
int openTimer;
int releaseTimer;
int finishTimer;

// **** PIN ASIGN ****
int photoReflecterPin[2] = {0,1};
int servoPin = 2;
int atTinyControlPin[2] = {10,11};
int curtainPin = 2;

//************** PINCH STATEMENT ********************
// 0. NONE
// 1. -> DETECT_CLOTH : if detected cloth around the top natch of PINCH
// 2. -> PINCH_OPENED : after DETECT_CLOTH, PINCH become OPEN
// 3. -> INSIDE_CLOTH : if detected cloth inside of the PINCH
// 4. -> MOVE         : move to other side to open the cloth
// 5. -> RELEASE_FLAG : move to first position to BATAM
// 6. -> RELEASE      : release the cloth
// 7. -> INITIALIZE   : return to first parameters
//***************************************************

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);

  initialize();
  
  pinMode(atTinyControlPin[0], OUTPUT);
  pinMode(atTinyControlPin[1], OUTPUT);

  // *** wire setting ***
  Wire.begin(WIRE_SLAVE_ADDRESS);
  Wire.onRequest(sendSensorNum);
  Wire.onReceive(receiveWireMessage);
  
  delay(100);
}

void loop() {
  
#ifdef DEBUG
  Serial.print(pinchState);
  Serial.print(" : ");
  Serial.print(analogRead(photoReflecterPin[0]));
  Serial.print(" , ");
  Serial.println(analogRead(photoReflecterPin[1]));
#endif 

  Serial.println(pinchState);

// 1. -> DETECT_CLOTH : if detected cloth around the top natch of PINCH
// 2. -> PINCH_OPENED : after DETECT_CLOTH, PINCH become OPEN
// 3. -> INSIDE_CLOTH : if detected cloth inside of the PINCH
// 4. -> MOVE         : move to other side to open the cloth
// 5. -> RELEASE_FLAG : move to first position to BATAM
// 6. -> RELEASE      : release the cloth
// 7. -> INITIALIZE 

  switch(pinchState){
    case NONE:
      myServo.write(SERVO_CLOSE);
      break;
    case DETECT_CLOTH:
      openTimer--;
      if(openTimer < 0){
        pinchState = PINCH_OPENED;
        openTimer = PINCH_OPEN_TIME;
      }
      myServo.write(SERVO_OPEN);
      break;
    case PINCH_OPENED:
      break;
    case INSIDE_CLOTH:
      myServo.write(SERVO_CLOSE);
      break;
    case RELEASE_FLAG://duration of returning back time
      releaseTimer--;
      if(releaseTimer < 0){
        pinchState = RELEASE;
        releaseTimer = PINCH_RELEASE_TIME;
      }
      myServo.write(SERVO_CLOSE);
      break;
    case RELEASE://duration of opening pinch
      finishTimer--;
      if(finishTimer < 0){
//        pinchState = NONE;
        pinchState = INITIALIZE;
        releaseTimer = PINCH_FINISH_TIME;
        steppingMotorControl(STOP);
      }
      myServo.write(SERVO_OPEN);
      break;
    case INITIALIZE:
      initialize();
      break;
  }
  
  delay(30);
}

///////////////////////////////////////////////////////////////////////////////////////////////
void initialize(){
  openTimer = PINCH_OPEN_TIME;
  releaseTimer = PINCH_RELEASE_TIME;
  finishTimer = PINCH_FINISH_TIME;  
  pinchState = NONE;
  steppingMotorControl(NONE);

    // *** servo check ***
  myServo.write(SERVO_OPEN);
  delay(500);
  myServo.write(SERVO_CLOSE);

  delay(100);
}

// ***********************************
// [0]: top natch photoReflecter num
// [1]: inside photoReflecter num,
// [2]: pinchState
// ***********************************
void sendSensorNum(){
  char sendData[3];

  sendData[0] = (unsigned char)(analogRead(photoReflecterPin[0])/4);
  sendData[1] = (unsigned char)(analogRead(photoReflecterPin[1])/4);
  
  switch(pinchState){
    case NONE: sendData[2] = 'n'; break;
    case DETECT_CLOTH: sendData[2] = 'd'; break;
    case PINCH_OPENED: sendData[2] = 'p'; break;
    case INSIDE_CLOTH: sendData[2] = 'i'; break;
    case MOVE: sendData[2] = 'm'; break;
    case RELEASE_FLAG: sendData[2] = 'f'; break;
    case RELEASE: sendData[2] = 'r'; break;
  }

  Wire.write(sendData);
}

// receive wire message & set the pinchState
void receiveWireMessage(int dataByteSize){
  char c;
  while(Wire.available()){
    c = Wire.read(); // 1バイト受信
  }
#ifdef DEBUG
  Serial.print("received message : ");
  Serial.println(c);
#endif
  if(c == 'c') steppingMotorControl(CLOCKWISE); 
  else if(c == 'a') steppingMotorControl(ANTCLOCKWISE);
  
  switch(c){
    case 'n': pinchState = NONE; break;
    case 'd': pinchState = DETECT_CLOTH; break;
    case 'p': pinchState = PINCH_OPENED; break;
    case 'i': pinchState = INSIDE_CLOTH; break;
    case 'm': pinchState = MOVE; break;
    case 'f': pinchState = RELEASE_FLAG; break;
    case 'r': pinchState = RELEASE; break;
    case 's': pinchState = INITIALIZE; break;
  }
}

