int SENDPIN[16];
int RECEIVEPIN[4];
boolean found;
int findNum, findPos;

String pos_array[6][4] = {{"InBull", "", "OutBull", ""}, {"16", "7", "4", "18"}, {"9", "2", "15", "12"}, {"14", "17", "10", "5"}, {"11", "3", "6", "20"}, {"8", "19", "13", "1"} };

void setup() {
  // put your setup code here, to run once:

  //pin allocate
  for(int i = 0; i < 16; i++){
    SENDPIN[i] = i + 22;
  }
  for(int i = 0; i < 4; i++){
    RECEIVEPIN[i] = 13 - i;
  }

  //pin setting
  for(int i = 0; i < 16; i++){
    pinMode(SENDPIN[i], OUTPUT);
    digitalWrite(SENDPIN[i], LOW);
  }
  
  for(int i = 0; i < 4; i++){
    pinMode(RECEIVEPIN[i], INPUT);
  }

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  findNum = 1000;
  findPos = 1000;

  for(int i = 0; i < 16; i++){
      digitalWrite(SENDPIN[i], HIGH);
      for(int j = 0; j < 4; j++){
        if(digitalRead(RECEIVEPIN[j])){
          findNum = i;
          findPos = j;
          found = true;
        }
      }
      digitalWrite(SENDPIN[i], LOW);
  }

  if(found){
    showHitPosition(findNum, findPos);
    found = false;
  }
}

void showHitPosition(int num, int pos){

  int SDT = num % 3;

  if(num == 0){

    if(pos == 1){
      Serial.println("In Bull");
    }
    else if(pos == 3){
      Serial.println("Out Bull");
    }
    
  }
  else{
    switch(SDT){
      case 0: //single
        Serial.print(pos_array[num/3][pos]);
        Serial.println("single");
        break;
      case 1: //triple
        num += 2;
        Serial.print(pos_array[num/3][pos]);
        Serial.println("triple");
        break;
      case 2: //double
        num += 1;
        Serial.print(pos_array[num/3][pos]);
        Serial.println("double");
        break;
      default:
        break;
    }
  }
  
}
