#include <Arduino.h>
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

int lastDebounceTime, lastReading;

void state_change()
{
  if (!flag)
  {
    Serial.println("Motor running");
    flag = true;
  }
  else
  {
    Serial.println("Motor stopped");
    Serial.print("Number of steps: ");
    Serial.println(count);
    flag = false;
    count = 0;
  }
}

void setup()
{
  // pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  pinMode(enA, OUTPUT);
  // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);


  pwm = map(dutyCycle,0,100,0,255);
  analogWrite(enA,pwm);

  Serial.begin(115200);
  lastDebounceTime = millis();
  lastReading = HIGH;
}

void loop()
{
  if (flag)
  {
    // Serial.println("Motor running?");
    analogWrite(enA,pwm);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(onTime);

    count++;
    // delay(300);
    analogWrite(enA,255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    delay(waitTime);
  }
  else
  {

    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
  }
  int btnState = digitalRead(sw);

	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastDebounceTime > 50) {
			Serial.println("Button pressed!");
      state_change();
		}

		// Remember last button press event
		lastDebounceTime = millis();
	}
  delay(10);
}