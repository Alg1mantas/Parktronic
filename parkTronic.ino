const int trigPin = 9; 
const int echoPin = 10;
const int dataPin = 3;
const int latchPin = 5;
const int clockPin = 7;
const int DISTANCE_1 = 10;
const int DISTANCE_2 = 20;
const int DISTANCE_3 = 30;
const int SPEED_OF_SOUND = 0.034;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(dataPin, LOW);
  digitalWrite(latchPin, LOW);
}

void shiftRegister(int shiftPattern) {
  digitalWrite(clockPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, shiftPattern);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
}

void loop() {
  long duration, distance, shiftPattern;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * SPEED_OF_SOUND / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance > DISTANCE_3) {
    shiftPattern = 0;
  } else if (distance < DISTANCE_3) {
    shiftPattern = B00001100;
  } else if (distance < DISTANCE_2) {
    shiftPattern = B00011110;
  } else if (distance < DISTANCE_1) {
    shiftPattern = B00111111;
  }
  shiftRegister(shiftPattern);
  delay(500);
}