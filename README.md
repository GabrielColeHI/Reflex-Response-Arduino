# Reflex-Response-Arduino
An interactive reaction game built with the Adafruit Circuit Playground Express(C++)
The slide switch toggles between the menu and the gameplay itself
0 = Menu
1 = Game

Menu: 
Difficulty is selected in the main menu by adjusting with the left/right buttons (LEDs show selected level).
	
The left side of the menu shows your score(which is wins/total rounds) and is mapped to the LEDs


Game:


A countdown lights up (bottom 2 LEDs), then one of 3 challenges is randomly shown:


Left side lights up blue: 	press left button


Right side lights up blue:	press right button


Full ring blue:			press both buttons at once


Press the wrong button or be too slow =  red lights + buzz.


Press the correct button(s) = green lights + victory tone.

Each round resets and gets faster with higher difficulty.


Inputs:
	Left Button(CircuitPlayground.leftButton): Player input for left side of challenge
		True when pressed

	Right Button(CircuitPlayground.rightButton): Player input for right side of challenge
		True when pressed	

	SlideSwitch(CircuitPlayground.slideSwitch): Toggles between play mode and menu
0 = Menu 1 = Play




Outputs:

NeoPixels(RGB LEDS) show a visual counter and challenge indicator for both difficulty, stats,  and the game itself

Speaker(PlayTone): Used to play a noise for either victory or for loss
