#include <Wire.h>

#define WIRE_SLAVE_TOP_ADDRESS 8
#define WIRE_SLAVE_TOP_REQUEST_SIZE 6
#define WIRE_SLAVE_MOVE_REQUEST_SIZE 3

int WIRE_SLAVE_MOVE_ADDRESS[4] = {3,4,5,6};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  

//  if(Serial.available() > 0){
//    Wire.beginTransmission(WIRE_SLAVE_TOP_ADDRESS);
//    int n = Serial.read();
//    Wire.write((char)n);
//    Wire.endTransmission(); 
//  }else{
    //Wire.requestFrom(WIRE_SLAVE_TOP_ADDRESS,WIRE_SLAVE_TOP_REQUEST_SIZE);

    //while(Wire.available()){
    //  char c = Wire.read();
    //  Serial.print((int)c);
    //  Serial.print(" ");
    //}
    Serial.println();

    for(int i=0;i<4;i++){
      Wire.requestFrom(WIRE_SLAVE_MOVE_ADDRESS[i],WIRE_SLAVE_TOP_REQUEST_SIZE);
      
      Serial.print(i+3);
      Serial.print(" : ");
      while(Wire.available()){
        char c = Wire.read();
        Serial.print((int)c);
        Serial.print(" ");
      }
      Serial.print(" ||| ");
      delay(100);
    }
    Serial.println();
  //}
  
  delay(500);
}
