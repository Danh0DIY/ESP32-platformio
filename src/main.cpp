#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

int screenW = 160; // chiều rộng thực tế màn hình
int screenH = 80;  // chiều cao thực tế màn hình

void drawFrameTest() {
  tft.fillScreen(TFT_BLACK);

  // Vẽ viền khung
  tft.drawRect(0, 0, screenW, screenH, TFT_WHITE);

  // Vẽ đường chéo
  tft.drawLine(0, 0, screenW - 1, screenH - 1, TFT_RED);
  tft.drawLine(0, screenH - 1, screenW - 1, 0, TFT_RED);

  // Ghi chữ vị trí
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(5, 5);
  tft.printf("W:%d H:%d", screenW, screenH);
}

void setup() {
  tft.init();
  tft.setRotation(1); // xoay ngang
}

void loop() {
  for (int offsetY = 0; offsetY <= 20; offsetY += 5) {
    for (int offsetX = 0; offsetX <= 20; offsetX += 5) {
      tft.setViewport(offsetX, offsetY, screenW, screenH);
      drawFrameTest();

      delay(1000); // dừng 1 giây để quan sát
    }
  }

  // Sau khi quét xong thì giữ nguyên khung cuối
  while (1);
}