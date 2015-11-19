#include <SoftwareSerial.h>


int value = 0;
int cvalue = 0;
SoftwareSerial mySerial(11, 12);

void setup(){
  Serial.begin(9600);
  mySerial.begin(19200);
  pinMode(13,OUTPUT);
  
  pinMode(12,INPUT);
  //mySerial.println("Hello, world?");
}



void loop(){


  //圧力センサ atsuryoku:255みたいに送る
  for (int i = 0; i < 3; i++){
    value = value + analogRead(0);
  }
  value = value / 3;

  int LEDintensity = map(value, 0, 1023, 0, 255);

  Serial.print("atsuryoku:");
  Serial.println(LEDintensity);
  
  //スイッチ on/offを1/0で送る
  delay(100);
  int val = digitalRead(12);
    if( val == 1) {
       Serial.println("switchOn");
    } else {
       Serial.println("switchOff"); 
    }
    
    

  //oFからの受信
  int length = Serial.available();
  if (length > 0) {
    String s = "";
    for (int i = 0; i < length; i++) {
      s += ((char)Serial.read());
    }
    //一度送られてくると同じ文字列が大量にくるので，startsWithで処理
    if (s.startsWith("of!")) {    //of!なら
        digitalWrite(13, HIGH);   
        delay(1000);              
        digitalWrite(13, LOW);   
        delay(1000);              
    }
  }  
  

  //加速度
  int x=analogRead(1) - 755;
  Serial.print("z : ");
  Serial.println(x);
  if (x  < -390){
    Serial.println("garbage:delete");
  }
}


