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
static unsigned int L1[2] = {0};
static unsigned int D1 = 0;

float lowpass = 0.85;//original=0.9

void setup() {
   // cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  // 自動キャリブレーションをオフ
   Serial.begin(9600);
}

void loop() {
    long start = millis();
    long total1 =  cs_4_2.capSense(30);
    unsigned int sendData;

    //lowpass
    L1[1] = lowpass * L1[0] + (1 - lowpass) * total1;

    //diff
    D1 = L1[1] - L1[0];

//    Serial.print(millis() - start);
//    Serial.print("\t");

    L1[0] = L1[1];

//    byte low = L1[0] & 127;
//    byte high = (L1[0] >> 7) & 127;
//    byte header = 128;
//    byte footer = 129;

    Serial.write('H');
    Serial.write(highByte(L1[0]));
    Serial.write(lowByte(L1[0]));
//    Serial.write(footer);

//    Serial.write(0);
//    Serial.write(256);


//    Serial.println(header);
//    Serial.println(high);
//    Serial.println(low);
//    Serial.println(footer);

//    Serial.println(L1[0]);    // ひとつめのセンサの値
//      Serial.write(L1[0]);    // ひとつめのセンサの値
//      Serial.println(sendData);    // ひとつめのセンサの値
//      Serial.write(sendData);    // ひとつめのセンサの値
//Serial.write(15);
//    Serial.println(D1);

//delay(10);
}
