int interval[3];
double distance[3];
double Distance[3][3];
double LowPass[3][2];

void setup() {
    pinMode( 2, OUTPUT );
    pinMode( 3, INPUT );
    pinMode( 4, OUTPUT );
    pinMode( 5, INPUT );
    pinMode( 6, OUTPUT );
    pinMode( 7, INPUT );
    
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    
    Serial.begin( 9600 );
    
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        Distance[i][j] = 0;
        LowPass[i][j] = 0;
      }
    }
}

void loop() {

    if ( Serial.available() > 0 ) {

//        Serial.read();

        // pulse !
        for(int i = 0; i < 5; i += 2){
          digitalWrite( i+2, HIGH );
          delayMicroseconds( 100 );
          digitalWrite( i+2, LOW );
        
          // mesure the interval 
          interval[i/2] = pulseIn( i+3, HIGH );
        
          delay(100);
        }

        for(int i = 0; i < 3; i++){
          distance[i] = interval[i] * 0.017; //cm
        }
        
        Serial.print( distance[0], 4 );
        Serial.print( "\t" );
        Serial.print( distance[1], 4 );
        Serial.print( "\t" );
        Serial.print( distance[2], 4 );
        Serial.print( "\n" );
        
        for(int i = 0; i < 3; i++){
          if(distance[i] < 100){
            digitalWrite(i+8, HIGH);
          }
          else{
            digitalWrite(i+8, LOW);
          }
        }
        
        //average lowpass
//        for(int i = 0; i < 3; i++){
//          Distance[i][0] = distance[i]
//          Distance[i][1] = Distance[i][0];
//          Distance[i][2] = Distance[i][1];
//        }
//
//        distance1 = average(LowPass1, Distance1);
//        distance2 = average(LowPass2, Distance2);
//        distance3 = average(LowPass3, Distance3);
        
        //lowpass
        for(int i = 0; i < 3; i++){
          LowPass[i][1] = LowPass[i][0];
          LowPass[i][0] = lowPass(LowPass[i][1], distance[i]);
          distance[i] = LowPass[i][0];
        }

//        Serial.print( interval, DEC );
//        Serial.print( "\t" );

//        Serial.print( distance[0], 4 );
//        Serial.print( "\t" );
//        Serial.print( distance[1], 4 );
//        Serial.print( "\t" );
//        Serial.print( distance[2], 4 );
//        Serial.print( "\n" );
      }
}

double average(double data[]){
  
  return (data[0] + data[1] + data[2]) / 3;
}

double lowPass(double lowpass, double data){

  return 0.9*lowpass + 0.1*data;
}

