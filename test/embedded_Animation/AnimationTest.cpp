#include <unity.h>
#include <FastLED.h>

#include <Animation.h>

#define NUM_LEDS 50
CRGB pixel[NUM_LEDS];

SwooshAnimator swooshAnimator(pixel, NUM_LEDS);

void test_no_change_if_not_started(void) {
	fill_solid(pixel, NUM_LEDS, CRGB::Black);
	TEST_ASSERT_EACH_EQUAL_PTR(CRGB::Black, pixel, NUM_LEDS);

	for (uint8_t i = 0; i < 10; ++i) {
		TEST_ASSERT_FALSE(swooshAnimator.changed());
		TEST_ASSERT_EACH_EQUAL_PTR(CRGB::Black, pixel, NUM_LEDS);
	}
}

void test_data_changed_if_started(void) {
	fill_solid(pixel, NUM_LEDS, CRGB::Black);
	TEST_ASSERT_EACH_EQUAL_PTR(CRGB::Black, pixel, NUM_LEDS);

	swooshAnimator.start(CRGB::Teal);
	TEST_ASSERT_TRUE(swooshAnimator.changed());
}

void setup() {

	delay(2000);

	UNITY_BEGIN();
	RUN_TEST(test_no_change_if_not_started);
	RUN_TEST(test_data_changed_if_started);
	UNITY_END();
}

void loop() {

	digitalWrite(LED_BUILTIN, HIGH);
	delay(500);
	digitalWrite(LED_BUILTIN, LOW);
	delay(500);
}

