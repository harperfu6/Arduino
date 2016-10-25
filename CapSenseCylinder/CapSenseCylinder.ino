#include <CapSense.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * 10MΩくらいの抵抗器を用います。
 * 抵抗値は感度に影響します。50K～50MΩで実験しました。
 * 抵抗値が大きくなるほど、返ってくる値も大きくなります。
 * Receive pinがsensor pinです。いろいろな大きさのアルミ
 * ホイルや金属片を試してみましょう。センサとなる金属を
 * 紙やプラスチックシートなどでくるむと良い結果が得られます。
 */

CapSense   cs_4_2 = CapSense(4,2);  // ピン4-2間に10MΩ、ピン2にアルミホイル
CapSense   cs_4_6 = CapSense(4,6);
CapSense   cs_4_8 = CapSense(4,8);
CapSense   cs_4_10 = CapSense(4,10);
static int y1[2] = {0};
static int y2[2] = {0};
static int y3[2] = {0};
static int y4[2] = {0};

static int ave1[10] = {0};
static int ave2[10] = {0};
static int ave3[10] = {0};
static int ave4[10] = {0};

float lowpass = 0.9;

void setup() {
   // cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  // 自動キャリブレーションをオフ
   Serial.begin(9600);
//   Serial.begin(115200);
}

void loop() {
    long start = millis();
    long total1 =  cs_4_2.capSense(30);
    long total2 =  cs_4_6.capSense(30);
    long total3 =  cs_4_8.capSense(30);
    long total4 =  cs_4_10.capSense(30);

//    Serial.print(millis() - start);
    //Serial.print("\t");

    y1[1] = lowpass * y1[0] + (1-lowpass) * total1;
    y2[1] = lowpass * y2[0] + (1-lowpass) * total2;
    y3[1] = lowpass * y3[0] + (1-lowpass) * total3;
    y4[1] = lowpass * y4[0] + (1-lowpass) * total4;

    Serial.print(y1[1]);    //ひとつめのセンサの値
    Serial.print(" ");
    Serial.print(y2[1]);
    Serial.print(" ");
    Serial.print(y3[1]);
    Serial.print(" ");
    Serial.println(y4[1]);

    y1[0] = y1[1];
    y2[0] = y2[1];
    y3[0] = y3[1];
    y4[0] = y4[1];

    

//    delay(10);
}


//float getAverage(int ave[]){
//
//  float sum = 0;
//  for(int i = 0; i < 10; i++){
//    sum += ave[i];
//  }
//  return sum / 10;
//}
//
//void reloadArray(int ave[], int newData){
//
//  for(int i = 0; i < 9; i++){
//    ave[i] = ave[i+1];
//  }
//}


