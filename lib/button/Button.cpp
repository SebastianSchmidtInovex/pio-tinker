#include <Button.h>
#include <stddef.h>

Button::Button(uint8_t inputCycles, void (*onPress)(void)) :
		inputCycles(inputCycles), onPress(onPress), onRelease(NULL), discards(inputCycles) {
}
Button::Button(uint8_t inputCycles, void (*onPress)(void), void (*onRelease)(void)) :
		inputCycles(inputCycles), onPress(onPress), onRelease(onRelease), discards(inputCycles) {
}

void Button::apply(bool input) {

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
				if (onPress != NULL) {
					(*onPress)();
				}
			} else {
				if (onRelease != NULL) {
					(*onRelease)();
				}
			}
		}
	}

}
