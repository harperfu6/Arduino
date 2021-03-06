#include <Servo.h>
#include <MsTimer2.h> 

#define INTERVAL 1
#define OUT_INTERVAL 50 * 2
#define SERVO_NUM 4
const int sw_pin = 2;
const int press_pin = 0;
const int accele_pin = 1;
boolean sw_state = false;
int press_value = 0;
int angle = 0;

boolean big_squere_end = true;
boolean small_end = true;

int each_angle[8];

Servo g_servo[SERVO_NUM];

void communication(){
  //圧力
  for (int i = 0; i < 3; i++){
    press_value = press_value + analogRead(press_pin);
  }
  press_value = press_value / 3;
  
  int LEDintensity = map(press_value, 0, 1023, 0, 255);
  Serial.print("press:");
  Serial.println(LEDintensity);
  
  //スイッチ
  int val = digitalRead(sw_pin);
  if( val == 1) {
    Serial.println("switchOn");
  }
  else {
    Serial.println("switchOff"); 
  }
  
  //加速度
  int x=analogRead(accele_pin) - 755;
  Serial.print("acc:");
  Serial.println(x);
  if (x  < -390){
    Serial.println("garbage:delete");
  }
  
  //受信
  int length = Serial.available();
  if (length > 0) {
    String s = "";
    for (int i = 0; i < length; i++) {
      s += ((char)Serial.read());
    }
    //一度送られてくると同じ文字列が大量にくるので，startsWithで処理
    if (s.startsWith("squ")) {    //of!なら
//四角形のゴミを吸い込んだ時の処理
big_squere();
    } else if (s.startsWith("sma")) {
	//小さいゴミを吸い込んだ時の処理
small();
    } else if (s.startsWith("big")) {
	//大きなゴミを吸い込んだ時の処理
big_squere();
    } else if (s.startsWith("val")) {
	//丸いゴミを吸い込んだ時の処理
big_squere();
    }
  }
}

void setup() 
{ 
  //for(int i = 0; i < SERVO_NUM; i++){
    //g_servo[i].attach(i+3);
  //}
//  g_servo[0].attach(12);//8
//  g_servo[1].attach(11);
//  g_servo[2].attach(10);
//  g_servo[3].attach(9);
  g_servo[0].attach(8);
  g_servo[1].attach(7);
  g_servo[2].attach(6);
  g_servo[3].attach(5);//1
  //g_servo[8].attach(4);
  
  each_angle[0] = 90;
  each_angle[1] = 40;
  each_angle[2] = 40;
  each_angle[3] = 120;
  each_angle[4] = 40;
  each_angle[5] = 80;
  each_angle[6] = 50;
  each_angle[7] = 80;
  
  pinMode(sw_pin, INPUT);
  Serial.begin(9600);
  
  for(int i = 0; i < SERVO_NUM; i++){
    g_servo[i].write(180);
    //g_servo[i].write(0);
  }
  
  MsTimer2::set(200, communication);
  MsTimer2::start();
} 

void loop() 
{ 
  sw_state = digitalRead(sw_pin);
  int press_value = analogRead(press_pin);
  
  int intensity = map(press_value, 0, 1023, 50, 180);
  //Serial.println(intensity);
  //Serial.println(intensity);

sw_state = true;
  if(sw_state){
    Serial.println("on!!");
    
    for(int h = 180; h >= 0 ; h--){
    //for(int h = 180; h >= 180 - intensity ; h--){
      int i;
      for(i = 0; i < SERVO_NUM; i++){
        g_servo[i].write(h);
      }
      delay(INTERVAL);
    }
    delay(500);
    
    for(int h = 0; h <= 180; h++){
    //for(int h = 180 - intensity; h <= 180; h++){
      int i;
      for(i = 0; i < SERVO_NUM; i++){
        g_servo[i].write(h);
      }
      delay(INTERVAL);
    }
    delay(500);
  }

 //communication();
 
// int val = digitalRead(sw_pin);
// 
// if(val){
//   big_squere(); 
//   small();
 }

// sw_state = true;
//  if(sw_state){
//    //if(press_value > 800){
//      big_squere();
//    //}
//    //else{
//      small();
//       //big_circle();
//    //}
//  }


void big_circle(){
  
  int small_angle = 90;
  int big_angle = 80;
  int diff = big_angle - small_angle;
  int test = 80;
  int i = 7;

//  for(int h = 0; h <= 90 ; h++){
//      //for(i = 1; i < 4; i++){
//        g_servo[0].write(180 - h + (90 - each_angle[0]));
//      //}
//       delay(INTERVAL);
//  }
//  delay(OUT_INTERVAL * 5);
//  for(int h = 0; h <= 90; h++){
//      //for(i = 1; i < 4; i++){
//        g_servo[i].write(90 - h);
//      //}
//       delay(INTERVAL);
//  }
//  delay(OUT_INTERVAL * 5);
//  for(int h = 0; h <= 90; h++){
//      //for(i = 1; i < 4; i++){
//        g_servo[i].write(h + (90 - test));
//      //}
//       delay(INTERVAL);
//  }
//  delay(OUT_INTERVAL * 5);
//  for(int h = 50; h <= 90; h++){
//      //for(i = 1; i < 4; i++){
//        g_servo[i].write(h + 90);
//      //}
//       delay(INTERVAL);
//  }

 
  for(int h = 0; h <= 90 ; h++){
      //for(i = 1; i < 4; i++){
        g_servo[0].write(180 - h + (90 - each_angle[0]));
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = 0; h <= 90; h++){
      //for(i = 1; i < 4; i++){
        g_servo[0].write(90 - h);
        g_servo[1].write(180 - h + (90 - each_angle[1]));
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = 0; h <= 90; h++){
      //for(i = 1; i < 4; i++){
        g_servo[0].write(h + (90 - each_angle[0]));
        g_servo[1].write(90 - h);
        g_servo[2].write(180 - h + (90 - each_angle[2]));
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = 0; h <= 90; h++){
      //for(i = 1; i < 4; i++){
        g_servo[0].write(h + 90);
        g_servo[1].write(h + (90 - each_angle[1]));
        g_servo[2].write(90 - h);
        g_servo[3].write(180 - h + (90 - each_angle[3]));
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = 0; h <= 90; h++){
      //for(i = 1; i < 4; i++){
        g_servo[1].write(h + 90);
        g_servo[2].write(h + (90 - each_angle[2]));
        g_servo[3].write(90 - h);
        g_servo[4].write(180 - h + (90 - each_angle[4]));
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = 0; h <= 90; h++){
      //for(i = 1; i < 4; i++){
        g_servo[2].write(h + 90);
        g_servo[3].write(h + (90 - each_angle[3]));
        g_servo[4].write(90 - h);
        g_servo[5].write(180 - h + (90 - each_angle[5]));
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = 0; h <= 90; h++){
      //for(i = 1; i < 4; i++){
        g_servo[3].write(h + 90);
        g_servo[4].write(h + (90 - each_angle[4]));
        g_servo[5].write(90 - h);
        g_servo[6].write(180 - h + (90 - each_angle[6]));
      //}
       delay(INTERVAL);
  }
  delay(OUT_INTERVAL);
  for(int h = 0; h <= 90; h++){
      //for(i = 1; i < 4; i++){
        g_servo[4].write(h + 90);
        g_servo[5].write(h + (90 - each_angle[5]));
        g_servo[6].write(90 - h);
        g_servo[7].write(180 - h + (90 - each_angle[7]));
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = 0; h <= 90; h++){
      //for(i = 1; i < 4; i++){
        g_servo[5].write(h + 90);
        g_servo[6].write(h + (90 - each_angle[6]));
        g_servo[7].write(90 - h);
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = 0; h <= 90; h++){
      //for(i = 1; i < 4; i++){
        g_servo[6].write(h + 90);
        g_servo[7].write(h + (90 - each_angle[7]));
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = 0; h <= 90; h++){
      //for(i = 1; i < 4; i++){
        g_servo[7].write(h + 90);
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL * 10);
}

void big_squere(){
  
  big_squere_end = false;
  
  angle = 180;
  for(int h = angle; h >= 0 ; h--){
      //for(i = 1; i < 4; i++){
        g_servo[0].write(h);
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 1; i < 4; i++){
        g_servo[1].write(h);
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 1; i < 4; i++){
        g_servo[2].write(h);
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 1; i < 4; i++){
        g_servo[0].write(180 - h);
        g_servo[3].write(h);
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 2; i < 5; i++){
        g_servo[1].write(180 - h);
        g_servo[4].write(h);
      //}
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 3; i < 6; i++){
        g_servo[2].write(180 - h);
        g_servo[5].write(h);
      //}
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 4; i < 7; i++){
        g_servo[3].write(180 - h);
        g_servo[6].write(h);
      //}
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 5; i < 8; i++){
        g_servo[4].write(180 - h);
        g_servo[7].write(h);
      //}
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = angle; h >= 0 ; h--){
    g_servo[5].write(180 - h);
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = angle; h >= 0 ; h--){
    g_servo[6].write(180 - h);
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL);
  for(int h = angle; h >= 0 ; h--){
    g_servo[7].write(180 - h);
   delay(INTERVAL);
  }
  communication();
  delay(500);
  
  big_squere_end = true;
}

void small(){
  
  small_end = false;
  
  angle = 10;
  for(int h = angle ; h >= 0 ; h--){
      //for(i = 1; i < 4; i++){
        g_servo[0].write(h);
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL / 2);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 1; i < 4; i++){
        g_servo[1].write(h);
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL / 2);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 1; i < 4; i++){
        g_servo[2].write(h);
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL / 2);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 1; i < 4; i++){
        g_servo[0].write(180 - h);
        g_servo[3].write(h);
      //}
       delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL / 2);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 2; i < 5; i++){
        g_servo[1].write(180 - h);
        g_servo[4].write(h);
      //}
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL / 2);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 3; i < 6; i++){
        g_servo[2].write(180 - h);
        g_servo[5].write(h);
      //}
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL / 2);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 4; i < 7; i++){
        g_servo[3].write(180 - h);
        g_servo[6].write(h);
      //}
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL / 2);
  for(int h = angle; h >= 0 ; h--){
      //for(i = 5; i < 8; i++){
        g_servo[4].write(180 - h);
        g_servo[7].write(h);
      //}
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL / 2);
  for(int h = angle; h >= 0 ; h--){
    g_servo[5].write(180 - h);
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL / 2);
  for(int h = angle; h >= 0 ; h--){
    g_servo[6].write(180 - h);
   delay(INTERVAL);
  }
  communication();
  delay(OUT_INTERVAL / 2);
  for(int h = angle; h >= 0 ; h--){
    g_servo[7].write(180 - h);
   delay(INTERVAL);
  }
  communication();
  delay(500);
  
  small_end = true;
}

void forward(int s_number, int interval){
   for(int i = 0; i <= 180; i++){
    g_servo[s_number].write(i);
    delay(interval);
    //Serial.println("Servo3: " + i);
  }
}

void reverse(int s_number, int interval){
  for(int i = 180; i >= 0; i--){
    g_servo[s_number].write(i);
    delay(interval);
    //Serial.println("Servo3: " + i);
  }
}


