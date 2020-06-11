#ifndef LIB_BUTTON_BUTTON_H
#define LIB_BUTTON_BUTTON_H

#include <stdint.h>

class Button {

private:
	uint8_t inputCycles;
	void (*onPress)(void);
	void (*onRelease)(void);

	uint8_t discards;
	bool lastButtonPressed = false;
	bool buttonPressed = false;

public:
	Button(uint8_t inputCycles, void (*onPress)(void));
	Button(uint8_t inputCycles, void (*onPress)(void), void (*onRelease)(void));

	void apply(bool input);

};

#endif /* LIB_BUTTON_BUTTON_H */
