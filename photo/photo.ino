//********************************************************************
//* フォトリフレクタからの入力を表示するプログラム
//********************************************************************
int pin = 0; //
void setup() {
Serial.begin(9600) ;
}
void loop() {
int val;
val = analogRead(pin) ; //アナログ1番ピンからセンサ値を読み込み
Serial.println(val) ; // シリアルモニターへ表示
delay(100) ; // 100ms待つ
}
