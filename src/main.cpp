#include <Arduino.h>

const int dacPin = 25;  // GPIO25 = DAC1
const int sampleRate = 8000; // 8kHz sample rate

// Bảng sin 1 chu kỳ (0-255)
const uint8_t sineTable[64] = {
  128, 140, 153, 165, 177, 188, 198, 207,
  214, 220, 225, 228, 230, 231, 230, 228,
  225, 220, 214, 207, 198, 188, 177, 165,
  153, 140, 128, 115, 102,  90,  78,  67,
   57,  48,  41,  35,  30,  27,  25,  24,
   25,  27,  30,  35,  41,  48,  57,  67,
   78,  90, 102, 115
};

// Hàm phát 1 nốt
void playTone(float frequency, int duration_ms) {
  int samplesPerCycle = sampleRate / frequency;
  int tableStep = (64 * frequency) / sampleRate;

  unsigned long start = millis();
  int i = 0;

  while (millis() - start < duration_ms) {
    dacWrite(dacPin, sineTable[i % 64]);
    delayMicroseconds(1000000 / sampleRate);
    i += tableStep;
  }
}

void setup() {
  // Test vài nốt piano
  playTone(262, 400); // C4
  delay(100);
  playTone(294, 400); // D4
  delay(100);
  playTone(330, 400); // E4
  delay(100);
  playTone(349, 400); // F4
  delay(100);
  playTone(392, 600); // G4
}

void loop() {
  // im lặng
}