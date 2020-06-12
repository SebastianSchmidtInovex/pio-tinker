#include "../../lib_embedded/button/Button.h"

#include <unity.h>
#include <Arduino.h>


void reflects_input_directly_on_zero_cycleCount(void) {
	Button button(LED_BUILTIN, 0);

	digitalWrite(LED_BUILTIN, HIGH);	// pull up

	TEST_ASSERT_FALSE(button.isPressed());

	digitalWrite(LED_BUILTIN, LOW);	// button press

	TEST_ASSERT_TRUE(button.isPressed());

	digitalWrite(LED_BUILTIN, HIGH);	// pull up

	TEST_ASSERT_FALSE(button.isPressed());
}

void filters_input_flicker_for_positive_cycleCount(void) {
	Button button(LED_BUILTIN, 2);

	digitalWrite(LED_BUILTIN, HIGH);	// pull up

	TEST_ASSERT_FALSE(button.isPressed());

	digitalWrite(LED_BUILTIN, LOW);	// button press

	TEST_ASSERT_FALSE(button.isPressed());	// debounce

	TEST_ASSERT_TRUE(button.isPressed());	// accept

	digitalWrite(LED_BUILTIN, HIGH);	// pull up

	TEST_ASSERT_FALSE(button.isPressed());

	digitalWrite(LED_BUILTIN, LOW);	// button press

	TEST_ASSERT_FALSE(button.isPressed());	// debounce

	digitalWrite(LED_BUILTIN, HIGH);	// pull up

	TEST_ASSERT_FALSE(button.isPressed());	// debounce
	TEST_ASSERT_FALSE(button.isPressed());	// register release

	digitalWrite(LED_BUILTIN, LOW);	// button press

	TEST_ASSERT_FALSE(button.isPressed());	// debounce

	TEST_ASSERT_TRUE(button.isPressed());	// accept
}

void reflects_input_change_once_for_positive_cycleCount(void) {
	Button button(LED_BUILTIN, 2);

	digitalWrite(LED_BUILTIN, HIGH);	// pull up

	TEST_ASSERT_FALSE(button.isPressed());

	digitalWrite(LED_BUILTIN, LOW);	// button press

	TEST_ASSERT_FALSE(button.isPressed());	// debounce

	TEST_ASSERT_TRUE(button.isPressed());	// accept

	digitalWrite(LED_BUILTIN, HIGH);	// pull up

	TEST_ASSERT_FALSE(button.isPressed());

	digitalWrite(LED_BUILTIN, LOW);	// button press

	TEST_ASSERT_FALSE(button.isPressed());	// ignore

	TEST_ASSERT_FALSE(button.isPressed());	// ignore

	TEST_ASSERT_FALSE(button.isPressed());	// ignore

	TEST_ASSERT_FALSE(button.isPressed());	// ignore

	TEST_ASSERT_FALSE(button.isPressed());	// ignore

	TEST_ASSERT_FALSE(button.isPressed());	// ignore
}

void setup() {

	delay(2000);

	pinMode(LED_BUILTIN, OUTPUT);

	UNITY_BEGIN();
	RUN_TEST(reflects_input_directly_on_zero_cycleCount);
	RUN_TEST(filters_input_flicker_for_positive_cycleCount);
	RUN_TEST(reflects_input_change_once_for_positive_cycleCount);
	UNITY_END();
}

void loop() {

	digitalWrite(LED_BUILTIN, HIGH);
	delay(500);
	digitalWrite(LED_BUILTIN, LOW);
	delay(500);
}

