#include <DHT.h>
#include <NewPing.h>

#define DHTPIN 4        // Pin for DHT11 or DHT22 sensor
#define DHTTYPE DHT11   // Change this to DHT22 if you're using DHT22 sensor
#define TRIGGER_PIN 12  // Pin for ultrasonic sensor trigger
#define ECHO_PIN 14     // Pin for ultrasonic sensor echo
#define MAX_DISTANCE 200 // Maximum distance to measure (in centimeters)

#define RELAY_PIN 16    // Pin for the relay controlling the water pump

#define WATERING_THRESHOLD 70  // Soil moisture threshold (adjust as needed)
#define TEMP_THRESHOLD 30      // Temperature threshold (adjust as needed)
#define HUMIDITY_THRESHOLD 50  // Humidity threshold (adjust as needed)

DHT dht(DHTPIN, DHTTYPE);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Make sure the relay is initially off

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // Read temperature and humidity from DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if the readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Read distance from ultrasonic sensor (convert to cm)
  int distance = sonar.ping_cm();

  // Print sensor data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if conditions meet watering thresholds
  if (temperature > TEMP_THRESHOLD || humidity < HUMIDITY_THRESHOLD || distance < WATERING_THRESHOLD) {
    // Turn on the water pump (activate the relay)
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Watering...");

    // Add a delay for watering duration (adjust as needed)
    delay(5000);

    // Turn off the water pump (deactivate the relay)
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Watering complete.");
  }

  // Add a delay before the next sensor readings (adjust as needed)
  delay(5000);
}
