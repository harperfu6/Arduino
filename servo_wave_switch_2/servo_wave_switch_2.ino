#include <Servo.h>

#define INTERVAL 1
const int sw_pin1 = 10;
const int sw_pin2 = 11;
const int sw_pin3 = 12;
boolean sw_state1 = false;
boolean sw_state2 = false;
boolean sw_state3 = false;
//boolean arm_forward = true;
//boolean arm_forward2 = true;


Servo g_servo[6];

void setup() 
{ 
  for(int i = 0; i < 6; i++){
    g_servo[i].attach(i + 2);
  }
  pinMode(sw_pin1, INPUT);
  pinMode(sw_pin2, INPUT);
  pinMode(sw_pin3, INPUT);
  
  for(int i = 0; i < 6; i++){
    g_servo[i].write(0);
    //delay(interval);
    //Serial.println("Servo3: " + i);
  }
  
  Serial.begin(9600);
  
} 

void loop() 
{ 
  //int iValue = digitalRead(SWICTH);
  //int iAngle = Map(iValue, 0, 1023, 0, 180, true);
  
  int current_state1 = digitalRead(sw_pin1);
  int current_state2 = digitalRead(sw_pin2);
  int current_state3 = digitalRead(sw_pin3);
  
  if(current_state1){
    sw_state1 = true;
    //arm_forward = !arm_forward;
  }
  
  if(current_state2){
    sw_state2 = true;
    //arm_forward = !arm_forward;
  }
  
  if(current_state3){
    sw_state3 = true;
    //arm_forward = !arm_forward;
  }
  
//  if(sw_state1){
//    for(int h = 0; h < 3; h++){
//      for(int i = 0; i <= 120; i++){
//        int j;
//        for(j = h; j < h + 2; j++){
//          g_servo[j].write(i);
//        }
//        if(j > 1){
//          g_servo[j - 1].write(120-i);
//        }
//        delay(INTERVAL);
//      }
//      delay(250);
//    }
//    
//    for(int h = 0; h <= 120; h++){
//      for(int i = 2; i < 4; i++){
//        g_servo[i].write(120 - h);
//      }
//      delay(INTERVAL);
//    }
//    delay(250);
//    sw_state1 = false;
//  }
 
  if(sw_state1){
    for(int h = 0; h <= 100; h++){
      for(int i = 0; i < 2; i++){
        g_servo[i].write(h);
      }
      delay(INTERVAL);
    }
   
    delay(150);
    
    for(int h = 0; h <= 100; h++){
      for(int i = 1; i < 3; i++){
        g_servo[i].write(h);
      }
      g_servo[0].write(100-h);
      delay(INTERVAL);
    }
    
    delay(150);
    
     for(int h = 0; h <= 100; h++){
      for(int i = 2; i < 4; i++){
        g_servo[i].write(h);
      }
      g_servo[1].write(100-h);
      delay(INTERVAL);
    }
    
    delay(150);
    
     for(int h = 0; h <= 100; h++){
      for(int i = 2; i < 4; i++){
        g_servo[i].write(100 - h);
      }
      delay(INTERVAL);
    }
    
    delay(150);
    
//    pre_state = HIGH;
    //arm_forward1 = true;
    sw_state1 = false;
  }
  
   if(sw_state2){
    for(int h = 0; h <= 20; h++){
      for(int i = 0; i < 2; i++){
        g_servo[i].write(h);
      }
      delay(INTERVAL);
    }
   
    delay(150);
    
    for(int h = 0; h <= 20; h++){
      for(int i = 1; i < 3; i++){
        g_servo[i].write(h);
      }
      g_servo[0].write(20-h);
      delay(INTERVAL);
    }
    
    delay(150);
    
//     for(int h = 0; h <= 45; h++){
//      for(int i = 2; i < 4; i++){
//        g_servo[i].write(h);
//      }
//      g_servo[1].write(45-h);
//      delay(INTERVAL);
//    }

    for(int h = 0; h <= 20; h++){
//      for(int i = 2; i < 4; i++){
//        g_servo[i].write(h);
//      }
      g_servo[2].write(h);
      g_servo[3].write(h+10);
      g_servo[1].write(20-h);
      delay(INTERVAL);
    }
    
    delay(150);
    
    for(int h = 0; h <= 20; h++){
      for(int i = 2; i < 4; i++){
        g_servo[i].write(20-h);
      }
      delay(INTERVAL);
    }
    
    delay(150);
  
//    pre_state = HIGH;
    //arm_forward1 = true;
    sw_state2 = false;
  }
  
  
  
  if(sw_state3){
//    for(int i = 0; i < 4; i++){
//      forward(i, INTERVAL);
//    }
//    pre_state = HIGH;
    //arm_forward = true;
    
  for(int i = 0; i <= 60; i++){
    g_servo[0].write(i);
    delay(INTERVAL);
    //Serial.println("Servo3: " + i);
  }
  
  delay(75);
  
  for(int i = 0; i <= 60; i++){
    g_servo[0].write(60 - i);
    g_servo[1].write(i);
    delay(INTERVAL);
    //Serial.println("Servo3: " + i);
  }
  
  delay(75);
    
   for(int i = 0; i <= 60; i++){
    g_servo[1].write(60 - i);
    g_servo[2].write(i);
    delay(INTERVAL);
    //Serial.println("Servo3: " + i);
  }
  
  delay(75);
   
   for(int i = 0; i <= 60; i++){
    g_servo[2].write(60 - i);
    g_servo[3].write(i);
    delay(INTERVAL);
    //Serial.println("Servo3: " + i);
  }
  
  delay(75);
  
  for(int i = 0; i <= 60; i++){
    g_servo[3].write(60 - i);
    delay(INTERVAL);
    //Serial.println("Servo3: " + i);
  }
  
  //delay(50);
    
    sw_state3 = false;
  }
  
} 

void forward(int s_number, int interval){
   for(int i = 0; i <= 90; i++){
    g_servo[s_number].write(i);
    delay(interval);
    //Serial.println("Servo3: " + i);
  }
}

void reverse(int s_number, int interval){
  for(int i = 90; i >= 0; i--){
    g_servo[s_number].write(i);
    delay(interval);
    //Serial.println("Servo3: " + i);
  }
}


