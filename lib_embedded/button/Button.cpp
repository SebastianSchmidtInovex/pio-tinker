#include <Arduino.h>
#include "Button.h"

Button::Button(uint8_t inputPin, uint8_t inputCycles) :
		inputPin(inputPin), inputCycles(inputCycles), discards(inputCycles) {
}

bool Button::isPressed() {

	bool input = digitalRead(inputPin) == LOW;

	if (input != lastButtonPressed) {
		discards = inputCycles;
		lastButtonPressed = input;
	}

	if (discards > 0) {
		discards--;
	}
	if (discards == 0) {
		if (input != buttonPressed) {
			return buttonPressed = input;
		}
	}
	return false;
}
