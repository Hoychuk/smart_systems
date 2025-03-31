#define LDR_PIN 34 
#define LED_PIN 5  

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);  
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (ldrValue < 2000) { 
    digitalWrite(LED_PIN, HIGH);  
  } else {
    digitalWrite(LED_PIN, LOW);  
  }

  delay(500);
}
