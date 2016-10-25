#include <Wire.h>
#include <Servo.h>
#include <DHT.h>
#include "Setting.h"

// *** PIN ASIGN ***
int PHOTO_REFRECTOR_PIN[4] = {2,1,3,0};

void setup() {
  Serial.begin(9600); 
  
  initialize();

  Wire.begin(WIRE_SLAVE_ADDRESS);
  Wire.onRequest(returnSensorNum);
  Wire.onReceive(servoOperate);

  delay(100);

#ifdef DEBUG  // test rotate
  servo.write(10);
  delay(500);
  servo.write(0);
  delay(100);
#endif
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // error 
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

#ifdef DEBUG
  Serial.print("Humidity: "); 
  Serial.print(humidity);
  Serial.println(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C ");

  Serial.print(analogRead(PHOTO_REFRECTOR_PIN[0]));
  Serial.print(" ");
  Serial.print(analogRead(PHOTO_REFRECTOR_PIN[1]));
  Serial.print(" ");
  Serial.print(analogRead(PHOTO_REFRECTOR_PIN[2]));
  Serial.print(" ");
  Serial.println(analogRead(PHOTO_REFRECTOR_PIN[3]));
#endif

  delay(100);
}

void returnSensorNum(){
  char sendData[6];
  sendData[0] = (char)humidity;
  sendData[1] = (char)temperature;
  sendData[2] = (char)(analogRead(PHOTO_REFRECTOR_PIN[0]) / 8);
  sendData[3] = (char)(analogRead(PHOTO_REFRECTOR_PIN[1]) / 8);
  sendData[4] = (char)(analogRead(PHOTO_REFRECTOR_PIN[2]) / 8);
  sendData[5] = (char)(analogRead(PHOTO_REFRECTOR_PIN[3]) / 8);

  Wire.write(sendData);
}

void servoOperate(int a){
    int c;
    while(Wire.available()){
      c = Wire.read(); // 1バイト受信
    }
    Serial.println((int)c * 8);
    
    servoMove((int)c * 8);
}

void servoMove(int angle){
  servo.write(angle);
  delay(500);
}

void initialize(){
  for(int i=0; i<4; i++)  luxNum[i] = 0;
  humidity = 0;
  temperature = 0;
  servo.attach(SERVOPIN);
  dht.begin();

  delay(100);
}
