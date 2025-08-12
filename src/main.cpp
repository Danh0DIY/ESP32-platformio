#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI(); 

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(0); // Đổi từ 0-3 để test xoay
  tft.fillScreen(TFT_BLACK);

  // Lấy kích thước
  int w = tft.width();
  int h = tft.height();

  // Vẽ khung viền
  tft.drawRect(0, 0, w, h, TFT_WHITE);

  // Vẽ các đường chéo để nhìn rõ góc
  tft.drawLine(0, 0, w-1, h-1, TFT_RED);
  tft.drawLine(w-1, 0, 0, h-1, TFT_RED);

  // Ghi chữ ở các mép
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("TOP", w/2 - 15, 2, 2);
  tft.drawString("BOTTOM", w/2 - 30, h - 16, 2);
  tft.drawString("LEFT", 2, h/2 - 8, 2);
  tft.drawString("RIGHT", w - 35, h/2 - 8, 2);

  // Ghi thông tin kích thước
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  String info = "W=" + String(w) + " H=" + String(h);
  tft.drawString(info, w/2 - 30, h/2 - 8, 2);

  Serial.println(info);
}

void loop() {
}