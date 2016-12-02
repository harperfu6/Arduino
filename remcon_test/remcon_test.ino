byte val;
bool isOn = true;

int ir_out = 2;
int led = 9;


int last = 0;
unsigned long us = micros();
 
// セットアップ
void setup() {
  // Serial Setting
  Serial.begin(9600);
  
  pinMode(ir_out, OUTPUT);
  pinMode(led, OUTPUT);
}

//実際にデータを送る処理
void sendData(unsigned int data[], int dataSize){

//  //2回繰り返す
//  for(int rep = 0; rep < 2; rep++){
//  for (int cnt = 0; cnt < dataSize; cnt++) {
//    unsigned long len = data[cnt]*10;  // dataは10us単位でON/OFF時間を記録している
//    unsigned long us = micros();
//    do {
//      digitalWrite(ir_out, 1 - (cnt&(1-rep))); // cntが偶数なら赤外線ON、奇数ならOFFのまま
//      delayMicroseconds(8);  // キャリア周波数38kHzでON/OFFするよう時間調整
//      digitalWrite(ir_out, 0);
//      delayMicroseconds(7);
//    } while (long(us + len - micros()) > 0); // 送信時間に達するまでループ
//    //インターバル
//    unsigned long intlen = 9330;
//    unsigned long intus = micros();
//    do {
//      digitalWrite(ir_out, 1); //赤外線ON
//      delayMicroseconds(8);  // キャリア周波数38kHzでON/OFFするよう時間調整
//      digitalWrite(ir_out, 0);
//      delayMicroseconds(7);
//    } while (long(intus + intlen - micros()) > 0); // 送信時間に達するまでループ
//    }
//  }

    for (int cnt = 0; cnt < dataSize; cnt++) {
    unsigned long len = data[cnt]*10;  // dataは10us単位でON/OFF時間を記録している
    unsigned long us = micros();
    do {
      digitalWrite(ir_out, 1 - (cnt&1)); // cntが偶数なら赤外線ON、奇数ならOFFのまま
      delayMicroseconds(8);  // キャリア周波数38kHzでON/OFFするよう時間調整
      digitalWrite(ir_out, 0);
      delayMicroseconds(7);
    } while (long(us + len - micros()) > 0); // 送信時間に達するまでループ
  }

}

void loop() {

//  if(Serial.available() > 0){

//// エアコンオフ
//unsigned int aircon_off[] = {614,184,66,58,65,57,66,58,65,58,65,182,66,57,66,58,65,182,66,182,66,57,66,58,65,58,65,58,66,57,66,58,65,182,66,57,66,58,65,58,65,182,66,182,65,182,65,58,65,57,66,58,65,58,65,58,65,182,66,58,65,57,66,58,65,58,65,58,65,58,66,58,65,58,65,58,65,58,65,58,65,58,66,57,66,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65};
//
////エアコンオン
//unsigned int aircon_on[] = {614,184,66,182,66,182,65,58,65,57,66,182,66,57,66,58,65,182,65,182,65,58,65,58,65,58,65,58,65,58,65,58,65,182,64,58,65,58,65,58,65,182,65,182,65,182,66,58,65,58,65,58,65,58,65,58,66,182,65,58,65,58,65,58,65,58,65,58,65,58,66,58,65,58,66,58,65,58,66,57,66,58,65,58,65,58,65,58,66,57,66,57,66,58,65,58,66,57,66,58,65,58,65,58,65};

// エアコンオフ
unsigned int aircon_off[] = {614,184,66,58,65,57,66,58,65,58,65,182,66,57,66,58,65,182,66,182,66,57,66,58,65,58,65,58,66,57,66,58,65,182,66,57,66,58,65,58,65,182,66,182,65,182,65,58,65,57,66,58,65,58,65,58,65,182,66,58,65,57,66,58,65,58,65,58,65,58,66,58,65,58,65,58,65,58,65,58,65,58,66,57,66,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,933,617,184,65,58,65,58,65,58,65,58,65,182,65,58,65,58,65,182,65,182,66,58,66,58,65,58,65,58,66,57,66,58,65,182,66,57,66,58,65,59,64,182,66,182,65,182,66,58,65,58,65,58,65,58,65,57,66,182,66,57,66,58,65,58,65,58,65,57,66,58,65,58,65,58,65,58,65,57,66,58,66,58,65,58,65,58,65,57,66,58,65,58,65,58,65,58,65,57,66,58,65,58,65,58,65};
//エアコンオン
unsigned int aircon_on[] = {614,184,66,182,66,182,65,58,65,57,66,182,66,57,66,58,65,182,65,182,65,58,65,58,65,58,65,58,65,58,65,58,65,182,64,58,65,58,65,58,65,182,65,182,65,182,66,58,65,58,65,58,65,58,65,58,66,182,65,58,65,58,65,58,65,58,65,58,65,58,66,58,65,58,66,58,65,58,66,57,66,58,65,58,65,58,65,58,66,57,66,57,66,58,65,58,66,57,66,58,65,58,65,58,65,936,614,184,66,182,65,182,66,58,65,58,65,182,66,58,65,57,66,182,66,182,65,58,66,58,66,58,66,58,65,58,65,58,65,182,65,58,65,58,65,58,66,181,65,182,65,182,65,58,65,58,65,58,65,58,65,58,65,182,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,65,58,66,58,65,58,65};


int dataSize;
//    val = Serial.read();
//    Serial.write(val);
//    if(val == 'a'){
//      digitalWrite(led, HIGH);
//      dataSize = sizeof(aircon_on) / sizeof(aircon_on[0]);
//      sendData(aircon_on, dataSize);
//    }
//    else if(val == 'b'){
//      digitalWrite(led, LOW);
//      dataSize = sizeof(aircon_off) / sizeof(aircon_off[0]);
//      sendData(aircon_off, dataSize);
//    }

      digitalWrite(led, HIGH);
      dataSize = sizeof(aircon_on) / sizeof(aircon_on[0]);
      sendData(aircon_on, dataSize);

      delay(3000);
      
      digitalWrite(led, LOW);
      dataSize = sizeof(aircon_off) / sizeof(aircon_off[0]);
      sendData(aircon_off, dataSize);

      delay(3000);
    
//  }
}

