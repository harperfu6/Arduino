#include <Servo.h>

// PINCH flag statement
#define NONE 0
#define DETECT_CLOTH 1
#define PINCH_OPENED 2
#define INSIDE_CLOTH 3
#define RELEASE 4

int pinch_state_flag[4] = {NONE, NONE, NONE, NONE};

// servo degree setting
#define SERVO_OPEN 70
#define SERVO_CLOSE 180

// time between open to close (about 30ms * PINCH_OPEN_TIME)
#define PINCH_OPEN_TIME 15;
// between release to close 
#define PINCH_RELEASE_TIME 10;

// arduino pin setting
  // analog
//#define PHOTO_REFLECTOR_PIN_1 1
//#define PHOTO_REFLECTOR_PIN_2 2
int photo_reflecterPin[4][2];

int analogPinNum = 1;
//for(int i = 0; i < 4; i++){
//  for(int j = 0; j < 2; j++){
//      photo_reflecterPin[i][j] = analogPinNum;
//      analogPinNum++;
//  }
//}

  // digital
//#define SERVO_PIN 10
int servoPin[4] = {9, 10, 11, 12};

//#define RELEASE_SWITCH_PIN 12
//int u_sonicPinSend = 2; //digital
int u_sonicPinReceive = 10; // analog

Servo myServo[4];
//int flag = NONE;
int openTimer[4], releaseTimer[4];


//stepping_motor
//int motorPin1 = 8; // 28BYJ48 の青
//int motorPin2 = 9; // 28BYJ48 のピンク
//int motorPin3 = 10; // 28BYJ48 の黄色
//int motorPin4 = 11; // 28BYJ48 pin のオレンジ</code>

int motorPin[4][4];
int digitalPinNum = 22;
//for(int i = 0; i < 4; i++){
//  for(int j = 0; j < 4; j++){
//      motorPin[i][j] = digitalPinNum;
//      digitalPinNum++;
//  }
//}
int motorSpeed = 1000; //速度。数値が小さいほど速くなる。800以下は脱調して動かない
int count = 0; // count of steps made
int countsperrev = 50;
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};


void setup() {
  // init
  Serial.begin(9600);
  
  for(int i = 0; i < 4; i++){
  for(int j = 0; j < 2; j++){
      photo_reflecterPin[i][j] = analogPinNum;
      analogPinNum++;
  }
}

for(int i = 0; i < 4; i++){
  pinch_state_flag[i] = NONE;
}

for(int i = 0; i < 4; i++){
  for(int j = 0; j < 4; j++){
      motorPin[i][j] = digitalPinNum;
      digitalPinNum++;
  }
}
  
  
//  myServo.attach(SERVO_PIN);
  for(int i = 0; i < 4; i++){
    myServo[i].attach(servoPin[i]);
    
    // servo check
    myServo[i].write(SERVO_OPEN);
    delay(500);
    myServo[i].write(SERVO_CLOSE);
    
      openTimer[i] = PINCH_OPEN_TIME;
    releaseTimer[i] = PINCH_RELEASE_TIME;
  }
  
  //stepping_motor
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      pinMode(motorPin[i][j], OUTPUT);
    }
  }
  
  //u_sonic
//  pinMode(u_sonicPinSend, OUTPUT);
  
//  
//  pinMode(motorPin1, OUTPUT);
//  pinMode(motorPin2, OUTPUT);
//  pinMode(motorPin3, OUTPUT);
//  pinMode(motorPin4, OUTPUT);
 
  delay(100);
}


///////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  
//  Serial.println(analogRead(photo_reflecterPin[0][0]));
//  Serial.print(" ");
//  Serial.println(analogRead(photo_reflecterPin[0][1]));
  
  //u_sonoic(send)
//  digitalWrite( u_sonicPinSend, HIGH );
//  delayMicroseconds( 100 );
//  digitalWrite(u_sonicPinSend, LOW );
  //photo_reflecter and servo
  for(int i = 0; i < 4; i++){
    if((pinch_state_flag[i] == NONE) && analogRead(photo_reflecterPin[i][0]) > 150){
      pinch_state_flag[i] = DETECT_CLOTH;
    }
  }
  for(int i = 0; i < 4; i++){
    if(pinch_state_flag[i] == DETECT_CLOTH){
      openTimer[i]--;
      if(openTimer[i] < 0){
        pinch_state_flag[i] = PINCH_OPENED;
        openTimer[i] = PINCH_OPEN_TIME;
      }
    }
  }
  for(int i = 0; i < 4; i++){
    if((pinch_state_flag[i] == PINCH_OPENED) && analogRead(photo_reflecterPin[i][1]) > 200){
      pinch_state_flag[i] = INSIDE_CLOTH;
    }
  }
  
  for(int i = 0; i < 4; i++){
    if(pinch_state_flag[i] == INSIDE_CLOTH){
        //stepping_motor
        clockwise(i);
        
        //u_sonic
        int input = analogRead(u_sonicPinReceive);
        if(input >=600 || input <= 400){
          for(int i = 0; i < 4; i++){
            pinch_state_flag[i] = RELEASE;
          }
        }
      }
    }
    
    for(int i = 0; i < 4; i++){
      if(pinch_state_flag[i] == RELEASE){
        releaseTimer[i]--;
      }
      if(releaseTimer[i] < 0){
        pinch_state_flag[i] = NONE;
        releaseTimer[i] = PINCH_RELEASE_TIME;
      }
    }
//  }
  
  int sum = 0;
  
  for(int i = 0; i < 4; i++){
    switch(pinch_state_flag[i]){
      case NONE: myServo[i].write(SERVO_CLOSE); break;
      case DETECT_CLOTH: myServo[i].write(SERVO_OPEN); break;
      case INSIDE_CLOTH: myServo[i].write(SERVO_CLOSE); break;
      case RELEASE: myServo[i].write(SERVO_OPEN);  break;  
    }
  }
  

  
  

  // Serial monitoring
//  Serial.print(analogRead(PHOTO_REFLECTOR_PIN_1));
//  Serial.print(" , ");
//  Serial.print(analogRead(PHOTO_REFLECTOR_PIN_2));
//  Serial.print(" , ");
//  Serial.println(flag);

  delay(30);
  
//  Serial.println(pinch_state_flag[0]);
}
///////////////////////////////////////////////////////////////////////////////////////////////

void anticlockwise(int index) //反時計回り
{
 for(int i = 0; i < 8; i++) { setOutput(i, index); delayMicroseconds(motorSpeed); }
} 
 
void clockwise(int index) //時計回り
{ for(int i = 7; i >= 0; i--)
 {
  setOutput(i, index);
  delayMicroseconds(motorSpeed);
 }
}
 
void setOutput(int out, int index)
{
 digitalWrite(motorPin[index][0], bitRead(lookup[out], 0));
 digitalWrite(motorPin[index][1], bitRead(lookup[out], 1));
 digitalWrite(motorPin[index][2], bitRead(lookup[out], 2));
 digitalWrite(motorPin[index][3], bitRead(lookup[out], 3));
}

