#include <Adafruit_CircuitPlayground.h>
int gameMode = 0;   // 0 = Main Menu, 1 = Play
int prevMode = -1;  // To detect changes
bool leftPrev = false;
bool rightPrev = false;
int totalAttempts = 0;
int correctAttempts = 0;
int difficulty = 0;


void setup() {
  CircuitPlayground.begin();  // Initialize CPX board
}

void loop() {

  gameMode = CircuitPlayground.slideSwitch() ? 1 : 0;

  if (gameMode != prevMode) {
    CircuitPlayground.clearPixels();

    prevMode = gameMode;
  }
  switch (gameMode) {
    case 0:  //Main Menu
      handleMenu();


      break;


    case 1:  //play mode
      handlePlay();
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

  // Shows correct/total as green progress bar 
  int litLEDs = 0;
  if (totalAttempts > 0) {
    float successRatio = (float)correctAttempts / totalAttempts;
    litLEDs = round(successRatio * 5.0);  // Map to 0–5 LEDs
  }
  for (int i = 0; i < litLEDs; i++) {
    CircuitPlayground.setPixelColor(i, 0, 255, 0);  // Green
  }

  // Show difficulty as blue LEDs (LEDs 5–9)
  for (int i = 0; i < difficulty; i++) {
    CircuitPlayground.setPixelColor(5 + i, 0, 0, 255);  // Blue
  }
}

void handlePlay() {
  CircuitPlayground.clearPixels();

  int baseDelay = 2500;
  int adjustedDelay = difficulty > 0 ? baseDelay / difficulty : baseDelay;

  // Countdown: bottom 2 bulbs 
  for (int i = 4; i <= 5; i++) CircuitPlayground.setPixelColor(i, 255, 0, 0);  // Red
  delay(500);
  for (int i = 4; i <= 5; i++) CircuitPlayground.setPixelColor(i, 255, 150, 0);  // Yellow
  delay(500);
  for (int i = 4; i <= 5; i++) CircuitPlayground.setPixelColor(i, 0, 255, 0);  // Green
  delay(500);
  CircuitPlayground.clearPixels();
  

delay(200);
while (CircuitPlayground.leftButton() || CircuitPlayground.rightButton()) {
  delay(10);
}

  // Random button challenge: 0 = left, 1 = right, 2 = both
  int challenge = random(0, 3);

  if (challenge == 0) {
    for (int i = 0; i <= 4; i++) CircuitPlayground.setPixelColor(i, 0, 0, 255);  // left side blue
  } else if (challenge == 1) {
    for (int i = 5; i <= 9; i++) CircuitPlayground.setPixelColor(i, 0, 0, 255);  //  right side  blue
  } else {
    for (int i = 0; i <= 9; i++) CircuitPlayground.setPixelColor(i, 0, 0, 255);  // Full ring
  }

  bool correct = false;
  bool failed = false;
  unsigned long startTime = millis();
  int timeout = adjustedDelay;



  while (!correct && !failed && millis() - startTime < timeout) {
//check if game ended
      if (!CircuitPlayground.slideSwitch()) {
    CircuitPlayground.clearPixels();
    Serial.println("Game exited early");
    return;  // Exit back to main menu
  }

    bool left = CircuitPlayground.leftButton();
    bool right = CircuitPlayground.rightButton();




  if (left != leftPrev || right != rightPrev) {
  if (left && !right) Serial.println("left");
  else if (right && !left) Serial.println("right");
  else if (left && right) Serial.println("both");
  leftPrev = left;
  rightPrev = right;
}
    // Correct input
    if (challenge == 0 && left && !right) correct = true;
    else if (challenge == 1 && right && !left) correct = true;
    else if (challenge == 2) {
      static unsigned long leftPressTime = 0;
      static unsigned long rightPressTime = 0;

      if (left) leftPressTime = millis();
      if (right) rightPressTime = millis();

      if (abs((long)leftPressTime - (long)rightPressTime) <= 150 && left && right) {
        correct = true;
      }

    }
    // Wrong input
    else if (left || right)
      failed = true;

    delay(10);
  }
totalAttempts++;

  // Feedback for input
  CircuitPlayground.clearPixels();
  if (correct) {
      correctAttempts++;

    for (int i = 0; i < 10; i++) CircuitPlayground.setPixelColor(i, 0, 255, 0);  // Green = win
    CircuitPlayground.playTone(1000, 300);

  } else {
    for (int i = 0; i < 10; i++) CircuitPlayground.setPixelColor(i, 255, 0, 0);  // Red = fail
    CircuitPlayground.playTone(200, 500);
  }
  noTone(5);
  delay(1000);

  CircuitPlayground.clearPixels();
}
