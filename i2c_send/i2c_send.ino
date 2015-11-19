#include <Wire.h>
 
void setup() {
  
//  Serial.begin(9600);
  Wire.begin();
  pinMode(2,INPUT) ;    //スイッチに接続ピンをデジタル入力に設定  
}
 
void loop() {
  
  if (digitalRead(2) == HIGH) {     //スイッチの状態を調べる
//    Serial.println("on!!");
    //digitalWrite(13,HIGH) ;      //スイッチが押されているならLEDを点灯
    print_command();
  }
  else{
    Serial.println("off!!");
    //digitalWrite(13,LOW) ;       //スイッチが押されていないならLEDを消灯
  }
   
}

//コマンド出力
void print_command( ){
  
  Wire.beginTransmission(1);
  Wire.write("10");
  Wire.endTransmission();
}
