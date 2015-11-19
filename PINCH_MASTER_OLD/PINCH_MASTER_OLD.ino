#include <Wire.h>

#define WIRE_SLAVE_TOP_ADDRESS 8
#define WIRE_SLACE_TOP_REQUEST_SIZE 6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  

//  if(Serial.available() > 0){
//    Wire.beginTransmission(WIRE_SLAVE_TOP_ADDRESS);
//    int n = Serial.read();
//    Wire.write((char)n);
//    Wire.endTransmission(); 
//  }else{
    Wire.requestFrom(WIRE_SLAVE_TOP_ADDRESS,WIRE_SLACE_TOP_REQUEST_SIZE);

    int data_index = 0;
    while(Wire.available()){
      char c = Wire.read();
      Serial.print((int)c);
      Serial.print(" ");
      if((int)c < 10 && (int)c > 0){
        if(data_index == 2){
          Wire.beginTransmission(WIRE_SLAVE_TOP_ADDRESS);
          Wire.write("2");
          Wire.endTransmission();
          Serial.println("index:2");
        }
        else if(data_index == 3){
          Wire.beginTransmission(WIRE_SLAVE_TOP_ADDRESS);
          Wire.write("3");
          Wire.endTransmission();
          Serial.println("index:3");
        }
        else if(data_index == 4){
          Wire.beginTransmission(WIRE_SLAVE_TOP_ADDRESS);
          Wire.write("4");
          Wire.endTransmission();
          Serial.println("index:4");
        }
        else if(data_index == 5){
          Wire.beginTransmission(WIRE_SLAVE_TOP_ADDRESS);
          Wire.write("5");
          Wire.endTransmission();
          Serial.println("index:5");
        }
      }
      data_index++;
    }
    Serial.println();
//  }
  
  delay(200);
}
