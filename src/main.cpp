#include <vector>

#include <State.h>
#include <Looper.h>
#include <Button.h>
#include <Animation.h>

#define MAX_MILLI_AMPERE 400
#define CYCLE_MS 15
#define DEBOUNCE_CYCLES 8
#define NUM_LEDS 50
#define NUM_BUTTONS 5

#define DATA_PIN 6
#define INPUT_PIN_0 8
#define INPUT_PIN_1 9
#define INPUT_PIN_2 10
#define INPUT_PIN_3 11
#define INPUT_PIN_4 12

// Cycle duration enforcer
Looper looper(CYCLE_MS);

// LED data
CRGB pixel[NUM_LEDS];

// animation
SwooshAnimator swooshAnimator(pixel, NUM_LEDS - 15);
StateDisplay stateDisplay(&(pixel[NUM_LEDS - 13]));
std::vector<Animator*> animators {
		&swooshAnimator,
		&stateDisplay
};

// state store
State state = State();

// button input
Button buttons[NUM_BUTTONS] = {
		Button(INPUT_PIN_0, DEBOUNCE_CYCLES),
		Button(INPUT_PIN_1, DEBOUNCE_CYCLES),
		Button(INPUT_PIN_2, DEBOUNCE_CYCLES),
		Button(INPUT_PIN_3, DEBOUNCE_CYCLES),
		Button(INPUT_PIN_4, DEBOUNCE_CYCLES)
};

// Controller
void readInput() {

	for (uint8_t index = 0; index < NUM_BUTTONS; ++index) {
		if (buttons[index].isPressed()) {
			state.switchBit(index);
		}
	}
}

void applyState() {

	if (state.changePending()) {
		stateDisplay.show(state.value());
		swooshAnimator.start(state.value());
	}
}

void render() {
	
	bool changed = false;
	for (Animator *animator : animators) {
		changed |= animator->changed();
	}
	if (changed) {
		FastLED.show();
	}
}

// Main
void setup() {

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(pixel, NUM_LEDS);
	FastLED.clear(true);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_MILLI_AMPERE);

	pinMode(INPUT_PIN_0, INPUT_PULLUP);
	pinMode(INPUT_PIN_1, INPUT_PULLUP);
	pinMode(INPUT_PIN_2, INPUT_PULLUP);
	pinMode(INPUT_PIN_3, INPUT_PULLUP);
	pinMode(INPUT_PIN_4, INPUT_PULLUP);
}

void loop() {

	looper.initCycle();

	readInput();

	applyState();

	render();

	looper.finishCycle();
}
