
// Code cơ bản nháy LED trên ESP32

#define LED_PIN 2  // Chân GPIO có LED tích hợp

void setup() {
  pinMode(LED_PIN, OUTPUT); // Cấu hình chân LED là OUTPUT
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // Bật LED
  delay(500);                  // Chờ 500ms
  digitalWrite(LED_PIN, LOW);  // Tắt LED
  delay(500);                  // Chờ 500ms
}