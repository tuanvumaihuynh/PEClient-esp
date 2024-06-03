#include <Arduino.h>
#include "DHT.h"
#include "DHT_U.h"
#include "PEClient.h"
#include "esp_log.h"

#define WIFI_SSID "VanPhong2.4g"
#define WIFI_PASSWORD "Vp@1denchin"
// #define WIFI_SSID "Only one"
// #define WIFI_PASSWORD "11112002"

#define MQTT_SERVER "broker.projectenergy.cloud"
#define MQTT_PORT 1883

#define CLIENT_ID "b43009d0-f3be-4faf-81f2-7ba6b89a5a35"
#define USERNAME "yawxqwxas"
#define PASSWORD "uu21hs621h"

#define LED1_PIN 5
#define LED2_PIN 17
#define LED3_PIN 16

#define DHT_PIN 4

PEClient peClient(WIFI_SSID, WIFI_PASSWORD, MQTT_SERVER, MQTT_PORT, CLIENT_ID, USERNAME, PASSWORD);
DHT dht(DHT_PIN, DHT11);

void led1Callback(String value);
void led2Callback(String value);
void led3Callback(String value);

void setup()
{
  peClient.begin();
  peClient.on("led1", led1Callback);
  peClient.on("led2", led2Callback);
  peClient.on("led3", led3Callback);

  while (!peClient.connected())
  {
    ESP_LOGI("Main", "Waiting for MQTT connection...");
    delay(1000);
  }
  peClient.sendAttribute("led1", false);
  peClient.sendAttribute("led2", false);
  peClient.sendAttribute("led3", false);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);

  dht.begin();
}

void loop()
{
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    ESP_LOGW("Main", "Failed to read from DHT sensor!");
    return;
  }
  peClient.sendMetric("temperature", t);
  peClient.sendMetric("humidity", h);
}

bool stringToBool(const String &value)
{
  return value.equalsIgnoreCase("true") || value == "1";
}

void led1Callback(String value)
{
  digitalWrite(LED1_PIN, stringToBool(value));
}

void led2Callback(String value)
{
  digitalWrite(LED2_PIN, stringToBool(value));
}

void led3Callback(String value)
{
  digitalWrite(LED3_PIN, stringToBool(value));
}