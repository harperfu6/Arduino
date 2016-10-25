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
//CapSense   cs_4_5 = CapSense(4,6);
//CapSense   cs_4_8 = CapSense(4,8);

void setup() {
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  // 自動キャリブレーションをオフ
   Serial.begin(9600);
}

void loop() {

    long start = millis();
    int total1 =  cs_4_2.capSense(30);
//   long total2 =  cs_4_5.capSense(30);]]
//    long total3 =  cs_4_8.capSense(30);

    //Serial.print(millis() - start);
    //Serial.print("\t");

    //Serial.println(total1);    // ひとつめのセンサの値

//    Serial.print("\t");
//    Serial.print(total2);
//    Serial.print("\t");
//    Serial.println(total3);

    //もしProcessingから何か文字を受け取ったら
    //if(Serial.available() > 0){
    Serial.write('H');
    Serial.write(highByte(total1));
    Serial.write(lowByte(total1));
    //Serial.write('\n');
    //}

    delay(40);
}

void establishContact(){
  //while(Serial.available() <= 0)
}

