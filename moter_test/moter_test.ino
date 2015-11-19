int p1 = 8; //ピンを指定してあげる。モータドライバの5，6ピンを参考に。
int p2 = 9;
int p3 = 6;
int p4 = 7;
void front() //前進
{
  //digitalWrite(p1,HIGH); //このHIGHとLOWで正回転、逆回転を切り替える。
  //digitalWrite(p2,LOW);
  digitalWrite(p3,HIGH);
  digitalWrite(p4,LOW);
}
void back() //後退
{
  //digitalWrite(p1,LOW);
  //digitalWrite(p2,HIGH);
  digitalWrite(p3,LOW);
  digitalWrite(p4,HIGH);
}
void right() //右旋回
{
  //digitalWrite(p1,HIGH);
  //digitalWrite(p2,LOW);
  digitalWrite(p3,LOW);
  digitalWrite(p4,HIGH);
}
void left() //左旋回
{
//digitalWrite(p1,LOW);
//digitalWrite(p2,HIGH);
digitalWrite(p3,HIGH);
digitalWrite(p4,LOW);
}
void stop() //停止
{
  digitalWrite(p1,LOW);
  digitalWrite(p2,LOW);
  digitalWrite(p3,LOW);
  digitalWrite(p4,LOW);
}
void setup()
{
  pinMode(p1,OUTPUT);
  pinMode(p2,OUTPUT);
  pinMode(p3,OUTPUT);
  pinMode(p4,OUTPUT);
}
void loop()
{
  //front(); //前進
  //delay(1000); //1000ミリ秒=1秒間
  //back(); //後退
  //delay(1000);
  right(); //右旋回
  //delay(1000);
  //left(); //左旋回
  //delay(1000);
  //stop(); //停止
  //delay(1000);
}
