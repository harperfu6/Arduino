#include <Servo.h>

#define INTERVAL 1
const int sw_pin1 = 10;
const int sw_pin2 = 11;
boolean sw_state1 = false;
boolean sw_state2 = false;
boolean arm_forward1 = true;
boolean arm_forward2 = true;


Servo g_servo[6];

void setup() 
{ 
  for(int i = 0; i < 6; i++){
    g_servo[i].attach(i + 2);
  }
  pinMode(sw_pin1, INPUT);
  pinMode(sw_pin2, INPUT);
  
  for(int i = 0; i < 6; i++){
    g_servo[i].write(180);
    //delay(interval);
    //Serial.println("Servo3: " + i);
  }
  
  Serial.begin(9600);
  
} 

int Map(int iIn, int iIn1, int iIn2, int iOut1, int iOut2, boolean bConstrain = false )
{
  double dValue = (double)(iIn - iIn1) * (iOut2 - iOut1) / (iIn2 - iIn1) + iOut1;
  int iValue = (0 < dValue) ? (int)(dValue + 0.5) : (int)(dValue - 0.5);
  if( bConstrain )
	{
	  int iOutMin, iOutMax;
	  if( iOut1 < iOut2 )
	  {
		  iOutMin= iOut1;
		  iOutMax= iOut2;
	  }
	  else
	  {
		  iOutMin= iOut2;
		  iOutMax= iOut1;
	  }
	  if( iOutMin > iValue )
	  {
                  return iOutMin;
	  }
	  if( iOutMax < iValue )
	  {
		  return iOutMax;
	  }
  }
  return iValue;
}

void loop() 
{ 
  //int iValue = digitalRead(SWICTH);
  //int iAngle = Map(iValue, 0, 1023, 0, 180, true);
  
  int current_state1 = digitalRead(sw_pin1);
  int current_state2 = digitalRead(sw_pin2);
  
  if(current_state1){
    sw_state1 = true;
  }
  
  if(current_state2){
    sw_state2 = true;
  }
 
  if(sw_state1 && !arm_forward1){
    for(int i = 0; i < 4; i++){
      forward(i, INTERVAL);
    }
//    pre_state = HIGH;
    arm_forward1 = true;
    sw_state1 = false;
  }
  else if(sw_state1 && arm_forward1){
     for(int i = 0; i < 4; i++){
      reverse(i, INTERVAL);
    }
//    pre_state = LOW;
    arm_forward1 = false;
    sw_state1 = false;
  }
  else{
  }
  
  if(sw_state2 && !arm_forward2){
    for(int i = 4; i < 6; i++){
      forward(i, INTERVAL);
    }
//    pre_state = HIGH;
    arm_forward2 = true;
    sw_state2 = false;
  }
  
  else if(sw_state2 && arm_forward2){
     for(int i = 4; i < 6; i++){
      reverse(i, INTERVAL);
    }
//    pre_state = LOW;
    arm_forward2 = false;
    sw_state2 = false;
  }
  
  else{
  }

//  for(int i = 0; i <= 180; i++){
//    for(int j = 0; j < 3; j++){
//    g_servo[j].write(i);
//    }
//    delay(INTERVAL);
//  }
//  
//  delay(1000);
//  
//  for(int i = 180; i >= 0; i--){
//    for(int j = 0; j < 3; j++){
//    g_servo[j].write(i);
//    }
//    delay(INTERVAL);
//  }
//  
//  delay(1000);
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


