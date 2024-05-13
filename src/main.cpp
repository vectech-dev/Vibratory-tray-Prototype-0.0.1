#include <Arduino.h>
// #define enA 8
#define in1 10
#define in2 11
#define sw 4
#define enA 12

int pwm;

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
    flag = false;
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


  pwm = map(70,0,100,0,255);
  analogWrite(enA,pwm);

  Serial.begin(115200);
  lastDebounceTime = millis();
  lastReading = HIGH;
}

void loop()
{
  if (flag)
  {
    analogWrite(enA,255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(50);
    analogWrite(enA,pwm);
    
    delay(300);

    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
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