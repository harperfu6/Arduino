int levelLeds[] = { 
  2,3,4,5,6,7,8,9 };

void setup()
{
  for(int i=0;i<8;i++){
    pinMode(levelLeds[i],OUTPUT);
    digitalWrite(levelLeds[i],LOW);
  }
  Serial.begin(9600);
}

int ecmPin = 0;

void loop()
{
  static int lasEcmLevel = 0;
  int input = analogRead(ecmPin);

  Serial.print(input);
  Serial.print(", ");

  input = abs(input - 512);

  Serial.println(input);

  int ecmLevel = map(input, 50, 380, 0, 8);

//  if(ecmLevel > lasEcmLevel)
//    lasEcmLevel++;
//  else if(ecmLevel < lasEcmLevel)
//    lasEcmLevel--;
  lasEcmLevel = ecmLevel;

  int pos;
  for(pos=0;pos<lasEcmLevel;pos++){
    digitalWrite(levelLeds[pos],HIGH);
  }

  for(;pos<8;pos++){
    digitalWrite(levelLeds[pos],LOW);
  }

  delay(5);
}
