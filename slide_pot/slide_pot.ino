int analogPin0 = 5;     // FeedbackVal
int analogPin1 = 4;     // ポテンショメータのワイプ(中央の端子)に
 
int FeedbackVal = 0;
int val1 = 0;
 
int pwm_a = 5;   //PWM control for motor outputs 1 and 2 is on digital pin 3
int dir_a = 9;  //direction control for motor outputs 1 and 2 is on digital pin 12
int dir_b = 10;  //direction control for motor outputs 1 and 2 is on digital pin 12
 
void setup()
{
    pinMode(dir_a, OUTPUT);
    pinMode(dir_b, OUTPUT);
    pinMode(pwm_a, OUTPUT);
    Serial.begin(9600);
}
 
void loop()
{
    FeedbackVal = analogRead(analogPin0);    // アナログピンを読み取る
    val1 = analogRead(analogPin1);    // アナログピンを読み取る
    //Serial.println(val1 - FeedbackVal);
    Serial.println(val1);
    if(val1 > FeedbackVal){
        int speed = val1 - FeedbackVal;
        if(speed > 7){
            digitalWrite(dir_a, LOW) ;
            digitalWrite(dir_b, HIGH) ;
            analogWrite(pwm_a, speed * 2 + 40);
        }
    }else if(val1 < FeedbackVal){
        int speed = FeedbackVal - val1;
        if(speed > 7){
            digitalWrite(dir_a, HIGH);
            digitalWrite(dir_b, LOW);
            analogWrite(pwm_a, speed * 2 + 40);
        }
    }else{
        analogWrite(pwm_a, 0);
    }
}
