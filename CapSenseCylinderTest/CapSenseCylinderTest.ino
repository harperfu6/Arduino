#define resolution 8
#define mains 60 // 60: north america, japan; 50: most other places

#define refresh 2 * 1000000 / mains

void setup() {
  Serial.begin(115200);
//  Serial.begin(9600);

  // unused pins are fairly insignificant,
  // but pulled low to reduce unknown variables
  for(int i = 2; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

//  for(int i = 8; i < 11; i++)
//    pinMode(i, INPUT);
pinMode(2, INPUT);
pinMode(6, INPUT);
pinMode(8, INPUT);
pinMode(10, INPUT);

  startTimer();
}

void loop() {  
  Serial.print(time(2, B00000001), DEC);
  Serial.print(" ");
  Serial.print(time(6, B00000010), DEC);
  Serial.print(" ");
  Serial.print(time(8, B00000100), DEC);
  Serial.print(" ");
  Serial.println(time(10, B00001000), DEC);

} 

long time(int pin, byte mask) {
  unsigned long count = 0, total = 0;
  while(checkTimer() < refresh) {
    // pinMode is about 6 times slower than assigning
    // DDRB directly, but that pause is important
    pinMode(pin, OUTPUT);
    PORTB = 0;
    pinMode(pin, INPUT);
    while((PINB & mask) == 0)
      count++;
    total++;
  }
  startTimer();
  return (count << resolution) / total;
}

extern volatile unsigned long timer0_overflow_count;

void startTimer() {
  timer0_overflow_count = 0;
  TCNT0 = 0;
}

unsigned long checkTimer() {
  return ((timer0_overflow_count << 8) + TCNT0) << 2;
}

