#include <Wire.h>
#include <BH1750.h>

const int dusk = 50;

// pins
const uint8_t btnPin = 2;
const uint8_t sensorPin = 5;
const uint8_t led1 = 7;
const uint8_t led2 = 8;

BH1750 lightMeter;

// separate interrupt flags
volatile bool motionRequest = false;
volatile bool switchRequest = false;

bool state = false;
bool dark = false;

// timer variables
unsigned long lastMotionTime = 0;
const unsigned long timeout = 60000; // one minute timer for lights

void setup() {
  Serial.begin(9600);
  Wire.begin();

  lightMeter.begin();

  pinMode(switchPin, INPUT_PULLUP);
  pinMode(sensorPin, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  //interrupts
  attachInterrupt(digitalPinToInterrupt(switchPin), switchISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensorPin), motionISR, RISING);

  Serial.println("System is turned on.");
}

// motion interrupt
void motionISR() {
  motionRequest = true;
}

// switch interrupt
void switchISR() {
  switchRequest = true;
}

void loop() {

  // read light level
  float lux = lightMeter.readLightLevel();

  // check if dark
  if (lux < dusk) {
    dark = true;
  } else {
    dark = false;
  }

  // handle motion (auto ON if dark, reset timer)
  if (motionRequest) {
    motionRequest = false;

    if (dark) {
      state = true;

      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);

      lastMotionTime = millis(); // start/reset timer

      Serial.println("Motion detected: Lights ON");
    }
  }

  // manual switch for when sensor doesn't work (or to turn off lights)
  if (switchRequest) {
    switchRequest = false;

    state = !state;

    digitalWrite(led1, state);
    digitalWrite(led2, state);

    if (state == HIGH) {
      Serial.println("Switch pressed: Lights ON");
    } else {
      Serial.println("Switch pressed: Lights OFF");
    }
  }

  // handle timeout (only if lights are ON)
  if (state == true) {
    if (millis() - lastMotionTime >= timeout) {
      state = false;

      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);

      Serial.println("Timeout: Lights OFF");
    }
  }
}