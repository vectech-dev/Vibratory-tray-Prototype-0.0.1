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

  pinMode(bulk_EN, OUTPUT);
  pinMode(bulk_IN1, OUTPUT);
  pinMode(bulk_IN2, OUTPUT);

  pinMode(sw, INPUT_PULLUP);

  // Set initial rotation direction
  Serial.begin(115200);
  lastDebounceTime = millis();
  lastReading = HIGH;

  pwmVib = map(dutyVib, 0, 100, 0, 255);
  pwmBulk = map(dutyBulk, 0, 100, 0, 255);
}

void startVibMotor()
{
  analogWrite(vib_en, pwmVib);
  digitalWrite(vib_in1, LOW);
  digitalWrite(vib_in2, HIGH);
}

void stopVibMotor()
{
  analogWrite(vib_en, 255);
  digitalWrite(vib_in1, HIGH);
  digitalWrite(vib_in2, HIGH);
}

void startBulkMotor()
{
  analogWrite(bulk_EN, pwmBulk);
  digitalWrite(bulk_IN1, LOW);
  digitalWrite(bulk_IN2, HIGH);
}

void stopBulkMotor()
{
  analogWrite(bulk_EN, 255);
  digitalWrite(bulk_IN1, HIGH);
  digitalWrite(bulk_IN2, HIGH);
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
      startVibMotor();
      isVibRunning = true;
      previousMillisVib = currentMillis;
    }
    else if (isVibRunning && currentMillis - previousMillisVib >= onTimeVib)
    {
      stopVibMotor();
      isVibRunning = false;
      previousMillisVib = currentMillis;
    }

    if (!isBulkRunning && currentMillis - previousMillisBulk >= offTimeBulk)
    {
      startBulkMotor();
      isBulkRunning = true;
      previousMillisBulk = currentMillis;
    }
    else if (isBulkRunning && currentMillis - previousMillisBulk >= onTimeBulk)
    {
      stopBulkMotor();
      isBulkRunning = false;
      previousMillisBulk = currentMillis;
    }
  }

  else
  {
    stopVibMotor();
    stopBulkMotor();
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