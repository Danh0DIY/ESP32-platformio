#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "danh";
const char* password = "1234567899";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected");

  HTTPClient http;

  // Test gửi request lên xiaozhi.me
  http.begin("http://xiaozhi.me");  // dùng http, chưa rõ server có https không
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.printf("🌍 Server Response code: %d\n", httpCode);
    String payload = http.getString();
    Serial.println("📄 Response:");
    Serial.println(payload);
  } else {
    Serial.printf("❌ Error in request: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() {
}