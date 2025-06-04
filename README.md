# Reflex-Response-Arduino

An interactive reaction game built with the Adafruit Circuit Playground Express (C++).

---

## Game Overview

The slide switch toggles between the menu and gameplay modes:  
- 0 = Menu  
- 1 = Game

---

## Menu Mode

- Difficulty is selected by pressing:
  - Left button to decrease difficulty  
  - Right button to increase difficulty  
- Right-side LEDs (pixels 5–9) display the selected difficulty level.
- Left-side LEDs (pixels 0–4) display your score as a progress bar representing wins out of total rounds.
- Hold both buttons to reset your score and total.

---

## Gameplay Mode

Each round begins with a countdown using the bottom 2 LEDs (red → yellow → green), followed by one of three random challenges:

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

- NeoPixels (RGB LEDs) — Visual feedback for countdowns, challenges, difficulty, and score  
- Speaker (`playTone`) — Auditory feedback for success or failure

---

## Gameplay Summary

- The game presents one challenge per round.  
- Players must respond with the correct button(s) within the time limit.  
- The menu shows current performance and allows difficulty adjustment.  
- The game can be exited at any time by switching back to menu mode.
