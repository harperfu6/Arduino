#include <Servo.h>

#define INTERVAL 1

Servo g_servo;

void setup() 
{ 
  g_servo.attach(11);
  //pinMode(sw_pin, INPUT);
  Serial.begin(9600);
  
} 

void loop(){
  
  forward(INTERVAL);
  delay(500);
  reverse(INTERVAL);
  delay(500);
}

void forward(int interval){
   for(int i = 0; i <= 180; i++){
    g_servo.write(i);
    delay(interval);
    //Serial.println("Servo3: " + i);
  }
}

void reverse(int interval){
  for(int i = 180; i >= 0; i--){
    g_servo.write(i);
    delay(interval);
    //Serial.println("Servo3: " + i);
  }
}
