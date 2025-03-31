#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>
#include <ArduinoJson.h>

// Налаштування для Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Налаштування для Telegram
#define BOT_TOKEN "7862997095:AAE3SzQnzZGbYCRBlC36VtqbeBpa7ohNMks"
#define CHAT_ID "1435707878"

// Налаштування датчика DHT
#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Налаштування пінів для вентиляції
#define FAN_PIN 12

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

float targetTemperature = 35.0;  // Початкове значення цільової температури

void setup() {
  Serial.begin(115200);
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);  // Вентилятор вимкнений спочатку

  // Підключення до Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setInsecure();
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Автоматичне керування вентилятором
  if (temperature >= targetTemperature) {
    digitalWrite(FAN_PIN, HIGH);
  } else {
    digitalWrite(FAN_PIN, LOW);
  }
  
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  for (int i = 0; i < numNewMessages; i++) {
    String text = bot.messages[i].text;
    Serial.println(text);
    
    /*if (text == "/fan_on") {
      digitalWrite(FAN_PIN, HIGH);
      bot.sendMessage(CHAT_ID, "Fan turned ON", "");
    } else if (text == "/fan_off") {
      digitalWrite(FAN_PIN, LOW);
      bot.sendMessage(CHAT_ID, "Fan turned OFF", "");
    } else */
    if (text.startsWith("/set_temp")) {
      String tempStr = text.substring(10);
      float newTemp = tempStr.toFloat();
      if (newTemp >= 10.0 && newTemp <= 40.0) {
        targetTemperature = newTemp;
        bot.sendMessage(CHAT_ID, "Target temperature set to " + String(targetTemperature) + " °C", "");
      } else {
        bot.sendMessage(CHAT_ID, "Invalid temperature! Please enter a value between 10 and 40.", "");
      }
    } else if (text == "/temperature") {
      bot.sendMessage(CHAT_ID, "Temperature: " + String(temperature) + " °C\nHumidity: " + String(humidity) + " %", "");
    } else {
      bot.sendMessage(CHAT_ID, "Unknown command", "");
    }
  }
}
