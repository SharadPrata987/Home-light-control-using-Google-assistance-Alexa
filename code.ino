#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

#define WIFI_SSID "Sam"
#define WIFI_PASS "11223344"

#define APP_KEY "9baf0fa1-8da0-446b-9490-fccb4af80633"
#define APP_SECRET "a720f4f2-d4cd-4139-aff7-47442e2d1a00-bda8e45a-7d61-4966-a2c8-83e011e36be5"

// Add 2 device IDs
#define DEVICE_ID_1 "69e50c0ac1c259380d9b2282"
#define DEVICE_ID_2 "69e50c2f52800e7ce36b343e"

#define LED1 D1  // GPIO5
#define LED2 D2  // GPIO4

// Callback for LED1
bool onPowerState1(const String &deviceId, bool &state) {
  digitalWrite(LED1, state ? HIGH : LOW);
  Serial.println(state ? "LED1 ON" : "LED1 OFF");
  return true;
}

// Callback for LED2
bool onPowerState2(const String &deviceId, bool &state) {
  digitalWrite(LED2, state ? HIGH : LOW);
  Serial.println(state ? "LED2 ON" : "LED2 OFF");
  return true;
}

void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  setupWiFi();

  // Assign devices
  SinricProSwitch &switch1 = SinricPro[DEVICE_ID_1];
  SinricProSwitch &switch2 = SinricPro[DEVICE_ID_2];

  switch1.onPowerState(onPowerState1);
  switch2.onPowerState(onPowerState2);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  SinricPro.handle();
}