#define DEBUG 1

#define SERVOPIN 2
#define DHTPIN 3
#define DHTTYPE DHT11

#define WIRE_SLAVE_ADDRESS 8

char charA_out[10];
int luxNum[4];
float humidity;
float temperature;
boolean clockwise = false;
Servo servo;
DHT dht(DHTPIN, DHTTYPE);
