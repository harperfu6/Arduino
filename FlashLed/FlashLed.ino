const int SW  = 2;

void setup(){

  // シリアル通信開始
  Serial.begin(9600);

  // ピンモード
  //pinMode(SW,  INPUT_PULLUP);
}

void loop(){

  // スイッチの値を読み取る
  //int value = digitalRead(2);

//  if (value != HIGH) {
//
//    Serial.println(1);
//  } 

  Serial.println(1);
  delay(1000);
}
