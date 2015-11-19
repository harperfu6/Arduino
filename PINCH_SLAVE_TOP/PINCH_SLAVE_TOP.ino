#include <Wire.h>
#include <Servo.h>
#include "DHT.h"

#define SERVOPIN 5
#define DHTPIN 6
#define DHTTYPE DHT11

#define WIRE_SLAVE_ADDRESS 8

char charA_out[10];

int PHOTO_REFRECTOR_PIN[4] = {0,1,2,3};
int luxNum[4];
float humidity;
float temperature;
boolean clockwise = false;

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

  delay(100);

  servo.write(45);
  delay(1000);
  servo.write(0);
  delay(1000);
}

void loop() {
  delay(100);

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // error 
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: "); 
  Serial.print(humidity);
  Serial.println(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(temperature);
  Serial.println(" *C ");

  Serial.print(analogRead(0));
  Serial.print(" ");
  Serial.print(analogRead(1));
  Serial.print(" ");
  Serial.print(analogRead(2));
  Serial.print(" ");
  Serial.println(analogRead(3));
  
  delay(100);
}

void returnSensorNum(){
  char sendData[6];
  sendData[0] = (char)humidity;
  sendData[1] = (char)temperature;
  sendData[2] = (char)(analogRead(PHOTO_REFRECTOR_PIN[0])/4);
  sendData[3] = (char)(analogRead(PHOTO_REFRECTOR_PIN[1])/4);
  sendData[4] = (char)(analogRead(PHOTO_REFRECTOR_PIN[2])/4);
  sendData[5] = (char)(analogRead(PHOTO_REFRECTOR_PIN[3])/4);

  Wire.write(sendData);
}

void servoOperate(int a){
  
//  int cnt_buf = 0; `
  
//  Serial.println(Wire.available());
//  if(Wire.available() > 0){
//    delay(100);
//    
//    cnt_buf = max(79,Wire.available());  //受信文字数 最大79文字
//    Serial.println("cnt_buf");
//    Serial.print(cnt_buf);
//    for (int iii = 0; iii < cnt_buf; iii++){
//      charA_out[iii] = Wire.read();
//    }
//    charA_out[cnt_buf] = '\0';  //終端文字
//  }
    int c;
    while(Wire.available()){
      c = Wire.read(); // 1バイト受信
    }
    Serial.println(c);
    
    switch(c){
      case 50:
        servoMove(0);
        break;
      case 51:
        servoMove(90/4);
        break;
      case 52:
        servoMove(180/4);
        break;
      case 53:
        servoMove(270/4);
        break;
    }
//  
//  servoMove(atoi(charA_out));
//  Serial.print("index: ");
//  Serial.println(atoi(charA_out));
  
//  if(!clockwise){
//    servoMove(45);
//    clockwise = true;
//  }
//  else{
//    servoMove(0);
//    clockwise = false;
//  }
}

void servoMove(int angle){
  servo.write(angle);
  delay(100);
}
