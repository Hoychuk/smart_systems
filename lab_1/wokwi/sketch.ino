#include <FastLED.h>

#define LED_PIN     2
#define NUM_LEDS    16
#define PIR_PIN     3
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
bool manualControl = false;
bool manualOn = false;

void setup() {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    pinMode(PIR_PIN, INPUT);
    Serial.begin(9600);
    Serial.println("Система запущена. Введіть 'on', 'off' або 'auto'.");
}

void loop() {
    int motion = digitalRead(PIR_PIN);
    
    if (!manualControl) {
        if (motion == HIGH) {
            setLights(true);
        } else {
            setLights(false);
        }
    } else {
        setLights(manualOn);
    }

    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command == "on") {
            manualControl = true;
            manualOn = true;
            Serial.println("Ручний режим: підсвічування увімкнено.");
        } else if (command == "off") {
            manualControl = true;
            manualOn = false;
            Serial.println("Ручний режим: підсвічування вимкнено.");
        } else if (command == "auto") {
            manualControl = false;
            Serial.println("Автоматичний режим відновлено.");
        }else{
          Serial.println("Не розпізнано.");
        }
    }
}

void setLights(bool state) {
    fill_solid(leds, NUM_LEDS, state ? CRGB::White : CRGB::Black);
    FastLED.show();
}
