#include <TFT_eSPI.h> // Thư viện TFT_eSPI
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

int offsetX = 0;
int offsetY = 0;

void drawFrameTest() {
  tft.fillScreen(TFT_BLACK);
  tft.drawRect(0, 0, tft.width(), tft.height(), TFT_RED);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(5, 5);
  tft.printf("OffsetX=%d OffsetY=%d", offsetX, offsetY);
}

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1); // 1 = ngang, 0 = dọc
  drawFrameTest();
}

void loop() {
  // Nhấn phím trên Serial Monitor để thử offset mới
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'w') offsetY--;
    if (c == 's') offsetY++;
    if (c == 'a') offsetX--;
    if (c == 'd') offsetX++;
    
    // Cập nhật màn hình
    tft.setViewport(offsetX, offsetY, tft.width(), tft.height());
    drawFrameTest();
  }
}