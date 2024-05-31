#include <Arduino.h>
#include "PEClient.h"
#include "esp_log.h"

// #define WIFI_SSID "VanPhong2.4g"
// #define WIFI_PASSWORD "Vp@1denchin"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

#define MQTT_SERVER "broker.abc.cloud"
#define MQTT_PORT 1883

#define CLIENT_ID "asd-7ba6b89a5a35"
#define USERNAME "username"
#define PASSWORD "pass"

PEClient peClient(WIFI_SSID, WIFI_PASSWORD, MQTT_SERVER, MQTT_PORT, CLIENT_ID, USERNAME, PASSWORD);

void doSomething(String value);

void setup()
{
  peClient.begin();
  peClient.on("led1", doSomething);
}

void loop()
{
  double temperature = random(2000, 3000) / 100.0;
  peClient.sendMetric("temperature", temperature);
  peClient.sendAttribute("location", "HCM");
  ESP_LOGD("Main", "Temperature: %f", temperature);
  delay(1000);
}

void doSomething(String value)
{
  ESP_LOGI("Main", "led1: %s", value.c_str());
}