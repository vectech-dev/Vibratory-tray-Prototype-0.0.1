#include <Arduino.h>
<<<<<<< Updated upstream
// #define enA 8
#define in1 10
#define in2 11
#define sw 14
#define enA 12

int pwm;
int dutyCycle = 41;
int onTime = 190;
int waitTime = 500;
int count =0;

bool flag = false;
=======
#include "main.h"
// #define vib_en 8
>>>>>>> Stashed changes

int lastDebounceTime, lastReading;

void state_change()
{
  if (!isSystemRunning)
  {
    Serial.println("Motor running");
    isSystemRunning = true;
  }
  else
  {
    Serial.println("Motor stopped");
    // Serial.print("Number of steps: ");
    // Serial.println(count);
    // count = 0;

    isSystemRunning = false;
  }
}

void setup()
{
  // pinMode(vib_en, OUTPUT);
  pinMode(vib_in1, OUTPUT);
  pinMode(vib_in2, OUTPUT);
  pinMode(vib_en, OUTPUT);

<<<<<<< Updated upstream

  pwm = map(dutyCycle,0,100,0,255);
  analogWrite(enA,pwm);
=======
  pinMode(sw, INPUT_PULLUP);

  // Set initial rotation direction
  digitalWrite(vib_in1, LOW);
  digitalWrite(vib_in2, HIGH);

  pwm = map(dutyVib, 0, 100, 0, 255);
  analogWrite(vib_en, pwm);
>>>>>>> Stashed changes

  Serial.begin(115200);
  lastDebounceTime = millis();
  lastReading = HIGH;
}

void loop()
{
  if (isSystemRunning)
  {
<<<<<<< Updated upstream
    // Serial.println("Motor running?");
    analogWrite(enA,pwm);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(onTime);
=======
>>>>>>> Stashed changes

    currentMillis = millis();
    // Serial.println("Motor running?");
    if (!isVibRunning && currentMillis - previousMillis >= offTimeVib)
    {
      analogWrite(vib_en, pwm);
      digitalWrite(vib_in1, LOW);
      digitalWrite(vib_in2, HIGH);
      isVibRunning = true;
      previousMillis = currentMillis;
    }
    delay(onTimeVib);

    // count++;
    // delay(300);
<<<<<<< Updated upstream
    analogWrite(enA,255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    delay(waitTime);
=======
    // Serial.print("jump=");
    // Serial.println(count);

    analogWrite(vib_en, 255);
    digitalWrite(vib_in1, HIGH);
    digitalWrite(vib_in2, HIGH);
    delay(offTimeVib);
>>>>>>> Stashed changes
  }
  else
  {

    digitalWrite(vib_in1, HIGH);
    digitalWrite(vib_in2, HIGH);
  }
  int btnState = digitalRead(sw);

<<<<<<< Updated upstream
	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastDebounceTime > 50) {
			Serial.println("Button pressed!");
=======
  // If we detect LOW signal, button is pressed
  if (btnState == LOW)
  {
    // if 50ms have passed since last LOW pulse, it means that the
    // button has been pressed, released and pressed again

    if (millis() - lastDebounceTime > 500)
    {
      Serial.println("Button pressed!");
>>>>>>> Stashed changes
      state_change();
		}

		// Remember last button press event
		lastDebounceTime = millis();
	}
  delay(10);
}