int  led = 13;
int  tumami = 0;
int  sentaku = -1;

void setup() {
   Serial.begin(9600);
   pinMode(led, OUTPUT);
   mainMenu();
}

void mainMenu() {
  Serial.println("meinmenyudesu");
  delay(2000);
  Serial.println("dennkiwo tenntousurubaaiha ichiwo");
  delay(4000);
  Serial.println("dennkiwo syoutousurubaaiha niwo");
  delay(4000);
  Serial.println("mouichido menyuwo kikubaaiha sya-puwo");
  delay(4000);
  Serial.println("oshitekudasai"); 
  delay(4000);
  Serial.println("dennwaba'nngo-wa<NUM VAL=01-2345-6789>desu."); 
}

void loop() {
  sentaku = map(analogRead(tumami), 0, 1023, 0, 3);
  switch (sentaku) {
    case 0:
      digitalWrite(led, HIGH);
      break;
    case 1:
      digitalWrite(led, LOW);
      break;
    case 2:
    default:
      mainMenu();
  }
  delay(1000);
}
