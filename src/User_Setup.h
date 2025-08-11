#define ST7735_DRIVER
#define TFT_WIDTH  160
#define TFT_HEIGHT 80

// Chân kết nối
#define TFT_MOSI 18
#define TFT_SCLK 5
#define TFT_CS   22
#define TFT_DC   21
#define TFT_RST  19
#define TFT_BL   -1 // bỏ qua, vì đã nối thẳng 3V3

// Loại LCD
#define ST7735_GREENTAB160x80

// Tốc độ SPI
#define SPI_FREQUENCY  27000000