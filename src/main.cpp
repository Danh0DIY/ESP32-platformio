#include <Arduino.h>
#include <TFT_eSPI.h>

#define BTN_PIN 23

TFT_eSPI tft = TFT_eSPI();

const int SCR_W = 160;
const int SCR_H = 80;
const int GROUND_Y = 60;

const int DINO_X = 18;
const int DINO_W = 12;
const int DINO_H = 12;
float dinoY = GROUND_Y - DINO_H;
float dinoV = 0;
const float GRAVITY = 1.35f;
const float JUMP_V = -9.6f;
bool onGround = true;

int playerX = DINO_X;
float playerY = GROUND_Y - DINO_H;
int playerOldY = (int)playerY;

struct Ob {
  int x;
  int w;
  int h;
  bool active;
  int prevX;
};
const int MAX_OBS = 4;
Ob obs[MAX_OBS];
int baseSpeed = 3;
unsigned long lastSpawn = 0;
unsigned long spawnInterval = 1000;

bool gameOver = false;
unsigned long lastFrame = 0;
const unsigned long FRAME_MS = 25;
int score = 0;
int displayScore = 0;

int lastBtn = HIGH;
unsigned long lastBtnTime = 0;
const unsigned long DEBOUNCE = 40;

int rrand(int a, int b) { return a + (rand() % (b - a + 1)); }

inline void fillBGRect(int x, int y, int w, int h) {
  if (x + w < 0 || x > SCR_W || y + h < 0 || y > SCR_H) return;
  tft.fillRect(x, y, w, h, TFT_BLACK);
}

void drawPlayer(int x, int y, uint16_t color) {
  fillBGRect(playerX - 4, playerOldY - 3, DINO_W + 10, DINO_H + 8);

  tft.fillRect(x, y + 4, 9, 6, color);
  tft.fillRect(x + 7, y + 1, 4, 4, color);
  tft.fillRect(x - 2, y + 3, 2, 3, color);
  tft.fillRect(x + 1, y + 9, 3, 2, color);
  tft.fillRect(x + 5, y + 9, 3, 2, color);

  playerOldY = y;
}

void drawObstacle(const Ob &o, uint16_t color) {
  int oy = GROUND_Y - o.h;
  tft.fillRect(o.x, oy, o.w, o.h, color);
  if (o.w >= 6 && color != TFT_BLACK) {
    int sx = o.x + (o.w / 2) - 1;
    tft.fillRect(sx, oy - 2, 3, 2, color);
  }
}

void eraseObstacle(const Ob &o) {
  int oy = GROUND_Y - o.h;
  fillBGRect(o.prevX - 2, oy - 3, o.w + 6, o.h + 6);
}

void drawGround() {
  tft.drawFastHLine(0, GROUND_Y, SCR_W, TFT_WHITE);
  for (int x = 0; x < SCR_W; x += 8) {
    tft.drawPixel(x + 2, GROUND_Y + 2, TFT_WHITE);
  }
}

void drawScore() {
  int sx = SCR_W - 46;
  tft.fillRect(sx, 2, 44, 12, TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_YELLOW);
  tft.setCursor(sx + 2, 3);
  tft.print("S:");
  tft.print(displayScore);
}

void resetGame() {
  tft.fillScreen(TFT_BLACK);
  drawGround();
  dinoY = GROUND_Y - DINO_H;
  playerY = dinoY;
  playerOldY = (int)dinoY;
  dinoV = 0;
  onGround = true;
  for (int i = 0; i < MAX_OBS; i++) {
    obs[i].active = false;
    obs[i].prevX = SCR_W + 10;
  }
  lastSpawn = millis();
  spawnInterval = 1000;
  baseSpeed = 3;
  score = 0;
  displayScore = 0;
  gameOver = false;
  drawPlayer(playerX, (int)dinoY, TFT_WHITE);
  drawScore();
}

void spawnOne() {
  int idx = -1;
  for (int i = 0; i < MAX_OBS; i++) if (!obs[i].active) { idx = i; break; }
  if (idx == -1) return;
  int kind = rrand(0, 2);
  if (kind == 0) { obs[idx].w = 6 + rrand(0, 2); obs[idx].h = 12 + rrand(0, 2); }
  else if (kind == 1) { obs[idx].w = 10 + rrand(0, 4); obs[idx].h = 8 + rrand(0, 3); }
  else { obs[idx].w = 8 + rrand(0, 4); obs[idx].h = 10 + rrand(0, 4); }
  obs[idx].x = SCR_W + rrand(0, 30);
  obs[idx].active = true;
  obs[idx].prevX = obs[idx].x;
}

bool collideWith(const Ob &o) {
  int ox1 = o.x;
  int ox2 = o.x + o.w;
  int oy1 = GROUND_Y - o.h;
  int oy2 = GROUND_Y;
  int dx1 = playerX;
  int dx2 = playerX + DINO_W;
  int dy1 = (int)playerY;
  int dy2 = (int)playerY + DINO_H;
  if (dx1 < ox2 && dx2 > ox1 && dy1 < oy2 && dy2 > oy1) return true;
  return false;
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT_PULLUP);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  randomSeed(analogRead(34));
  tft.setTextSize(1);
  tft.setTextColor(TFT_YELLOW);
  tft.setCursor(10, 8);
  tft.print("GAME CUA DANH");
  tft.setCursor(10, 20);
  tft.print("---------------------");
  delay(2000);

  resetGame();
}

void loop() {
  unsigned long now = millis();
  if (now - lastFrame < FRAME_MS) return;
  lastFrame = now;

  int b = digitalRead(BTN_PIN);
  if (b != lastBtn) {
    lastBtnTime = now;
    lastBtn = b;
  }
  bool pressed = false;
  if (now - lastBtnTime > DEBOUNCE) {
    if (b == LOW) pressed = true;
  }

  if (gameOver) {
    if (pressed) {
      resetGame();
      delay(150);
    }
    return;
  }

  if (pressed && onGround) {
    dinoV = JUMP_V;
    onGround = false;
  }

  dinoV += GRAVITY;
  dinoY += dinoV;
  if (dinoY >= GROUND_Y - DINO_H) {
    dinoY = GROUND_Y - DINO_H;
    dinoV = 0;
    onGround = true;
  }
  playerY = dinoY;
  int curDinoY = (int)dinoY;

  drawPlayer(playerX, curDinoY, TFT_YELLOW);

  for (int i = 0; i < MAX_OBS; i++) {
    if (!obs[i].active) continue;
    eraseObstacle(obs[i]);
    obs[i].prevX = obs[i].x;
    obs[i].x -= baseSpeed;
    if (obs[i].x + obs[i].w < -10) {
      obs[i].active = false;
    }
  }

  if (now - lastSpawn >= spawnInterval) {
    spawnOne();
    lastSpawn = now;
    spawnInterval = 700 + rrand(0, 700);
  }

  for (int i = 0; i < MAX_OBS; i++) {
    if (obs[i].active) drawObstacle(obs[i], TFT_WHITE);
  }

  tft.drawFastHLine(0, GROUND_Y, SCR_W, TFT_WHITE);

  score++;
  if (score % 4 == 0) displayScore = score / 4;
  drawScore();

  for (int i = 0; i < MAX_OBS; i++) {
    if (obs[i].active && collideWith(obs[i])) {
      drawPlayer(playerX, curDinoY, TFT_RED);
      tft.setTextColor(TFT_WHITE);
      tft.setTextSize(1);
      tft.setCursor(42, 28);
      tft.print("GAME OVER");
      tft.setCursor(36, 40);
      tft.print("Score:");
      tft.print(displayScore);
      tft.setCursor(36, 52);
      tft.print("--NGU--");
      gameOver = true;
      return;
    }
  }

  static unsigned long lastRamp = 0;
  if (millis() - lastRamp > 6000) {
    lastRamp = millis();
    if (baseSpeed < 9) baseSpeed++;
    if (spawnInterval > 500) spawnInterval = max(500UL, spawnInterval - 60);
  }

  playerOldY = curDinoY;
}