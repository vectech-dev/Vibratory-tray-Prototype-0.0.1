#define vib_in1 10
#define vib_in2 11
#define vib_en 12

#define bulk_IN1 15
#define bulk_IN2 16
#define bulk_EN 17

#define sw 14


int pwm;
int dutyVib = 60; // Percent of time the motor stays on in a single cycle.
int onTimeVib = 160;   // The amount of time the motor stays on in a single step.
int offTimeVib = 500;
// int count = 0;

bool isSystemRunning = false;
bool isVibRunning;
bool isBulkRunning;

long currentMillis;
long previousMillis;