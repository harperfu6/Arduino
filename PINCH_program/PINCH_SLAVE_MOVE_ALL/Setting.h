#define DEBUG 1

// Set the wire slave address 3 -- 6
#define WIRE_SLAVE_ADDRESS 5

// servo degree setting
#define SERVO_OPEN 70
#define SERVO_CLOSE 180

// time between open to close (about 30ms * PINCH_OPEN_TIME)
#define PINCH_OPEN_TIME 5;
// between release to close 
#define PINCH_RELEASE_TIME 300;
#define PINCH_FINISH_TIME 300;

// PINCH flag statement
#define NONE 0
#define DETECT_CLOTH 1
#define PINCH_OPENED 2
#define INSIDE_CLOTH 3
#define MOVE 4
#define RELEASE_FLAG 5
#define RELEASE 6
#define INITIALIZE 7

// stepping motor statement 
#define STOP 0
#define CLOCKWISE 1
#define ANTCLOCKWISE 2
