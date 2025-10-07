const int sensorPin = A0;
const int buzzerPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  int moisturePercent = map(sensorValue, 1023, 0, 0, 100);

  Serial.println(moisturePercent); // Send only % value

  if (moisturePercent < 40) {
    tone(buzzerPin, 4000, 500);
  } else {
    noTone(buzzerPin);
  }

  delay(1000); // 1 second update
}

