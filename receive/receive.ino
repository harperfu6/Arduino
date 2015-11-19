int getValue;
int firstVal[10];
int logVal[10];
int calib; = 0
double averageVal = 0;

double threshold = 0;
boolean calcCalib = false;
boolean findBasket = false;

double startTime = 0;
double span = 10;

void setup() {
  Serial.begin(9600);
//  Serial.begin(38400);
//  Serial.println("start");
  

}

void loop() {

  if(!calcCalib){
    for(int i = 0; i < 10; i++){
      firstVal[i] = analogRead(0);
      calib += firstVal[i];
    }
    calib /= 10;
    threshold = calib / 2;
    
    calcCalib = true;
  }
  
  for(int i = 0; i < 10; i++){
    logVal[i] = analogRead(0);
    averageVal += logVal[i];
  }
  
  averageVal /= 10;
  
  
   // pulse !
//          digitalWrite( i+2, HIGH );
//          delayMicroseconds( 100 );
//          digitalWrite( i+2, LOW );
//        
//          // mesure the interval 
//          interval[i/2] = pulseIn( i+3, HIGH );

    getValue = analogRead(0);
//     Serial.println(getValue);
     
     if(!findBasket){
       if(getValue < threshold){
         Serial.println("near!!!");
         findBasket = true;
         startTime = millis()
       }
     }
     
     if(findBasket){
       if(abs(average - calib) < 50){
         findBasket = false;
       }
     }
     
//     if(millis() - startTime > span){
//       findBasket = false;
//     }
          
//  delay(40);
}
