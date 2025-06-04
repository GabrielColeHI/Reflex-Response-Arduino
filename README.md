# Reflex-Response-Arduino

An interactive reaction game built with the Adafruit Circuit Playground Express (C++).

---

## Game Overview

The slide switch toggles between the menu and game modes:  
- 0 = Menu  
- 1 = Game

---

## Menu Mode

- Difficulty is selected by pressing:
  - Left button to decrease difficulty  
  - Right button to increase difficulty  
- Right-side LEDs (pixels 5–9) display the selected difficulty level.  
- Left-side LEDs (pixels 0–4) display your score as a progress bar representing wins out of total rounds.  
- Hold both buttons in menu to reset your score and total.

---

## Gameplay Mode

Each round begins with a countdown using the bottom 2 LEDs (red -> yellow -> green), followed by one of three random challenges:

| LED Display      | Required Input               |
|------------------|------------------------------|
| Left side blue   | Press the left button only   |
| Right side blue  | Press the right button only  |
| Full ring blue   | Press both buttons together  |

- Incorrect input or timeout results in red lights and a failure tone.  
- Correct input triggers green lights and a success tone.  
- Higher difficulty shortens the response time for each round.

---

## Inputs

- `CircuitPlayground.leftButton()` — Player input for left-side challenges  
- `CircuitPlayground.rightButton()` — Player input for right-side challenges  
- `CircuitPlayground.slideSwitch()` — Toggles between menu (0) and game (1)

---

## Outputs

- NeoPixels (RGB LEDs) — Visual feedback for countdowns, gameplay, difficulty, and score  
- Speaker (`playTone`) — Auditory feedback for a win or a loss

---

## Gameplay Summary

- The game presents one challenge per round.  
- Players must respond with the correct button(s) within the time limit.  
- The menu shows current performance and allows difficulty adjustment.  
- The game can be exited at any time by switching back to menu mode.

---

## Inputs/Outputs & Game Rules (Assignment Sheet)

### Inputs

| Sensor                     | Purpose                          | Function Used                         | Notes                           |
|----------------------------|----------------------------------|----------------------------------------|---------------------------------|
| Slide Switch               | Switch between menu and game     | `CircuitPlayground.slideSwitch()`     | 0 = menu, 1 = gameplay          |
| Left Button                | Decrease difficulty / input      | `CircuitPlayground.leftButton()`      | Debounced, used in both modes   |
| Right Button               | Increase difficulty / input      | `CircuitPlayground.rightButton()`     | Debounced, used in both modes   |

### Outputs

| Output     | Purpose                             | Function Used                         |
|------------|-------------------------------------|----------------------------------------|
| NeoPixels  | Display score, difficulty, feedback | `CircuitPlayground.setPixelColor()`    |
| Speaker    | Win/loss sound feedback             | `CircuitPlayground.playTone()`         |

### Game Logic

- Game starts when slide switch = 1  
- Countdown (red -> yellow -> green) displayed on LEDs 4–5  
- One of 3 random challenges:
  - Left, Right, or Both buttons
- Correct input = green flash + success tone  
- Incorrect input or timeout = red flash + fail tone  
- Response time = `baseDelay / difficulty`, with baseDelay = 2500ms  
- Score tracked via: `correctAttempts / totalAttempts`  
- Menu mode displays:
  - Score on left LEDs (0–4)
  - Difficulty on right LEDs (5–9)
- Holding both buttons resets score
