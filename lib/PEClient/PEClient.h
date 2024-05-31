/*
  PEClient.h - Library for PEClient demo code.
  Created by Vux, May 22, 2024.
  Released into the public domain.
*/

#ifndef PECLIENT_H
#define PECLIENT_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <map>
#include <functional>

class PEClient
{
public:
  PEClient(const char *wifiSSID, const char *wifiPassword, const char *mqttServer, int mqttPort, const char *clientId, const char *username, const char *password);
  void begin();
  void loop();

  void sendMetric(unsigned long timestamp, const char *key, double value);

  void sendMetric(const char *key, double value);

  void sendAttribute(const char *key, double value);
  void sendAttribute(const char *key, const char *value);

  void on(const char *key, void (*callback)(String));

private:
  void initWiFi();
  void reconnect();
  static void callback(char *topic, byte *message, unsigned int length);

  const char *_ssid;
  const char *_password;
  const char *_mqttServer;
  int _mqttPort;
  const char *_clientId;
  const char *_username;
  const char *_passwordMqtt;

  WiFiClient _espClient;
  PubSubClient _client;

  String _sendMetricTopic;
  String _sendAttributeTopic;

  std::map<String, std::function<void(String)>> _callbacks;
  static PEClient *_instance;
};

#endif
