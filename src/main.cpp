#include <TFT_eSPI.h> // Thư viện TFT_eSPI
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

int x; // Tọa độ X của chữ
String text = "Hello from ESP32!"; // Nội dung chữ
int textWidth;

void setup() {
  tft.init();
  tft.setRotation(1); // Ngang
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  // Tính độ rộng chữ
  textWidth = tft.textWidth(text);
  x = tft.width(); // Bắt đầu từ ngoài màn hình bên phải
}

void loop() {
  tft.fillScreen(TFT_BLACK); // Xóa màn hình
  tft.setCursor(x, (tft.height() - 16) / 2); // Căn giữa theo chiều cao
  tft.print(text);

  x--; // Di chuyển sang trái

  // Nếu chữ đã chạy hết ra ngoài trái màn hình
  if (x < -textWidth) {
    x = tft.width(); // Reset lại bên phải
  }

  delay(20); // Điều chỉnh tốc độ chạy
}