#define RELAY_PIN    17 // ESP32 pin GIOP17 that connects to relay
#define MOISTURE_PIN 36 // ESP32 pin GIOP36 (ADC0) that connects to AOUT pin of moisture sensor

#define THRESHOLD 1000 // CHANGE YOUR THRESHOLD HERE

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  int value = analogRead(MOISTURE_PIN); // read the analog value from sensor

  if (value < THRESHOLD) {
    Serial.print("The soil is DRY => turn pump ON");
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    Serial.print("The soil is WET => turn pump OFF");
    digitalWrite(RELAY_PIN, LOW);
  }

  Serial.print(" (");
  Serial.print(value);
  Serial.println(")");

  delay(200);
}


