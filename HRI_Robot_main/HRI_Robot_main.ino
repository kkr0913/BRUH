/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Front Right Motor
const int MOTOR0PIN1 = 12;
const int MOTOR0PIN2 = 14;
const int ENABLEPIN0 = 27;

// Front Left Motor
const int MOTOR1PIN1 = 26;
const int MOTOR1PIN2 = 25;
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
const int MOTOR4PIN1 = 17;
const int MOTOR4PIN2 = 16;
const int ENABLEPIN4 = 32;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel0 = 0;
const int pwmChannel1 = 1;
const int pwmChannel2 = 2;
const int pwmChannel3 = 3;
const int pwmChannel4 = 4;
const int resolution = 8;
int dutyCycle = 200;



void stopMoving() {
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
  digitalWrite(MOTOR0PIN1, HIGH);
  digitalWrite(MOTOR0PIN2, LOW);
  digitalWrite(MOTOR1PIN1, LOW);
  digitalWrite(MOTOR1PIN2, HIGH);
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, LOW);
  digitalWrite(MOTOR3PIN1, LOW);
  digitalWrite(MOTOR3PIN2, HIGH);

  ledcWrite(pwmChannel0, dutyCycle);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
  ledcWrite(pwmChannel3, dutyCycle);
}

void moveBackward() {
  digitalWrite(MOTOR0PIN1, LOW);
  digitalWrite(MOTOR0PIN2, HIGH);
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, LOW);
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, HIGH);
  digitalWrite(MOTOR3PIN1, HIGH);
  digitalWrite(MOTOR3PIN2, LOW);

  ledcWrite(pwmChannel0, dutyCycle);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
  ledcWrite(pwmChannel3, dutyCycle);
}

void moveRight() {
  digitalWrite(MOTOR0PIN1, LOW);
  digitalWrite(MOTOR0PIN2, HIGH);
  digitalWrite(MOTOR1PIN1, LOW);
  digitalWrite(MOTOR1PIN2, HIGH);
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, LOW);
  digitalWrite(MOTOR3PIN1, HIGH);
  digitalWrite(MOTOR3PIN2, LOW);

  ledcWrite(pwmChannel0, dutyCycle);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
  ledcWrite(pwmChannel3, dutyCycle);
}

void moveLeft() {
  digitalWrite(MOTOR0PIN1, HIGH);
  digitalWrite(MOTOR0PIN2, LOW);
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, LOW);
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, HIGH);
  digitalWrite(MOTOR3PIN1, LOW);
  digitalWrite(MOTOR3PIN2, HIGH);

  ledcWrite(pwmChannel0, dutyCycle);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
  ledcWrite(pwmChannel3, dutyCycle);
}

void turnLeft() {
  digitalWrite(MOTOR0PIN1, HIGH);
  digitalWrite(MOTOR0PIN2, LOW);
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, LOW);
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, LOW);
  digitalWrite(MOTOR3PIN1, HIGH);
  digitalWrite(MOTOR3PIN2, LOW);

  ledcWrite(pwmChannel0, dutyCycle);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
  ledcWrite(pwmChannel3, dutyCycle);
}

void turnRight() {
  digitalWrite(MOTOR0PIN1, LOW);
  digitalWrite(MOTOR0PIN2, HIGH);
  digitalWrite(MOTOR1PIN1, LOW);
  digitalWrite(MOTOR1PIN2, HIGH);
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, HIGH);
  digitalWrite(MOTOR3PIN1, LOW);
  digitalWrite(MOTOR3PIN2, HIGH);

  ledcWrite(pwmChannel0, dutyCycle);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
  ledcWrite(pwmChannel3, dutyCycle);
}



void setup() {
  Serial.begin(115200);
  
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
  moveForward();
  delay(2000);
  stopMoving();
  delay(1000);
  moveBackward();
  delay(2000);
  stopMoving();
  delay(1000);
  moveRight();
  delay(2000);
  stopMoving();
  delay(1000);
  moveLeft();
  delay(2000);
  stopMoving();
  delay(1000);
  turnRight();
  delay(2000);
  stopMoving();
  delay(1000);
  turnLeft();
  delay(2000);
  stopMoving();
  delay(1000);
}
