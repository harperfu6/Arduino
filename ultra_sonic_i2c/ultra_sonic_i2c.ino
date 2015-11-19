#include <Wire.h>
char charA_out[10];

const int u_sensorNum = 3;//測距センサの数
int interval[u_sensorNum]; //超音波の受信までにかかった時間
double distance[u_sensorNum]; //距離
double Distance[u_sensorNum][3]; //直前３回までの距離履歴
double LowPass[u_sensorNum][2]; //直前２回までのローパスの値

//int location = 0;
const int locArraySize = 6;
int locationArray[locArraySize];
//int locationAverageArray[]

int location[2];

void setup() {
  Serial.begin(9600);
//  Serial.begin(38400);
//  Serial.println("start");
  
  //測距センサ
  pinMode( 2, OUTPUT );
  pinMode( 3, INPUT );
  pinMode( 4, OUTPUT );
  pinMode( 5, INPUT );
  pinMode( 6, OUTPUT );
  pinMode( 7, INPUT );
  
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
    
  //LED(測距テスト用)
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
    
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      Distance[i][j] = 0;
      LowPass[i][j] = 0;
    }
  }
  
  for(int i = 0; i < locArraySize; i++){
    locationArray[i] = 0;
  }
  
  for(int i = 0; i < 2; i++){
    location[i] = 0;
  }
  
  Wire.begin(1);
  Wire.onReceive(myReadLine);
  
  delay(100);
}

void loop() {
  
//  if ( Serial.available() > 0 ) {

//        Serial.read();

        // pulse !
        for(int i = 0; i < u_sensorNum + 2; i += 2){
//  for(int i = 4; i < 5; i += 2){
          digitalWrite( i+2, HIGH );
          delayMicroseconds( 50 );
          digitalWrite( i+2, LOW );
        
          // mesure the interval 
          interval[i/2] = pulseIn( i+3, HIGH );
        
          delay(50);
        }
//        
        for(int i = 0; i < u_sensorNum; i++){
          distance[i] = interval[i] * 0.017; //cm
//          LowPass[i][0] = distance[i];
        }
//        
//        Serial.print( distance[0], 4 );
//        Serial.print( "\t" );
//        Serial.print( distance[1], 4 );
//        Serial.print( "\t" );
//        Serial.print( distance[2], 4 );
//        Serial.print( "\n" );
        
//        if(distance[2] > 0 && distance[2] < 60){
//          Serial.print("location:");
//          Serial.print("2");
//          Serial.print(";");  
//        }
//        else{
//          Serial.print("location:");
//          Serial.print("0");
//          Serial.print(";");
//        }
        
//        
//        Serial.print("left:");
//        Serial.print((int)distance[0]);
//        Serial.print(";");
//        Serial.print("center:");
//        Serial.print((int)distance[1]);
//        Serial.print(";");
//        Serial.print("right:");
//        Serial.print((int)distance[2]);
//        Serial.print(";");
        
//        for(int i = 0; i < u_sensorNum; i++){
//          if(distance[i] < 100){
//            digitalWrite(i+8, HIGH);
//          }
//          else{
//            digitalWrite(i+8, LOW);
//          }
//        }
        
        //average lowpass
//        for(int i = 0; i < u_sensorNum; i++){
//          Distance[i][0] = distance[i]
//          Distance[i][1] = Distance[i][0];
//          Distance[i][2] = Distance[i][1];
//        }
//
//        distance1 = average(LowPass1, Distance1);
//        distance2 = average(LowPass2, Distance2);
//        distance3 = average(LowPass3, Distance3);
        
        //lowpass
//        for(int i = 0; i < u_sensorNum; i++){
//          LowPass[i][1] = LowPass[i][0];
//          LowPass[i][0] = lowPass(LowPass[i][1], distance[i]);
//          distance[i] = LowPass[i][0];
//        }
        
//        location = getLocation(distance);




        getLocation2(distance);
        locationArray[locArraySize - 1] = location[0];
        int average = (int)averageValue();
        Serial.print("location:");        
        Serial.print(average);
        Serial.print(";");



   
//        Serial.println(location[0]);
//        Serial.println((int)averageValue());
          //int average = (int)averageValue();
          
//          Serial.print("location:");
//          Serial.print((int)averageValue());
////          Serial.print("2");
//          Serial.print(";");
          
//          delay(15);
          
        
//        if(average == 0){
//          digitalWrite(8, LOW);
//          digitalWrite(9, LOW);
//          digitalWrite(10, LOW);
//        }
//        else if(average == 1){
//          digitalWrite(8, HIGH);
//          digitalWrite(9, LOW);
//          digitalWrite(10, LOW);
//        }
//        else if(average == 2){
//          digitalWrite(8, LOW);
//          digitalWrite(9, HIGH);
//          digitalWrite(10, LOW);
//        }
//        else if(average == 3){
//          digitalWrite(8, LOW);
//          digitalWrite(9, LOW);
//          digitalWrite(10, HIGH);
//        }
        
//        locationArray[locArraySize - 1] = location;
//        int average = (int)averageValue();
//        Serial.println(average);

//        Serial.print( interval, DEC );
//        Serial.print( "\t" );

//      }
}

double average(double data[]){
  
  return (data[0] + data[1] + data[2]) / 3;
}

double lowPass(double lowpass, double data){

  return 0.9*lowpass + 0.1*data;
}

void getLocation1(double data[]){
  
  if(data[0] > 100 && data[1] > 100 && data[2] > 100){
    location[0] = 0;
  }
  else if(data[0] < 100 && data[1] > 100 && data[2] > 100){
    location[0] = 1;
  }
  else if(data[0] > 100 && data[1] > 100 && data[2] < 100){
    location[0] = 3;
  }
  else if(data[0] > 100 && data[1] < 100 && data[2] > 100){
    location[0] = 2;
  }
  else if(data[0] < 100 && data[1] < 100 && data[2] > 100 && (location[1] == 3 || location[1] == 2)){
    location[0] = 2;
  }
  else if(data[0] > 100 && data[1] < 100 && data[2] < 100 && (location[1] == 1 || location[1] == 2)){
    location[0] = 2;
  }
  else{
    location[0] = location[1];
  }
  
  location[1] = location[0];
}

void getLocation2(double data[]){
  if((data[0] < 100 && data[0] > 0) || (data[1] < 100 && data[1] > 0) || (data[2] < 100 && data[2] > 0)){
    int minIndex = 0;
    int minValue = data[0];
    for(int i = 1; i < 3; i++){
      if(data[i] < minValue){
        minIndex = i;
        minValue = data[i];
      }
    }
    location[0] = minIndex + 1;
  }
  else{
    location[0] = 0;
  }
  
  location[1] = location[0];
}

double averageValue(){
  int sum = 0;
  for(int i = 0; i < locArraySize - 1; i++){
    locationArray[i] = locationArray[i+1];
    sum += locationArray[i];
  }
  
  sum /= locArraySize - 1;
  
  return floor(sum + 0.5);
}

void myReadLine(int a){
  int cnt_buf = 0; 
  
//  Serial.println("get!!");
  //受信したら
  if(Wire.available() > 0){
    delay(100);
    
    cnt_buf = max(79,Wire.available());  //受信文字数 最大79文字
    for (int iii = 0; iii < cnt_buf; iii++){
      charA_out[iii] = Wire.read();
    }
    charA_out[cnt_buf] = '\0';  //終端文字
  }
  get_photo_reflector(atoi(charA_out));
  
}

void get_photo_reflector(int index){
    switch(index){
    case 1:
      Serial.print("capIn;"); // シリアルモニターへ表示(ボトル)
      break;
    case 2:
      Serial.print("petIn;") ; // シリアルモニターへ表示(キャップ)
      break;
    case 3:
      Serial.print("labelIn;"); // シリアルモニターへ表示(ラベル)
      break;
  }
}



