#include <Wire.h>

const int sensorNum = 3;//フォトリフレクタの数
int analogPins[sensorNum];//アナログピン
int val[sensorNum];//ループごとのそれぞれのフォトリフレクタの値
int firstVal[sensorNum];//それぞれのフォトリフレクタの初期値
int recDiff = 50;//いくつ変化したらINしたとみなすか
unsigned long startTime = 0.;//INしたときの時間
unsigned long span = 300.;//次のINの認識まで何ミリ秒待つか
boolean recognize = true;//今INを認識する状態か否か


void setup() {
  Serial.begin(9600);
//  Serial.begin(38400);

  Wire.begin();

  for(int i = 0; i < sensorNum; i++){
    analogPins[i] = i;
    firstVal[i] = analogRead(analogPins[i]);  
  }
  
  delay(100);
}

void loop() {
    for(int i = 0; i < sensorNum; i++){
    val[i] = analogRead(analogPins[i]) ; //アナログ0番ピンからセンサ値を読み込み
  }
  
//          Serial.print( val[0], 4 );
//        Serial.print( "\t" );
//        Serial.print( val[1], 4 );
//        Serial.print( "\t" );
//        Serial.print( val[2], 4 );
//        Serial.print( "\n" );
  
    for(int i = 0; i < sensorNum; i++){
  
    if(val[i] > firstVal[i] + recDiff){
      if(recognize){
        if(i == 0){
          Serial.print("capIn;") ; // シリアルモニターへ表示(ボトル)
            print_command(1);
        }
        if(i == 1){
          Serial.print("petIn;") ; // シリアルモニターへ表示(キャップ)
            print_command(2);
        }
        if(i == 2){
          Serial.print("labelIn;"); // シリアルモニターへ表示(ラベル)
            print_command(3);
        }
        startTime = millis();
        recognize = false;
      }
    }
    if(millis() - startTime > span){
      recognize = true;
    }
  }
}

void print_command(int sensor_index){
  
  Wire.beginTransmission(1);
  switch(sensor_index){
    case 1:
      Wire.write("1");
//      Serial.println("caplIn;");
      break;
    case 2:
      Wire.write("2");
//      Serial.print("petIn;") ;
      break;
    case 3:
      Wire.write("3");
//      Serial.print("labelIn;");
      break;
  }
  Wire.endTransmission();
}
