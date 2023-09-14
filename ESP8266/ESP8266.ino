#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "DigitalHomeEE51";
const char* password = "HUKU7BFYYL";
const char* server = "api.thingspeak.com";
const char* apiKey = "O6GVLOXO44BEOLBR";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n');
    receivedData.trim();

    if (receivedData.startsWith("AQ:")) {
      // Parse received data from Arduino Uno R3
      int indexAQ = receivedData.indexOf(":") + 1;
      int indexTemp = receivedData.indexOf("Temp:") + 5;
      int indexHum = receivedData.indexOf("Hum:") + 4;

      int AQValue = receivedData.substring(indexAQ, indexTemp - 6).toInt();
      float temperature = receivedData.substring(indexTemp, indexHum - 5).toFloat();
      float humidity = receivedData.substring(indexHum).toFloat();

      // Send data to ThingSpeak
      if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        const int httpPort = 80;
        if (client.connect(server, httpPort)) {
          String url = "/update?api_key=";
          url += apiKey;
          url += "&field1=";
          url += String(AQValue);
          url += "&field2=";
          url += String(temperature);
          url += "&field3=";
          url += String(humidity);

          client.print("GET " + url + " HTTP/1.1\r\n" +
                       "Host: " + server + "\r\n" +
                       "Connection: close\r\n\r\n");
          delay(2000); /

          Serial.println("Data sent to ThingSpeak");
        } else {
          Serial.println("Failed to connect to ThingSpeak");
        }
      }
    }
  }

  delay(1000); 
}
