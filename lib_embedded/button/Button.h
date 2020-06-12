#ifndef LIB_EMBEDDED_BUTTON_Button_H
#define LIB_EMBEDDED_BUTTON_Button_H

#include <stdint.h>

class Button {
private:
	uint8_t inputPin;
	uint8_t inputCycles;

	uint8_t discards;
	bool lastButtonPressed = false;
	bool buttonPressed = false;

public:
	Button(uint8_t inputPin, uint8_t inputCycles);

	bool isPressed();
};

#endif /* LIB_EMBEDDED_BUTTON_Button_H */
