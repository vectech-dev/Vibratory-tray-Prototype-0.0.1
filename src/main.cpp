#include <Arduino.h>
#include "main.h"
// #define vib_en 8

int lastDebounceTime, lastReading;

void state_change()
{
  if (!isSystemRunning)
  {
    Serial.println("Motor running");
    isSystemRunning = true;
    isVibRunning = true;
    isBulkRunning = true;
  }
  else
  {
    Serial.println("Motor stopped");
    // Serial.print("Number of steps: ");
    // Serial.println(count);
    // count = 0;

    isSystemRunning = false;
    isVibRunning = false;
    isBulkRunning = false;
  }
}

void setup()
{
  // pinMode(vib_en, OUTPUT);
  pinMode(vib_in1, OUTPUT);
  pinMode(vib_in2, OUTPUT);
  pinMode(vib_en, OUTPUT);

  pinMode(sw, INPUT_PULLUP);

  // Set initial rotation direction
  digitalWrite(vib_in1, LOW);
  digitalWrite(vib_in2, HIGH);

  pwm = map(dutyVib, 0, 100, 0, 255);
  analogWrite(vib_en, pwm);

  Serial.begin(115200);
  lastDebounceTime = millis();
  lastReading = HIGH;
}

void loop()
{
  if (isSystemRunning)
  {

    currentMillis = millis();
    // Serial.println("Motor running?");
    if (!isVibRunning && currentMillis - previousMillisVib >= offTimeVib)
    {
      // Serial.println("reaching");
      analogWrite(vib_en, pwm);
      digitalWrite(vib_in1, LOW);
      digitalWrite(vib_in2, HIGH);
      isVibRunning = true;
      previousMillisVib = currentMillis;
    }
    else if (isVibRunning && currentMillis - previousMillisVib >= onTimeVib)
    {
      analogWrite(vib_en, 255);
      digitalWrite(vib_in1, HIGH);
      digitalWrite(vib_in2, HIGH);
      isVibRunning = false;
      previousMillisVib = currentMillis;
    }
  }
  // delay(onTimeVib);

  // count++;
  // delay(300);
  // Serial.print("jump=");
  // Serial.println(count);

  else
  {
    analogWrite(vib_en, 255);
    digitalWrite(vib_in1, HIGH);
    digitalWrite(vib_in2, HIGH);
  }
  int btnState = digitalRead(sw);

  // If we detect LOW signal, button is pressed
  if (btnState == LOW)
  {
    // if 50ms have passed since last LOW pulse, it means that the
    // button has been pressed, released and pressed again

    if (millis() - lastDebounceTime > 500)
    {
      Serial.println("Button pressed!");
      state_change();
    }

    // Remember last button press event
    lastDebounceTime = millis();
  }
  delay(10);
}