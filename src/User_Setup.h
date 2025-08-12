// User_Setup.h - cấu hình chân cho màn hình ST7735 80x160 trên ESP32

#define ST7735_DRIVER    // Màn hình ST7735

#define TFT_WIDTH  160
#define TFT_HEIGHT 80

#define TFT_MOSI 18
#define TFT_SCLK 5
#define TFT_CS   22
#define TFT_DC   21
#define TFT_RST  19  // Nếu màn hình không có chân reset, đặt -1

#define TFT_BL   33  // Nếu có chân backlight, chỉnh lại chân này hoặc comment nếu không dùng

// SPI frequency settings
#define SPI_FREQUENCY  40000000  // 40 MHz SPI speed, có thể chỉnh thấp hơn nếu lỗi

// Chọn kiểu màn hình và màu sắc, không cần thay đổi
#define TFT_RGB_ORDER TFT_RGB  // Một số màn hình dùng TFT_BGR

// Các cấu hình thêm có thể thêm ở đây nếu cần