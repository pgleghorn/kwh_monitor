#define LIGHT_SENSOR_PIN 0
int lightValue = 0;
int lightValueMin = 10000;
int lightValueMax = 0;
int lightValueAverage = 0;
int sleep = 1;
long tick = 0;

int threshold = 3;  // anything higher is considered "on"
int status = 0;

void setup() {
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void writeStatusChange(int s) {
  char msgBuffer[100];
  sprintf(msgBuffer, "tick=%ld, status=%d, light=%d, min=%d, max=%d, avg=%d", tick, s, lightValue, lightValueMin, lightValueMax, lightValueAverage);
  Serial.println(msgBuffer);
}

void loop() {
  lightValue = analogRead(LIGHT_SENSOR_PIN);

  if (lightValue > lightValueMax) lightValueMax = lightValue;
  if (lightValue < lightValueMin) lightValueMin = lightValue;
  lightValueAverage = ( lightValueMax + lightValueMin) / 2;
  if (status == 0) {
    if (lightValue > threshold) {
      tick++;
      status = 1;
      digitalWrite(LED_BUILTIN, HIGH);
      writeStatusChange(status);
    }
  } else {
    if (lightValue < threshold) {
      status = 0;
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  delay(sleep);
}
