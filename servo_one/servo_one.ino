#include <Servo.h>

#define INTERVAL 1
const int sw_pin = 10;
boolean pre_state = LOW;

Servo g_servo[3];

void setup() 
{ 
  g_servo[0].attach(11);
  g_servo[1].attach(12);
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
  
  forward(0, INTERVAL);
  //delay(100);
  forward(1, INTERVAL);
  delay(500);
  reverse(0, INTERVAL);
  //delay(100);
  reverse(1, INTERVAL);
  delay(500);
  
  //int current_state = digitalRead(sw_pin);

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


