#include <stdint.h>

template<class T = void>
class ButtonHandler {
public:
	virtual ~ButtonHandler() {
	}

	virtual void onPress(T token) {
	}
	virtual void onRelease(T token) {
	}
};

// Template class declaration -------------------

template<class T = void>
class Button {

private:
	T token;
	uint8_t inputPin;
	uint8_t inputCycles;

	ButtonHandler<T> *handler;

	uint8_t discards;
	bool lastButtonPressed = false;
	bool buttonPressed = false;

public:
	Button(T token, uint8_t inputPin, uint8_t inputCycles, ButtonHandler<T> *handler);

	uint8_t getInputPin();
	void apply(bool input);
};

// Template class definition -------------------

template<class T>
Button<T>::Button(T token, uint8_t inputPin, uint8_t inputCycles, ButtonHandler<T> *handler) :
		token(token), inputPin(inputPin), inputCycles(inputCycles), handler(handler), discards(inputCycles) {
}

template<class T>
uint8_t Button<T>::getInputPin() {
	return inputPin;
}

template<class T>
void Button<T>::apply(bool input) {

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
				handler->onPress(token);
			} else {
				handler->onRelease(token);
			}
		}
	}
}
