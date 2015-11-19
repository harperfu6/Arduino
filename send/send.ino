void setup() {
  Serial.begin(9600);
  
    //測距センサ
  pinMode( 6, OUTPUT );
  pinMode( 7, INPUT );
  
}

void loop() {
         digitalWrite( 6, HIGH );
          delayMicroseconds( 100 );
          digitalWrite(6, LOW );
         Serial.println(pulseIn( 7, HIGH ));

    delay(50);
}
