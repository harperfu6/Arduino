//7seg I2c
 
#include <Wire.h>

char charA_out[10];
boolean light = false;
 
void setup() {
  Serial.begin(9600);
  
  pinMode(12,OUTPUT);
  Wire.begin(1);
  Wire.onReceive(myReadLine);
 
}
 
void loop() {
  delay(100);
//  digitalWrite(13, HIGH);
}
 
void myReadLine(int a){
  int cnt_buf = 0; 
  
  //受信したら
  if(Wire.available() > 0){
//    digitalWrite(13, HIGH);
    delay(100);
    printf("%d\n", 10);
    
    cnt_buf = max(79,Wire.available());  //受信文字数 最大79文字
    for (int iii = 0; iii < cnt_buf; iii++){
      charA_out[iii] = Wire.read();
    }
    charA_out[cnt_buf] = '\0';  //終端文字
  }
  led_switch(atoi(charA_out));
  
} 

void led_switch(int command){
  
  switch(command){
    case 10:
      Serial.println(command);
      if(!light){
        digitalWrite(12, HIGH);
        light = true;
      }
      else{
        digitalWrite(12, LOW);
        light = false;
      }
      break;
  }
//  if(command == 10){
//    if(!light){
//        Serial.println(command);
//      digitalWrite(12, HIGH);
//      light = true;
//    }
//    else{
//      digitalWrite(12, LOW);
//      light = false;
//    }
//  }
}
