#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

// Додаткові бібліотеки Firebase
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Дані підключення до Wi-Fi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// Firebase API Key та URL бази даних
#define API_KEY "AIzaSyCzmBySE-PeR_PNfdSLK6S5BzQ0i8swpKE"
#define DATABASE_URL "https://lab-4-eb5a6-default-rtdb.firebaseio.com"

// Об'єкти Firebase
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase connected");
    signupOK = true;
  } else {
    Serial.printf("Firebase error: %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    
    // Емуляція температури (20 - 30 градусів)
    float temperature = 20.0 + (random(0, 1000) / 100.0);
    
    if (Firebase.RTDB.setFloat(&fbdo, "sensor/temperature", temperature)) {
      Serial.println("Temperature sent to Firebase");
      Serial.println("Temperature: " + String(temperature) + " °C");
    } else {
      Serial.println("FAILED to send temperature");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}
