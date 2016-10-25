#include <Wire.h>
#include <Servo.h>
#include "DHT.h"

#define SERVOPIN 2
#define DHTPIN 3
#define DHTTYPE DHT11

#define WIRE_SLAVE_ADDRESS 8

#define ROTATION_TIME 10;
#define INTERVAL_TIME 10;
#define DIFF_ANGLE 1
char charA_out[10];

//int PHOTO_REFRECTOR_PIN[4] = {0,1,2,3};
int PHOTO_REFRECTOR_PIN[4] = {2,1,3,0};
int luxNum[4];
float humidity;
float temperature;
boolean clockwise = false;

int totalAngle, diffAngle;
int rotationCount, finishCount;
boolean isRotation = false;
boolean rotationFinish = false;
int startAngle, goalAngle;
boolean plusFlag = false;
boolean minusFlag = false;
int currentAngle;

Servo servo;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
//initialize
  for(int i=0; i<4; i++)  luxNum[i] = 0;
  humidity = 0;
  temperature = 0;
  servo.attach(SERVOPIN);
  dht.begin();

  Wire.begin(WIRE_SLAVE_ADDRESS);
  Wire.onRequest(returnSensorNum);
  Wire.onReceive(servoOperate);
  
  rotationCount = ROTATION_TIME;
  finishCount = INTERVAL_TIME;

  delay(100);

//  servo.write(10);
//  delay(1000);
  servo.write(0);
  delay(1000);
  
  startAngle = 0;
  currentAngle = 0;
}

void loop() {
//  delay(100);
  
//  if(Serial.available()){
//    int angle = Serial.read();
//    testServo(angle);
//  }

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // error 
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  if(isRotation){
    if(plusFlag){
      servoMove(currentAngle + DIFF_ANGLE);
      currentAngle += DIFF_ANGLE;
    }
    else{
      servoMove(currentAngle - DIFF_ANGLE);
      currentAngle -= DIFF_ANGLE;
    }
  }
  
  if((plusFlag && currentAngle > goalAngle) || (minusFlag && currentAngle < goalAngle)){
    isRotation = false;
    rotationCount = ROTATION_TIME;
    rotationFinish = true;
    startAngle = goalAngle;
    currentAngle = goalAngle;
    plusFlag = false;
    minusFlag = false;
  }
  
  if(rotationFinish){
    finishCount--;
  }
  
  if(finishCount < 0){
    rotationFinish = false;
    finishCount = INTERVAL_TIME;
  }

//  Serial.print("Humidity: "); 
//  Serial.print(humidity);
//  Serial.println(" %\t");
//  Serial.print("Temperature: "); 
//  Serial.print(temperature);
//  Serial.println(" *C ");

//  Serial.print(analogRead(PHOTO_REFRECTOR_PIN[0]));
//  Serial.print(" ");
//  Serial.print(analogRead(PHOTO_REFRECTOR_PIN[1]));
//  Serial.print(" ");
//  Serial.print(analogRead(PHOTO_REFRECTOR_PIN[2]));
//  Serial.print(" ");
//  Serial.println(analogRead(PHOTO_REFRECTOR_PIN[3]));
  
  delay(200);
}

void returnSensorNum(){
  char sendData[6];
  sendData[0] = (char)humidity;
  sendData[1] = (char)temperature;
  sendData[2] = (char)(analogRead(PHOTO_REFRECTOR_PIN[0]) / 8);
  sendData[3] = (char)(analogRead(PHOTO_REFRECTOR_PIN[1]) / 8);
  sendData[4] = (char)(analogRead(PHOTO_REFRECTOR_PIN[2]) / 8);
  sendData[5] = (char)(analogRead(PHOTO_REFRECTOR_PIN[3]) / 8);
  
//  Serial.print((int)sendData[2] * 8);
//  Serial.print(" ");
//  Serial.print((int)sendData[3] * 8);
//  Serial.print(" ");
//  Serial.print((int)sendData[4] * 8);
//  Serial.print(" ");
//  Serial.print((int)sendData[5] * 8);
//  Serial.println(" ");

  Wire.write(sendData);
}

void servoOperate(int a){
  
  Serial.println("gettttttt");
  
    unsigned char c;
    while(Wire.available()){
      c = Wire.read(); // 1バイト受信
    }
    Serial.println((int)c);

    char getChar = c;
    
    if(!isRotation && !rotationFinish){
    if(c == 'a'){
      goalAngle = 0;
      Serial.println("aaaaa");
    }
    else if(c == 'b'){
      goalAngle = 22;
      Serial.println("bbbbb");
    }
    else if(c == 'c'){
      goalAngle = 45;
      Serial.println("ccccc");
    }
    
    isRotation = true;
    
    Serial.print("goalAngle: ");
    Serial.println(goalAngle);
    Serial.print("StartAngle: ");
    Serial.println(startAngle);
    
    
    if(goalAngle >= startAngle){
      plusFlag = true;
    }
    else{
      minusFlag = true;
    }
    
//    servoMove(totalAngle)

  }
}

void testServo(int angle){
  switch(angle){
      case 50:
        servoMove(0);
        break;
      case 51:
        servoMove(90/(360/105));
        break;
      case 52:
        servoMove(180/(360/105));
        break;
      case 53:
        servoMove(270/(360/105));
        break;
    }
}

void servoMove(int angle){
  servo.write(angle);
//  delay(5000);
}
