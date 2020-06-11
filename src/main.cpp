#include <Arduino.h>
#include <FastLED.h>

#include <Button.h>
#include <Animation.h>

#define MAX_MILLI_AMPERE 400
#define NUM_LEDS 50
#define DATA_PIN 6
#define INPUT_PIN 12
#define CYCLE_MS 15
#define DEBOUNCE_CYCLES 5

// LED data
CRGB pixel[NUM_LEDS];

// animation
SwooshAnimator animator(pixel, NUM_LEDS);

// button input
void onPressCallback(void) {
	animator.start();
}
Button button(DEBOUNCE_CYCLES, onPressCallback);

void setup() {

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(pixel, NUM_LEDS);
	FastLED.clear(true);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_MILLI_AMPERE);

	pinMode(INPUT_PIN, INPUT_PULLUP);
}

void loop() {
	button.apply(digitalRead(INPUT_PIN) == LOW);

	if (animator.changed()) {
		FastLED.show();
	}
	delay(CYCLE_MS);
}
