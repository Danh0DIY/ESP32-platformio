// ======= Loại màn hình =======
#define ST7735_DRIVER
#define ST7735_GREENTAB160x80

#define TFT_WIDTH  80
#define TFT_HEIGHT 160

// ======= Chân kết nối ESP32 =======
#define TFT_MOSI 18  // SDA
#define TFT_SCLK 5   // SCL
#define TFT_CS   22  // Chip Select
#define TFT_DC   21  // Data/Command
#define TFT_RST  19  // Reset

// Màn hình không có MISO, nên bỏ qua
// Đèn nền (BLK) nối 3V3 luôn sáng

// ======= Tùy chọn màu =======
#define TFT_RGB_ORDER TFT_BGR // ST7735S thường là BGR
#define TFT_INVERSION_ON     // Nếu màu bị đảo thì thử OFF

// ======= Font chữ =======
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

// ======= Giảm bộ đệm nếu thiếu RAM =======
// #define SPI_FREQUENCY  27000000
#define SPI_FREQUENCY  40000000