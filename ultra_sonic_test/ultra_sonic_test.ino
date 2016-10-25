#include <FlexiTimer2.h>
#include <Servo.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define WIRE_SLAVE_TOP_ADDRESS 8
#define WIRE_SLAVE_TOP_REQUEST_SIZE 6
#define WIRE_SLAVE_MOVE_REQUEST_SIZE 3

SoftwareSerial mySerial(9, 8);


#define STOP 0
#define CLOCKWISE 1
#define ANTCLOCKWISE 2

#define CURTAIN_OPEN 0
#define CURTAIN_CLOSE 1
#define CURTAIN_STOP 2

// PINCH flag statement
//#define NONE 0
//#define DETECT_CLOTH 1
//#define PINCH_OPENED 2
//#define INSIDE_CLOTH 3
//#define MOVE 4
//#define RELEASE 5

//int pinch_state_flag[4] = {NONE, NONE, NONE, NONE};

// stepping motor statement 
//#define STOP 0
//#define CLOCKWISE 1
//#define ANTCLOCKWISE 2

// servo degree setting
//#define SERVO_OPEN 70
//#define SERVO_CLOSE 180

// time between open to close (about 30ms * PINCH_OPEN_TIME)
//#define PINCH_OPEN_TIME 50;
// between release to close 
//#define PINCH_RELEASE_TIME 30;

//int photo_reflecterPin[4][2];
//int servoPin = 2;

int u_sonicPinReceive = 0; // analog
int u_sonicCount[3];

//Servo myServo[4];
//int openTimer[4], releaseTimer[4];

int WIRE_SLAVE_MOVE_ADDRESS[4] = {3,4,5,6}; //4 pinches

//int atTinyControlPin[2] = {3,4};
int cartainPin[2] = {3,4};
#define CURTAIN_TIME 100;
int curtainTime;

char pinch_state;
int photoValue[2] = {0,0};

int humidity = 50;
int temperature = 25;
int bright = 2;

char buf[256]; // 受信用バッファを255文字分確保
//char c; // 受信用文字
int count = 0; // 受信用カウンタ


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(38400);
  Wire.begin();
  
  delay(1000);
  
  for(int i = 0; i < 4; i++){\
    Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
    Wire.write('s'); //初期化
    Wire.endTransmission();
    Serial.println("start");
    delay(500);
  }
  
  curtainTime = CURTAIN_TIME;
  pinMode(cartainPin[0], OUTPUT);
  pinMode(cartainPin[1], OUTPUT);
  digitalWrite(cartainPin[0],LOW);
  digitalWrite(cartainPin[1],LOW);
  
  for(int i = 0; i < 3; i++){
    u_sonicCount[i] = 0;
  }

  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
               int input = analogRead(u_sonicPinReceive);
              Serial.print("ultra: ");
              Serial.print(input);
  
    Serial.println();
//    
////    //u_sonic
////    int input = analogRead(u_sonicPinReceive);
////    if(input >=600 || input <= 400){
////      for(int i = 0; i < 4; i++){
////        Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
////        Wire.write('r');
////        Wire.endTransmission();
////      }
////    }
//
//    //photo_reflector
//    for(int i=0;i<4;i++){
//      Wire.requestFrom(WIRE_SLAVE_MOVE_ADDRESS[i],WIRE_SLAVE_MOVE_REQUEST_SIZE);
//      
//      Serial.print(i+3);
//      Serial.print(" : ");
//      
//      int data_index = 0;
////      int pinch_state = 0;
//      while(Wire.available()){
//
//        unsigned char c = Wire.read();
//        
////        char c = Wire.read();
////        Serial.print((int)c);
////        Serial.print(" ");
////        
//        if(data_index == 0){
//          photoValue[0] = (int)c;
//          Serial.print("photo1: ");
//          Serial.print(photoValue[0]);
//          Serial.print(" ");
//        }
//        else if(data_index == 1){
//          photoValue[1] = (int)c;
//          Serial.print("photo2: ");
//          Serial.print(photoValue[1]);
//          Serial.print(" ");
//        }
//        else if(data_index == 2){
//          pinch_state = c;
//          Serial.print("State: ");
//          Serial.print(pinch_state);
//          Serial.print(" ");
//        }
//        data_index++;
//      }
//      Serial.println("");
//      
//          switch (pinch_state){
//            case 'n':
//              if(photoValue[0] > 300/6){
//                Serial.println("nnnnnnn");
//                pinch_state = 'd'; //detect_cloth
//                Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                Wire.write(pinch_state);
//                Wire.endTransmission();
//              }
//              break;
//            case 'p': //pinch_opened
//            {
//              float threshold = 0.0;
//              if(i == 1){
//                threshold = 150;
//                Serial.println("111111111");
//              }
//              else{
//                threshold = 50;
//              }
//              
//              if(photoValue[1] > threshold){
//                pinch_state = 'i'; //inside_close
//                Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                Wire.write(pinch_state);
//                Wire.endTransmission();
//                
//                if(i == 2){
//                  //stepping
//                  Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                  Wire.write('c'); //stepping start
//                  Wire.endTransmission();
//                  
//                  Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                  Wire.write('m'); //stepping start
//                  Wire.endTransmission();
//                }
//                if(i == 3){
//                  //stepping
//                  Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                  Wire.write('a'); //stepping start
//                  Wire.endTransmission();
//                  
//                  Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                  Wire.write('m'); //stepping start
//                  Wire.endTransmission();
//                }
//              }
//            }
//              break;
//            case 'm':
//            {
//              //u_sonic
////              int input = analogRead(u_sonicPinReceive);
////              Serial.print("ultra: ");
////              Serial.print(input);
//              if(input >= 300){
////              if(u_sonicCount >= 3){
//                for(int i = 0; i < 4; i++){
//                  Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                  Wire.write('f');
//                  Wire.endTransmission();
//                  
//                  if(i == 0){
//                    Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                    Wire.write('c'); //stepping start
//                    Wire.endTransmission();
//                  }
//                  else if(i == 1){
//                    Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                    Wire.write('a'); //stepping start
//                    Wire.endTransmission();
//                  }
//                  else if(i == 2){
//                    Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                    Wire.write('a'); //stepping start
//                    Wire.endTransmission();
//                  }
//                  else if(i == 3){
//                    Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                    Wire.write('c'); //stepping start
//                    Wire.endTransmission();
//                  }
//                }
//              }
//            }
////            }
//            break;
//            case 'r':
//              //return back after rota
//              if(i == 0){
//                Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                Wire.write('a'); //stepping start
//                Wire.endTransmission();
//              }
//              if(i == 1){
//                Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
//                Wire.write('c'); //stepping start
//                Wire.endTransmission();
//              }
////              Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[i]);
////              Wire.write('c'); //stepping start
////              Wire.endTransmission();
////              //カーテン
////              steppingMotorControl(ANTCLOCKWISE);
//              break;
//      
////        data_index++;
//      }      
//      
////      Serial.print(" ||| ");
//      delay(100);
//    }
//    
//    
//    Wire.requestFrom(WIRE_SLAVE_TOP_ADDRESS,WIRE_SLAVE_TOP_REQUEST_SIZE);
//
//    int data_index = 0;
//    while(Wire.available()){
//      char c = Wire.read();
//      Serial.print((int)c);
//      Serial.print(" ");
//      if(data_index == 0){
//        humidity = c;
//      }
//      if(data_index == 1){
//        temperature = c;
//      }
//      if((int)c < 10 && (int)c > 0){
//        if(data_index == 2){
//          Wire.beginTransmission(WIRE_SLAVE_TOP_ADDRESS);
//          Wire.write("2");
//          Wire.endTransmission();
//          Serial.println("index:2");
//          bright = 4;
//        }
//        else if(data_index == 3){
//          Wire.beginTransmission(WIRE_SLAVE_TOP_ADDRESS);
//          Wire.write("3");
//          Wire.endTransmission();
//          Serial.println("index:3");
//        }
//        else if(data_index == 4){
//          Wire.beginTransmission(WIRE_SLAVE_TOP_ADDRESS);
//          Wire.write("4");
//          Wire.endTransmission();
//          Serial.println("index:4");
//          bright = 2;
//        }
//        else if(data_index == 5){
//          Wire.beginTransmission(WIRE_SLAVE_TOP_ADDRESS);
//          Wire.write("5");
//          Wire.endTransmission();
//          Serial.println("index:5");
//          
//          //カーテン
//          curtainControl(CURTAIN_OPEN);
//        }
//      }
//      data_index++;
//    }
//    
//    
//    
//    
//    
//    
//      //送信
////    Tmp:17.5;Hum:40;Ill:1
//    mySerial.print("Tmp:");
//    mySerial.print(temperature);
//    mySerial.print(";Hum:");
//    mySerial.print(humidity);
//    mySerial.print(";Ill:");
//    mySerial.println(bright);
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    
//    Serial.println();
//  //}
//  
//  //受信
//  if(mySerial.available()){
//    char get = mySerial.read();
//    
//    if(get == 'a'){
//      pinch_state = 'd'; //detect_cloth
//      Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[1]);
//      Wire.write(pinch_state);
//      Wire.endTransmission();
//    }
//    else if(get == 'b'){
//      pinch_state = 'i'; //detect_cloth
//      Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[1]);
//      Wire.write(pinch_state);
//      Wire.endTransmission();
//    }
//    else if(get == 'c'){
//      pinch_state = 'd'; //detect_cloth
//      Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[2]);
//      Wire.write(pinch_state);
//      Wire.endTransmission();
//    }
//    else if(get == 'd'){
//      pinch_state = 'i'; //detect_cloth
//      Wire.beginTransmission(WIRE_SLAVE_MOVE_ADDRESS[2]);
//      Wire.write(pinch_state);
//      Wire.endTransmission();
//    }
//    
//  }
//
//
//  
//
//  
  delay(100);
}

void curtainControl(int mode){
  switch(mode){
    case CURTAIN_OPEN:
      digitalWrite(cartainPin[0],HIGH); digitalWrite(cartainPin[1],HIGH);
      break;
    case CURTAIN_CLOSE:
      digitalWrite(cartainPin[0],LOW); digitalWrite(cartainPin[1],HIGH);
      break;
    case CURTAIN_STOP:
      digitalWrite(cartainPin[0],LOW); digitalWrite(cartainPin[1],LOW);
      break;
  }  
}
