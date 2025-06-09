#include <Adafruit_CircuitPlayground.h>

int gameMode = 0;   // 0 = Main Menu, 1 = Play
int prevMode = -1;

volatile bool leftPressed = false;
volatile bool rightPressed = false;

int totalAttempts = 0;
int correctAttempts = 0;
int difficulty = 1;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(4), onLeftPress, FALLING);
  attachInterrupt(digitalPinToInterrupt(5), onRightPress, FALLING);
}

void loop() {
  gameMode = CircuitPlayground.slideSwitch() ? 1 : 0;

  if (gameMode != prevMode) {
    CircuitPlayground.clearPixels();
    prevMode = gameMode;
  }

  switch (gameMode) {
    case 0: handleMenu(); break;
    case 1: handlePlay(); break;
  }
}

void handleMenu() {
  // Adjust difficulty with buttons
  if (CircuitPlayground.leftButton() && !CircuitPlayground.rightButton()) {
    difficulty--;
    delay(200);
  }
  if (CircuitPlayground.rightButton() && !CircuitPlayground.leftButton()) {
    difficulty++;
    delay(200);
  }

  // Reset stats if both buttons held
  if (CircuitPlayground.leftButton() && CircuitPlayground.rightButton()) {
    correctAttempts = 0;
    totalAttempts = 0;
    delay(500); // debounce 
  }

  difficulty = constrain(difficulty, 1, 4);

  CircuitPlayground.clearPixels();

  // Show average (green) on LEDs 0–4, right-to-left
  int litLEDs = 0;
  if (totalAttempts > 0) {
    float successRatio = (float)correctAttempts / totalAttempts;
    litLEDs = round(successRatio * 5.0);
  }
  for (int i = 0; i < litLEDs; i++) {
    CircuitPlayground.setPixelColor(4 - i, 0, 255, 0);  // Green, right-to-left
  }

  // Show difficulty (blue) on LEDs 5–9, left-to-right
  for (int i = 0; i < difficulty; i++) {
    CircuitPlayground.setPixelColor(5 + i, 0, 0, 255);  // Blue
  }
}


void handlePlay() {
  CircuitPlayground.clearPixels();
  int delayTime = 2500 / difficulty;

  // Countdown
  for (int i = 4; i <= 5; i++) CircuitPlayground.setPixelColor(i, 255, 0, 0);
  delay(500);
  for (int i = 4; i <= 5; i++) CircuitPlayground.setPixelColor(i, 255, 150, 0);
  delay(500);
  for (int i = 4; i <= 5; i++) CircuitPlayground.setPixelColor(i, 0, 255, 0);
  delay(500);
  CircuitPlayground.clearPixels();

  delay(200);
  leftPressed = false;
  rightPressed = false;

  int challenge = random(0, 3);
  if (challenge == 0) {
    for (int i = 0; i <= 4; i++) CircuitPlayground.setPixelColor(i, 0, 0, 255);
  } else if (challenge == 1) {
    for (int i = 5; i <= 9; i++) CircuitPlayground.setPixelColor(i, 0, 0, 255);
  } else {
    for (int i = 0; i <= 9; i++) CircuitPlayground.setPixelColor(i, 0, 0, 255);
  }

  bool correct = false;
  bool failed = false;
  unsigned long startTime = millis();
  const unsigned long graceWindow = 200;

  while (millis() - startTime < delayTime && !correct && !failed) {
    if (!CircuitPlayground.slideSwitch()) {
      CircuitPlayground.clearPixels();
      return;
    }

    // Both challenge with grace window
    if (challenge == 2) {
      if (leftPressed && !rightPressed) {
        unsigned long firstPress = millis();
        while (millis() - firstPress < graceWindow) {
          if (rightPressed) {
            correct = true;
            break;
          }
          delay(5);
        }
        if (!correct) failed = true;
      } else if (rightPressed && !leftPressed) {
        unsigned long firstPress = millis();
        while (millis() - firstPress < graceWindow) {
          if (leftPressed) {
            correct = true;
            break;
          }
          delay(5);
        }
        if (!correct) failed = true;
      } else if (leftPressed && rightPressed) {
        correct = true;
      }
    }

    // Regular left or right challenges
    else {
      if (challenge == 0 && leftPressed && !rightPressed) correct = true;
      else if (challenge == 1 && rightPressed && !leftPressed) correct = true;
      else if (leftPressed || rightPressed) failed = true;
    }

    delay(10);
  }

  leftPressed = false;
  rightPressed = false;
  totalAttempts++;

  CircuitPlayground.clearPixels();
  if (correct) {
    correctAttempts++;
    for (int i = 0; i < 10; i++) CircuitPlayground.setPixelColor(i, 0, 255, 0);
    CircuitPlayground.playTone(1000, 300);
  } else {
    for (int i = 0; i < 10; i++) CircuitPlayground.setPixelColor(i, 255, 0, 0);
    CircuitPlayground.playTone(200, 500);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
}


void onLeftPress() {
  leftPressed = true;
}

void onRightPress() {
  rightPressed = true;
}
