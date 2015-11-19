#include <Servo.h>

#define INTERVAL 1
const int sw_pin = 10;
int pre_state = LOW;


Servo g_servo[6];

void setup() 
{ 
  for(int i = 0; i < 6; i++){
    g_servo[i].attach(i + 2);
  }
  pinMode(sw_pin, INPUT);
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
  
  int current_state = digitalRead(sw_pin);
  if(current_state && !pre_state){
    for(int i = 0; i < 6; i++){
      forward(i, INTERVAL);
    }
    pre_state = HIGH;
  }
  else if(!current_state && pre_state){
     for(int i = 0; i < 6; i++){
      reverse(i, INTERVAL);
    }
    pre_state = LOW;
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


