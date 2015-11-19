void setup(){
  //シリアル通信開始
  Serial.begin(9600);
}

void loop(){
  Serial.print('H');//「H」を送信（点灯）
  delay(1000);      //１秒待つ
  Serial.print('L');//「L」を送信（消灯）
  delay(1000);      //１秒待つ
}
