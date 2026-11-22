

// UNO R4 - Automated Gate / Smart Dustbin

#include <Servo.h>

// Pin connections
const uint8_t TRIG_PIN  = 7;
const uint8_t ECHO_PIN  = 6;
const uint8_t GREEN_PIN = 9;
const uint8_t RED_PIN   = 10;
const uint8_t SERVO_PIN = 5;

// Servo settings
Servo gateServo;

const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE = 90;

const unsigned int SERVO_STEP_DELAY = 12;

// Ultrasonic sensor settings
const unsigned long SENSOR_TIMEOUT = 30000UL;
const float CM_PER_US = 0.0343 / 2.0;
const float THRESHOLD_CM = 15.0;

// Gate status
bool gateOpen = false;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(RED_PIN, LOW);

  Serial.begin(115200);

  gateServo.attach(SERVO_PIN);

  // Start with gate closed
  gateServo.write(CLOSED_ANGLE);
  gateOpen = false;

  showGreen();

  Serial.println("Automated Gate Starting...");
}

float readDistanceCM() {

  // Send ultrasonic trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Measure echo duration
  unsigned long duration =
    pulseIn(ECHO_PIN, HIGH, SENSOR_TIMEOUT);

  // No echo received
  if (duration == 0) {
    return -1.0;
  }

  // Convert time into distance
  float distance = duration * CM_PER_US;

  return distance;
}

void showGreen() {
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
}

void showRed() {
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
}

// Move servo smoothly
void setServoAngleSmooth(int targetAngle) {

  int current = gateServo.read();

  if (current == 255) {
    gateServo.write(targetAngle);
    delay(300);
    return;
  }

  if (current < targetAngle) {

    for (int angle = current;
         angle <= targetAngle; angle++) {

      gateServo.write(angle);
      delay(SERVO_STEP_DELAY);
    }

  } else if (current > targetAngle) {

    for (int angle = current;
         angle >= targetAngle; angle--) {

      gateServo.write(angle);
      delay(SERVO_STEP_DELAY);
    }
  }

  delay(80);
}

void openGate() {

  if (!gateOpen) {

    Serial.println("Opening gate...");

    setServoAngleSmooth(OPEN_ANGLE);

    gateOpen = true;
  }
}

void closeGate() {

  if (gateOpen) {

    Serial.println("Closing gate...");

    setServoAngleSmooth(CLOSED_ANGLE);

    gateOpen = false;
  }
}

void loop() {

  float distance = readDistanceCM();

  if (distance < 0) {

    Serial.println("No echo received");

    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, LOW);

  } else {

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= THRESHOLD_CM) {

      // Object detected nearby
      showRed();
      openGate();

    } else {

      // No object nearby
      showGreen();
      closeGate();
    }
  }

  delay(120);
}
