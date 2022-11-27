/* 
 *  Fall 2022
 *  ME-134 Robotics
 *  HRI Robot project by Kyu Rae Kim, Travis Clauson, and Kwangmin Kim
 *  4-wheel robot controlled by hand gestures
 *  Target goal:  Move forward/backward and stop the motor using hand gestures
 *  Stretch goal: Implement mecanum wheels to move freely in any directions
 *                and Raspberry Pi to be completely independent from external sources
*/

#include <JY901.h>
#include "Adafruit_VL53L0X.h"

// Front Right Motor
const int MOTOR0PIN1 = 14;
const int MOTOR0PIN2 = 12;
const int ENABLEPIN0 = 27;

// Front Left Motor
const int MOTOR1PIN1 = 25;
const int MOTOR1PIN2 = 26;
const int ENABLEPIN1 = 33;

// Rear Right Motor
const int MOTOR2PIN1 = 15;
const int MOTOR2PIN2 = 4;
const int ENABLEPIN2 = 5;

// Rear Left Motor
const int MOTOR3PIN1 = 18;
const int MOTOR3PIN2 = 19;
const int ENABLEPIN3 = 23;

// Camera Motor
const int MOTOR4PIN1 = 13;
const int MOTOR4PIN2 = 32;
const int ENABLEPIN4 = 0;

// Internal LED Pin
const int LEDPIN = 2;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel0 = 0;
const int pwmChannel1 = 1;
const int pwmChannel2 = 2;
const int pwmChannel3 = 3;
const int pwmChannel4 = 4;
const int resolution = 8;
int dutyCycle = 150;
int dutyCycle_cam = 75;

int rxdata = 0;
int cam_dir = 0;
int gesture = 0;
int cam_angle;
int distance;
const int min_distance = 30;
Adafruit_VL53L0X lidar = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;


void stopMoving() {
  dutyCycle = 0;
  digitalWrite(MOTOR0PIN1, LOW);
  digitalWrite(MOTOR0PIN2, LOW);
  digitalWrite(MOTOR1PIN1, LOW);
  digitalWrite(MOTOR1PIN2, LOW);
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, LOW);
  digitalWrite(MOTOR3PIN1, LOW);
  digitalWrite(MOTOR3PIN2, LOW);
}

void moveForward() {
  dutyCycle = 150;
  digitalWrite(MOTOR0PIN1, HIGH);
  digitalWrite(MOTOR0PIN2, LOW);
  digitalWrite(MOTOR1PIN1, LOW);
  digitalWrite(MOTOR1PIN2, HIGH);
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, LOW);
  digitalWrite(MOTOR3PIN1, LOW);
  digitalWrite(MOTOR3PIN2, HIGH);
}

void moveBackward() {
  dutyCycle = 150;
  digitalWrite(MOTOR0PIN1, LOW);
  digitalWrite(MOTOR0PIN2, HIGH);
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, LOW);
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, HIGH);
  digitalWrite(MOTOR3PIN1, HIGH);
  digitalWrite(MOTOR3PIN2, LOW);
}

void moveLeft() {
  dutyCycle = 180;
  digitalWrite(MOTOR0PIN1, LOW);
  digitalWrite(MOTOR0PIN2, HIGH);
  digitalWrite(MOTOR1PIN1, LOW);
  digitalWrite(MOTOR1PIN2, HIGH);
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, HIGH);
  digitalWrite(MOTOR3PIN1, LOW);
  digitalWrite(MOTOR3PIN2, HIGH);
}

void moveRight() {
  dutyCycle = 180;
  digitalWrite(MOTOR0PIN1, HIGH);
  digitalWrite(MOTOR0PIN2, LOW);
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, LOW);
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, LOW);
  digitalWrite(MOTOR3PIN1, HIGH);
  digitalWrite(MOTOR3PIN2, LOW);
}

void turnLeft() {
  dutyCycle = 150;
  digitalWrite(MOTOR0PIN1, LOW);
  digitalWrite(MOTOR0PIN2, HIGH);
  digitalWrite(MOTOR1PIN1, LOW);
  digitalWrite(MOTOR1PIN2, HIGH);
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, LOW);
  digitalWrite(MOTOR3PIN1, HIGH);
  digitalWrite(MOTOR3PIN2, LOW);
}

void turnRight() {
  dutyCycle = 150;
  digitalWrite(MOTOR0PIN1, HIGH);
  digitalWrite(MOTOR0PIN2, LOW);
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, LOW);
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, HIGH);
  digitalWrite(MOTOR3PIN1, LOW);
  digitalWrite(MOTOR3PIN2, HIGH);
}

void motorControl(int gestures) {
  if (gestures == 1) moveForward();
  else if (gestures == 2) moveBackward();
  else if (gestures == 3) moveRight();
  else if (gestures == 4) moveLeft();
  else if (gestures == 5) turnRight();
  else if (gestures == 6) turnLeft();
  else stopMoving();
}

void camControl(int LR) {
  if (LR == 0) {
    digitalWrite(MOTOR4PIN1, LOW);
    digitalWrite(MOTOR4PIN2, LOW);
    return;
  }
  else if (LR == 1) {
    digitalWrite(MOTOR4PIN1, HIGH);
    digitalWrite(MOTOR4PIN2, LOW);
  }
  else if (LR == 2) {
    digitalWrite(MOTOR4PIN1, LOW);
    digitalWrite(MOTOR4PIN2, HIGH);
  }
}

void lidarControl() {
  lidar.rangingTest(&measure, false);
  distance = measure.RangeMilliMeter;
  if (distance <= min_distance) stopMoving();
}

void getCamAngle() {
  JY901.receiveSerialData();
  cam_angle = JY901.getRoll();
  
  if (cam_angle > 30 || cam_angle < -30) {
    digitalWrite(LEDPIN, HIGH);
    stopMoving();
  }
  else {
    digitalWrite(LEDPIN, LOW);
  }
}


void setup() {
  Serial.begin(115200);   // Rasberry Pi
  Serial2.begin(9600);    // IMU
  JY901.attach(Serial2);  // IMU
  lidar.begin();          // Lidar
  
  pinMode(MOTOR0PIN1, OUTPUT);
  pinMode(MOTOR0PIN2, OUTPUT);
  pinMode(ENABLEPIN0, OUTPUT);
  pinMode(MOTOR1PIN1, OUTPUT);
  pinMode(MOTOR1PIN2, OUTPUT);
  pinMode(ENABLEPIN1, OUTPUT);
  pinMode(MOTOR2PIN1, OUTPUT);
  pinMode(MOTOR2PIN2, OUTPUT);
  pinMode(ENABLEPIN2, OUTPUT);
  pinMode(MOTOR3PIN1, OUTPUT);
  pinMode(MOTOR3PIN2, OUTPUT);
  pinMode(ENABLEPIN3, OUTPUT);
  pinMode(MOTOR4PIN1, OUTPUT);
  pinMode(MOTOR4PIN2, OUTPUT);
  pinMode(ENABLEPIN4, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  
  ledcSetup(pwmChannel0, freq, resolution);
  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);
  ledcSetup(pwmChannel3, freq, resolution);
  ledcSetup(pwmChannel4, freq, resolution);

  ledcAttachPin(ENABLEPIN0, pwmChannel0);
  ledcAttachPin(ENABLEPIN1, pwmChannel1);
  ledcAttachPin(ENABLEPIN2, pwmChannel2);
  ledcAttachPin(ENABLEPIN3, pwmChannel3);
  ledcAttachPin(ENABLEPIN4, pwmChannel4);
}

void loop() {
  if (Serial.available()) rxdata = Serial.read();
  cam_dir = rxdata / 10;
  gesture = rxdata % 10;

  ledcWrite(pwmChannel0, dutyCycle);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
  ledcWrite(pwmChannel3, dutyCycle);
  ledcWrite(pwmChannel4, dutyCycle_cam);

  motorControl(gesture);
  camControl(cam_dir);
  lidarControl();
  getCamAngle();

  delay(30);
}
