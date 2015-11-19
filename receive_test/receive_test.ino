int val;//受信データ用の変数を用意

void setup(){
  //シリアル通信開始
  Serial.begin(9600);
  //13ピンをデジタル出力に設定
  pinMode(13,OUTPUT);
}

void loop(){
  if(Serial.available()>0){ //データが来たら
    val=Serial.read();    //データを読み込み、valへ代入
  }
  if(val=='H'){           //valが「H」の場合
    digitalWrite(13,HIGH);//点灯
  }else{                  //valが「L」の場合
    digitalWrite(13,LOW); //消灯
  }
}
