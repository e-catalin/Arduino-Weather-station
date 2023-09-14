#include <SoftwareSerial.h>
#include <DHT.h>

SoftwareSerial espSerial(2,3); // RX, TX
#define DHTPIN 7      // Digital pin connected to the DHT11 sensor
#define DHTTYPE DHT11     // DHT sensor type


DHT dht(DHTPIN, DHTTYPE); // DHT sensor object

int AQValue; // Air quality value from MQ135 sensor
float temperature; // Temperature value from DHT11 sensor
float humidity; // Humidity value from DHT11 sensor

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
  dht.begin();
}

void loop() {
  // Read air quality value from MQ135 sensor
  AQValue = analogRead(A0);

  // Read temperature and humidity values from DHT11 sensor
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Send sensor data to ESP8266
  espSerial.print("AQ:");
  espSerial.print(AQValue);
  espSerial.print(",Temp:");
  espSerial.print(temperature);
  espSerial.print(",Hum:");
  espSerial.println(humidity);
  //Debug values in monitor
  Serial.print("AQ:");
  Serial.print(AQValue);
  Serial.print(",Temp:");
  Serial.print(temperature);
  Serial.print(",Hum:");
  Serial.println(humidity);

  delay(3000); 
}
