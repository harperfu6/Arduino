#include <Servo.h>

#define INTERVAL 1
#define SERVO_NUM 9
const int sw_pin = 2;
const int press_pin = 0;
boolean sw_state = false;

Servo g_servo[SERVO_NUM];

void setup() 
{ 
  //for(int i = 0; i < SERVO_NUM; i++){
    //g_servo[i].attach(i+3);
  //}
  g_servo[0].attach(12);//8
  g_servo[1].attach(11);
  g_servo[2].attach(10);
  g_servo[3].attach(9);
  g_servo[4].attach(8);
  g_servo[5].attach(7);
  g_servo[6].attach(6);
  g_servo[7].attach(5);//1
  g_servo[8].attach(4);
  
  pinMode(sw_pin, INPUT);
  Serial.begin(9600);
  
  for(int i = 0; i < SERVO_NUM; i++){
    g_servo[i].write(180);
    //g_servo[i].write(0);
  }
  
} 

void loop() 
{ 
  sw_state = digitalRead(sw_pin);
  int press_value = analogRead(press_pin);
  
  int intensity = map(press_value, 0, 1023, 50, 180);
  Serial.println(intensity);
  
  if(sw_state){
    Serial.println("on!!");
    
    for(int h = 180; h >= 0 ; h--){
    //for(int h = 180; h >= 180 - intensity ; h--){
      int i;
      for(i = 0; i < SERVO_NUM; i++){
        g_servo[i].write(h);
      }
      if(i == 7){
        delay(INTERVAL *2);
      }
      else{
      delay(INTERVAL);
      }
    }
    delay(500);
    
    for(int h = 0; h <= 180; h++){
    //for(int h = 180 - intensity; h <= 180; h++){
      int i;
      for(i = 0; i < SERVO_NUM; i++){
        g_servo[i].write(h);
      }
      if(i == 7){
        delay(INTERVAL * 2);
      }
      else{
      delay(INTERVAL);
      }
    }
    delay(500);
  }

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


