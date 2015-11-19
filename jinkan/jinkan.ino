int ledPin = 13;                // LED用のピンを選択する。
int inputPin = 2;               // （PIRセンサー用の）入力ピンを選択する。
int pirState = LOW;             // 動作が感知されないと仮定してから、開始する。
int val = 0;                    // ピンステータスの読み取りは変更可能。
int pinSpeaker = 10;           //PWNピン（デジタル9、10または11番ピン）にスピーカーをセットアップする。

void setup() {
  pinMode(ledPin, OUTPUT);      // 出力をLEDに指定する。
  pinMode(inputPin, INPUT);     // 入力をセンサーに指定する。
  //pinMode(pinSpeaker, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  val = digitalRead(inputPin);  // 入力値を読み取る。
  if (val == HIGH) {            // 入力が「HIGH」であるかどうか確認する。
    digitalWrite(ledPin, HIGH);  // LEDの電源を入れる。
    playTone(300, 160);
    delay(150);

   
    if (pirState == LOW) {
      // たった今電源を入れたところです。
      Serial.println("Motion detected!");
      // 出力の変更は印刷するだけでいいのです。
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW); // LEDの電源を切る。
      playTone(0, 0);
      delay(300);   
      if (pirState == HIGH){
      // たった今電源を切ったところです。
      Serial.println("Motion ended!");
      // 出力の変更は印刷するだけでいいのです。
      pirState = LOW;
    }
  }
}
// 期間の単位はミリ秒、周波数の単位はヘルツ
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        //digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}
