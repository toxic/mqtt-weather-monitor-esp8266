#include "DHT.h"
#include "ESP8266WiFi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// WiFi access point credentials
#define WLAN_SSID     "WIFI_SID"
#define WLAN_PASS     "WIFI_PASS"

// Setup the MQTT
#define MQTT_SERVER      "MQTT_SERVER_ADDRESS"
#define MQTT_SERVERPORT  1883

int DHT_DIGITAL_PIN = D3;
int LIGHT_ANALOG_PIN = A0;
DHT dht(DHT_DIGITAL_PIN, DHT11);

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT);

// Setup MQTT publish
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, "home/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, "home/humidity");
Adafruit_MQTT_Publish light = Adafruit_MQTT_Publish(&mqtt, "home/light");

void MQTT_connect();

void setup() {

  Serial.begin(115200);

  // Init & connect to WIFI
  Serial.print("WIFI: ");

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Connected");

  // Init temperature & humidity sensor
  dht.begin();
}

void loop() {
  MQTT_connect();

  // publish values
  float temperatureValue = dht.readTemperature();
  float humidityValue = dht.readHumidity();
  int lightValue = analogRead(LIGHT_ANALOG_PIN);

  temperature.publish(temperatureValue);
  humidity.publish(humidityValue);
  light.publish((uint32_t)lightValue);

  Serial.println("Debug:");
  Serial.println(String(temperatureValue) + String("°C"));
  Serial.println(String(humidityValue) + String("%rh"));
  Serial.println(String(lightValue) + String("L"));

  delay(60000); // sleep 1 minute
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("MQTT: ");

  uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));

    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1); // die
    }
  }
  Serial.println("Connected");
}
