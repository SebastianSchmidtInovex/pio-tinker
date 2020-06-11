#ifndef LIB_BUTTON_BUTTON_H
#define LIB_BUTTON_BUTTON_H

#include <stdint.h>

class Button {

private:
	uint8_t inputPin;
	uint8_t inputCycles;

	void (*onPress)(void) = noOp;
	void (*onRelease)(void) = noOp;

	uint8_t discards;
	bool lastButtonPressed = false;
	bool buttonPressed = false;

public:
	Button(uint8_t inputPin, uint8_t inputCycles);

	Button& registerOnPress(void (*onPress)(void));
	Button& registerOnRelease(void (*onRelease)(void));

	uint8_t getInputPin();
	bool apply(bool input);

	static void noOp(void) {
	}

	static Button create(uint8_t inputPin, uint8_t inputCycles) {
		return Button(inputPin, inputCycles);
	}
};

#endif /* LIB_BUTTON_BUTTON_H */
