#include <unity.h>
#include <string.h>

#include "Button.h"

#define INPUT_PIN 12
#define PRESSED 1
#define RELEASED -1

uint8_t callCount = 0;
int8_t lastCall = 0;

void onPressCallback(void) {
	lastCall = PRESSED;
	callCount++;
}

void onReleaseCallback(void) {
	lastCall = RELEASED;
	callCount++;
}

void setUp(void) {
	lastCall = 0;
	callCount = 0;
}

//void tearDown(void) {}

void callbacks_can_be_null(void) {

	Button button = Button::create(INPUT_PIN, 0);
	TEST_ASSERT_EQUAL_INT8(0, callCount);

	// press
	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(0, callCount);

	// release
	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(0, callCount);

	// register and press
	button.registerOnPress(onPressCallback);
	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);

	// release
	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(1, callCount);

	// press
	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(2, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);

	// release
	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(2, callCount);

	// press
	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(3, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);

	// release
	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(3, callCount);

	// register and press
	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(4, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);

	// release
	button.registerOnRelease(onReleaseCallback);
	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(5, callCount);
	TEST_ASSERT_EQUAL_INT8(RELEASED, lastCall);
}

void reflects_input_change_once_for_zero_dropCount(void) {

	Button button = Button::create(INPUT_PIN, 0).registerOnPress(onPressCallback).registerOnRelease(onReleaseCallback);
	TEST_ASSERT_EQUAL_INT8(0, callCount);

	// press
	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);

	// release
	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(2, callCount);
	TEST_ASSERT_EQUAL_INT8(RELEASED, lastCall);

	// press
	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(3, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);

	// release
	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(4, callCount);
	TEST_ASSERT_EQUAL_INT8(RELEASED, lastCall);

	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(4, callCount);

	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(4, callCount);

	// press
	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(5, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);
}

void filters_input_flicker_for_positive_dropCount(void) {

	Button button = Button::create(INPUT_PIN, 2).registerOnPress(onPressCallback).registerOnRelease(onReleaseCallback);
	TEST_ASSERT_EQUAL_INT8(0, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(0, callCount);

	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(0, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(0, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);

	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(1, callCount);

	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(2, callCount);
	TEST_ASSERT_EQUAL_INT8(RELEASED, lastCall);
}

void reflects_input_change_once_for_positive_dropCount(void) {

	Button button = Button::create(INPUT_PIN, 3).registerOnPress(onPressCallback).registerOnRelease(onReleaseCallback);
	TEST_ASSERT_EQUAL_INT8(0, callCount);

	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(0, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(0, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(0, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);

	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(1, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);
}

void release_only_after_press(void) {

	Button button = Button::create(INPUT_PIN, 0).registerOnPress(onPressCallback).registerOnRelease(onReleaseCallback);
	TEST_ASSERT_EQUAL_INT8(0, callCount);

	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(0, callCount);

	button.apply(true);

	TEST_ASSERT_EQUAL_INT8(1, callCount);
	TEST_ASSERT_EQUAL_INT8(PRESSED, lastCall);

	button.apply(false);

	TEST_ASSERT_EQUAL_INT8(2, callCount);
	TEST_ASSERT_EQUAL_INT8(RELEASED, lastCall);
}

void returns_given_inputPin(void) {
	Button button = Button::create(INPUT_PIN, 0);

	TEST_ASSERT_EQUAL_UINT8(INPUT_PIN, button.getInputPin());
}

int main(int argc, char **argv) {

	UNITY_BEGIN();

	RUN_TEST(callbacks_can_be_null);
	RUN_TEST(reflects_input_change_once_for_zero_dropCount);
	RUN_TEST(filters_input_flicker_for_positive_dropCount);
	RUN_TEST(reflects_input_change_once_for_positive_dropCount);
	RUN_TEST(release_only_after_press);

	UNITY_END();

	return 0;
}
