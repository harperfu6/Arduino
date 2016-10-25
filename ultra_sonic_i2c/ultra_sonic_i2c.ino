#include <Wire.h>
char charA_out[10];

const int u_sensorNum = 3;//測距センサの数
unsigned long interval[u_sensorNum]; //超音波の受信までにかかった時間
unsigned long distance[u_sensorNum]; //距離
unsigned long Distance[u_sensorNum][3]; //直前３回までの距離履歴
unsigned long LowPass[u_sensorNum][2]; //直前２回までのローパスの値

const int locArraySize = 6;
int locationArray[locArraySize];

const int dataArraySize = 10;
unsigned long dataArray0[dataArraySize];
unsigned long dataArray1[dataArraySize];
unsigned long dataArray2[dataArraySize];

unsigned int nearCountA = 0;
unsigned int nearCountB = 0;
unsigned int nearCountC = 0;


double location[2]; //ローパスのため

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
  
  for(int i = 0; i < dataArraySize; i++){
    dataArray0[i] = 1000000000;
    dataArray1[i] = 1000000000;
    dataArray2[i] = 1000000000;
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
        for(int i = 0; i < u_sensorNum * 2; i += 2){
          
          if(i != 2){ //真ん中が壊れているため
          digitalWrite( i+2, HIGH );
          delayMicroseconds( 10 );
          digitalWrite( i+2, LOW );
        
          // mesure the interval 
          interval[i/2] = pulseIn( i+3, HIGH );
        
          delay(5);
          }
        }
//        
        for(int i = 0; i < u_sensorNum; i++){
          distance[i] = interval[i] * 0.017; //cm
        }
        distance[1] = 1000000; //真ん中の値を擬似的にセット
//        
//        Serial.print( distance[0]);
//        Serial.print( "   \t" );
//        Serial.print( distance[1]);
//        Serial.print( "   \t" );
//        Serial.print( distance[2]);
//        Serial.print( "\n" );    
        
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


        //とりあえず一番近い場所をlocation[0]に入れる
        getLocation4(distance);
        
        //場所でローバス
        double tempLocation = lowPass(location[1], location[0]);

        //四捨五入
        int newLocation = (int)floor(tempLocation + 0.7);
        
//        location[1] = location[0];
          location[1] = tempLocation;
//        locationArray[locArraySize - 1] = location[0];
//        int average = (int)averageValue();



//このブロックがメインに送る内容（の一部）
        Serial.print("location:");        
        Serial.print(newLocation);
//        Serial.print(location[0]);
        Serial.print(";");
        
}

double average(unsigned long data[]){

  return (data[0] + data[1] + data[2]) / 3;
}

double lowPass(double lowpass, double data){

  return 0.99*lowpass + 0.01*data;
}

void getLocation1(unsigned long data[]){
  
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

void getLocation2(unsigned long data[]){
  if((data[0] < 1000000 && data[0] > 0) || (data[1] < 1000000 && data[1] > 0) || (data[2] < 1000000 && data[2] > 0)){
    unsigned long minIndex = 0;
    unsigned long minValue = data[0];
    for(int i = 1; i < 3; i++){
      if(data[i] > 0){
        if(data[i] < minValue){
          minIndex = i;
          minValue = data[i];
        }
      }
    }
    location[0] = minIndex + 1;
  }
  else{
    location[0] = 0;
  }
  
  location[1] = location[0];
}

void getLocation3(unsigned long data[]){
  
//        Serial.print( data[0], 4 );
//        Serial.print( "   \t" );
//        Serial.print( data[1], 4 );
//        Serial.print( "   \t" );
//        Serial.print( data[2], 4 );
//        Serial.print( "\n" );
  
  unsigned long sumA = 0;
  unsigned long sumB = 0;
  unsigned long sumC = 0;
  
  nearCountA = (unsigned long)0;
  nearCountB = (unsigned long)0;
  nearCountC = (unsigned long)0;
  
  dataArray0[dataArraySize - 1] = data[0];
  dataArray1[dataArraySize - 1] = data[1];
  dataArray2[dataArraySize - 1] = data[2];
  
  for(int i = 0; i < dataArraySize - 1; i++){
    dataArray0[i] = dataArray0[i+1];
    dataArray1[i] = dataArray1[i+1];
    dataArray2[i] = dataArray2[i+1];
    
    if(dataArray0[i] < (unsigned long)500){
      nearCountA++;
    }
    if(dataArray1[i] < (unsigned long)500){
      nearCountB++;
    }
    if(dataArray2[i] < (unsigned long)500){
      nearCountC++;
    }
    
//        Serial.print("distance0 : ");
//        Serial.print(dataArray0[i], 4 );
//        Serial.print( "   \t" );
//        Serial.print("distance1 : ");
//        Serial.print(dataArray1[i], 4 );
//        Serial.print( "   \t" );
//        Serial.print("distance2 : ");
//        Serial.print(dataArray2[i], 4 );
//        Serial.print( "\n" );
    
    sumA += dataArray0[i];
    sumB += dataArray1[i];
    sumC += dataArray2[i];
  }
  
//      Serial.print("count0 : ");
//        Serial.print(nearCountA);
//        Serial.print( "   \t" );
//        Serial.print("count1 : ");
//        Serial.print(nearCountB);
//        Serial.print( "   \t" );
//        Serial.print("count2 : ");
//        Serial.print(nearCountC);
//        Serial.print( "\n" );
  
  if(nearCountA > 0 || nearCountB > 0 || nearCountC > 0){
    unsigned long maxIndex = 1;
    unsigned long maxValue = nearCountA;
    if(nearCountB > maxValue){
      if(sumB < sumA){
        maxIndex = 2;
        maxValue = nearCountB;
      }
    }
    if(nearCountC > maxValue){
      if(sumC < sumB){
        maxIndex = 3;
      }
    }
    location[0] = maxIndex;
  }
  else{
    location[0] = 0;
  }
  
//  sum0 /= (dataArraySize - 1);
//  sum1 /= (dataArraySize - 1);
//  sum2 /= (dataArraySize - 1);
  
//  if(sum0 < 1000000 || sum1 < 1000000 || sum2 < 1000000){
//    unsigned long minIndex = 1;
//    unsigned long minValue = sum0;
//    if(sum1 < minValue){
//      minIndex = 2;
//      minValue = sum1;
//    }
//    if(sum2 < minValue){
//      minIndex = 3;
//    }
//    location[0] = minIndex;
//  }
//  else{
//    location[0] = 0;
//  }
}

void getLocation4(unsigned long data[]){
  
//        Serial.print( data[0], 4 );
//        Serial.print( "   \t" );
//        Serial.print( data[1], 4 );
//        Serial.print( "   \t" );
//        Serial.print( data[2], 4 );
//        Serial.print( "\n" );
  
  nearCountA = 0;
//  nearCountB = (unsigned long)0;
  nearCountC = 0;
  
  dataArray0[dataArraySize - 1] = data[0];
//  dataArray1[dataArraySize - 1] = data[1];
  dataArray2[dataArraySize - 1] = data[2];
  
  for(int i = 0; i < dataArraySize - 1; i++){
    dataArray0[i] = dataArray0[i+1];
//    dataArray1[i] = dataArray1[i+1];
    dataArray2[i] = dataArray2[i+1];
    
    if(dataArray0[i] < (unsigned long)100){
      nearCountA++;
//      Serial.println("countA!!");
    }
//    if(dataArray1[i] > (unsigned long)20000){
//      nearCountB++;
//    }
    if(dataArray2[i] < (unsigned long)100){
      nearCountC++;
//      Serial.println("countC!!");
    }
    
//        Serial.print("distance0 : ");
//        Serial.print(dataArray0[i], 4 );
//        Serial.print( "   \t" );
//        Serial.print("distance1 : ");
//        Serial.print(dataArray1[i], 4 );
//        Serial.print( "   \t" );
//        Serial.print("distance2 : ");
//        Serial.print(dataArray2[i], 4 );
//        Serial.print( "\n" );
  }
  
//      Serial.print("count0 : ");
//        Serial.print(nearCountA);
//        Serial.print( "   \t" );
//        Serial.print("count1 : ");
//        Serial.print(nearCountB);
//        Serial.print( "   \t" );
//        Serial.print("count2 : ");
//        Serial.print(nearCountC);
//        Serial.print( "\n" );

  nearCountB = 0; //ただいま故障中
  
  if(nearCountA > 0 || nearCountB > 0 || nearCountC > 0){
    unsigned long maxIndex = 1;
    unsigned long maxValue = nearCountA;
//    if(nearCountB > maxValue){
//      if(sumB < sumA){
//        maxIndex = 2;
//        maxValue = nearCountB;
//      }
//    }
    if(nearCountC > maxValue){
      maxIndex = 3;
    }
    location[0] = maxIndex;
  }
  else{
    location[0] = 0;
  }
  
//  sum0 /= (dataArraySize - 1);
//  sum1 /= (dataArraySize - 1);
//  sum2 /= (dataArraySize - 1);
  
//  if(sum0 < 1000000 || sum1 < 1000000 || sum2 < 1000000){
//    unsigned long minIndex = 1;
//    unsigned long minValue = sum0;
//    if(sum1 < minValue){
//      minIndex = 2;
//      minValue = sum1;
//    }
//    if(sum2 < minValue){
//      minIndex = 3;
//    }
//    location[0] = minIndex;
//  }
//  else{
//    location[0] = 0;
//  }
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
//    Serial.print("comeI2C!!!");
    
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



