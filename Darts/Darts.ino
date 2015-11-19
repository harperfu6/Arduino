

int NUM[10];
int SDT[7];

//const int pos_array[10][2] = {{9, 14}, {12, 11}, {5, 8}, {20, 16}, {10, 15}, {6, 2}, {13, 17}, {4, 3}, {18, 19}, {1, 7} };
String pos_array[10][2] = {{"09", "14"}, {"12", "11"}, {"05", "08"}, {"20", "16"}, {"10", "15"}, {"06", "02"}, {"13", "17"}, {"04", "03"}, {"18", "19"}, {"01", "07"} };
boolean found;
int findNum, findPos;

void setup(){
  
  for(int i = 0; i < 10; i++){
    NUM[i] = i + 2;
  }
  for(int i = 0; i < 7; i++){
    SDT[i] = i + 12;
  }
  
  for(int i = 0; i < 10; i++){
    pinMode(NUM[i], OUTPUT);
    digitalWrite(NUM[i], LOW);
  }
  
  for(int i = 0; i < 7; i++){
    pinMode(SDT[i], INPUT);
  }
  
  Serial.begin(9600);
}

void loop(){
  
  for(int i = 0; i < 10; i++){
      digitalWrite(NUM[i], HIGH);
      for(int j = 0; j < 7; j++){
        if(digitalRead(SDT[j])){
          findNum = i;
          findPos = j;
          found = true;
        }
      }
      digitalWrite(NUM[i], LOW);
  }
  
  if(found){
    showHitPosition(findNum, findPos);
    found = false;
  }
}

void showHitPosition(int num, int pos){
  
  String HitPosition;
  
  switch(pos){
    case 0:
      Serial.print(pos_array[num][0]);
      Serial.println("3");
      break;
    case 1:
      Serial.print(pos_array[num][0]);
      Serial.println("2");
      break;
    case 2:
      Serial.print(pos_array[num][0]);
      Serial.println("1");
      break;
    case 3:
      switch(num){
        case 0:
          Serial.println("502");
          break;
        case 1:
          Serial.println("501");
          break;
        default:
          break;
      }
      break;
    case 4:
      Serial.print(pos_array[num][1]);
      Serial.println("1");
      break;
    case 5:
      Serial.print(pos_array[num][1]);
      Serial.println("2");
      break;
    case 6:
      Serial.print(pos_array[num][1]);
      Serial.println("3");
      break;
    default:
      break;
  }
}
