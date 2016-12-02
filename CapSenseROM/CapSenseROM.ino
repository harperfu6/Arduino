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
static int L1[2] = {0};
static int D1 = 0;

float lowpass = 0.85;//original=0.9

void setup() {
   // cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  // 自動キャリブレーションをオフ
   Serial.begin(9600);
}

void loop() {
    long start = millis();
    long total1 =  cs_4_2.capSense(30);

    //lowpass
    L1[1] = lowpass * L1[0] + (1 - lowpass) * total1;

    //diff
    D1 = L1[1] - L1[0];

//    Serial.print(millis() - start);
//    Serial.print("\t");

    L1[0] = L1[1];

    Serial.println(L1[0]);    // ひとつめのセンサの値
//    Serial.println(D1);

//    delay(10);
}
