#include <vector>

#include <Looper.h>
#include <Button.h>
#include <Animation.h>

#define CYCLE_MS 15
#define DEBOUNCE_CYCLES 5
#define MAX_MILLI_AMPERE 400
#define NUM_LEDS 50

#define DATA_PIN 6
#define INPUT_PIN 12

// Cycle duration enforcer
Looper looper(CYCLE_MS);

// LED data
CRGB pixel[NUM_LEDS];

// animation
SwooshAnimator swooshAnimator(pixel, NUM_LEDS);
std::vector<Animator*> animators { &swooshAnimator };

// button input
Button button(INPUT_PIN, DEBOUNCE_CYCLES);
void readInput() {
	if (button.isPressed()) {
		swooshAnimator.start();
	}
}

void setup() {

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(pixel, NUM_LEDS);
	FastLED.clear(true);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_MILLI_AMPERE);

	pinMode(INPUT_PIN, INPUT_PULLUP);
}

void loop() {

	looper.initCycle();

	readInput();

	bool changed = false;
	for (Animator *animator : animators) {
		changed |= animator->changed();
	}
	if (changed) {
		FastLED.show();
	}

	looper.finishCycle();
}
