#include "wiring_private.h"

#define BoardType0
// #define BoardType1

// #define DEBUG_MODE

volatile uint8_t *inputRegister;
volatile uint8_t *inputRegister2;

const unsigned long ANTI_CHATTERING_TIME = 200; // [ms]

const char TABLE_DEC2HEX[] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

/**
 * hardware dependent code
 */

const uint8_t OUTPUT_PINS[] = {
#ifdef BoardType0
  //2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11
#else
  2, 3, 4, 5, 6, 7, 8, 9
#endif
};
const uint8_t OUTPUT_PINS_LENGTH = sizeof(OUTPUT_PINS) / sizeof(OUTPUT_PINS[0]);

void setupPorts() {
  inputRegister  = portInputRegister(digitalPinToPort(A0));

#ifdef BoardType0
  analogReference(DEFAULT);

  cbi(ADCSRA, ADPS2);
  sbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
#else
  inputRegister2 = portInputRegister(digitalPinToPort(11));

  cbi(ADCSRA, ADPS2);
  sbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
#endif
}

uint8_t customAnalogRead(uint8_t pin) {
  ADMUX = (DEFAULT << 6) | (pin & 0x07);

  sbi(ADCSRA, ADSC);

  while (bit_is_set(ADCSRA, ADSC));

  return (ADCH << 6);
}

inline uint8_t getInputState() {
#ifdef BoardType0
  return (*inputRegister & 0x3f) | (customAnalogRead(6) & 0x80);
#else
  return *inputRegister | (((*inputRegister2) & 24) << 3);
#endif
}

/**
 * hardware independent code
 */

void setup() {
  Serial.begin(9600);

  for (int8_t i = 0; i < OUTPUT_PINS_LENGTH; i++) {
    pinMode(OUTPUT_PINS[i], OUTPUT);
    digitalWrite(OUTPUT_PINS[i], LOW);
  }

  setupPorts();

#ifdef DEBUG_MODE
  checkPerformance();
#endif
}

#ifdef DEBUG_MODE
void checkPerformance() {
  unsigned long startTime = millis();
  for (int i = 0; i < 1000; i++) {
    traversePins();
  }
  unsigned long elapsedTime = millis() - startTime;

  Serial.print(elapsedTime);
  Serial.println(" [ms]");
}
#endif

void loop() {
  traversePins();
}

void traversePins() {
  uint8_t state;

  for (int8_t i = OUTPUT_PINS_LENGTH - 1; i >= 0; i--) {
    digitalWrite(OUTPUT_PINS[i], HIGH);

    state = getInputState();
    if (state != 0) {
      showHitPosition(i, state);
    }

    digitalWrite(OUTPUT_PINS[i], LOW);
  }
}

void showHitPosition(uint8_t outputPinIndex, uint8_t inputState) {
  static unsigned long prevTime = 0;

  unsigned long currTime = millis();
  unsigned long elapsedTime = currTime - prevTime;
  prevTime = currTime;

  if (elapsedTime < ANTI_CHATTERING_TIME) {
    return;
  }

  uint8_t inputBit;
  switch (inputState) {
  case 1:   inputBit = 0; break;
  case 2:   inputBit = 1; break;
  case 4:   inputBit = 2; break;
  case 8:   inputBit = 3; break;
  case 16:  inputBit = 4; break;
  case 32:  inputBit = 5; break;
  case 64:  inputBit = 6; break;
  case 128: inputBit = 7; break;
  default:  return;
  }

#ifdef DEBUG_MODE
  Serial.print(TABLE_DEC2HEX[outputPinIndex]);
  Serial.println(TABLE_DEC2HEX[inputBit]);
#else
  //Serial.write((outputPinIndex << 4) + inputBit);
  Serial.print(outputPinIndex);
  Serial.print(" ");
  Serial.print(inputBit);
  Serial.print("   ");
  
#endif
}
