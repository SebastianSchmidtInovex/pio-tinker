#include <Button.h>
#include <stddef.h>

Button::Button(uint8_t inputPin, uint8_t inputCycles) :
		inputPin(inputPin), inputCycles(inputCycles), discards(inputCycles) {
}

Button& Button::registerOnPress(void (*onPress)(void)) {
	this->onPress = onPress;
	return *this;
}
Button& Button::registerOnRelease(void (*onRelease)(void)) {
	this->onRelease = onRelease;
	return *this;
}

uint8_t Button::getInputPin() {
	return inputPin;
}

bool Button::apply(bool input) {

	if (input != lastButtonPressed) {
		discards = inputCycles;
		lastButtonPressed = input;
	}

	if (discards > 0) {
		discards--;
	}
	if (discards == 0) {
		if (input != buttonPressed) {
			buttonPressed = input;

			if (buttonPressed) {
				(*onPress)();
			} else {
				(*onRelease)();
			}
		}
	}
	return false;
}
