#include <unity.h>
#include <string.h>

#include <Button.hpp>

#define INPUT_PIN 12
#define PRESSED 1
#define RELEASED -1
#define TOKEN 42

class TestButtonHandler: public ButtonHandler<uint8_t> {
public:
uint8_t callCount = 0;
uint8_t lastToken = 0;
int8_t lastCall = 0;

	void reset(void) {
		lastCall = 0;
		lastToken = 0;
		callCount = 0;
	}

	void assertCallback(uint8_t expectedCount) {
		TEST_ASSERT_EQUAL_UINT8(expectedCount, callCount);
	}

	void assertCallback(uint8_t expectedCount, int8_t expectedSignal) {
		TEST_ASSERT_EQUAL_UINT8(expectedCount, callCount);
		TEST_ASSERT_EQUAL_UINT8(TOKEN, lastToken);
		TEST_ASSERT_EQUAL_INT8(expectedSignal, lastCall);
	}

	void onPress(uint8_t token) override {
		lastCall = PRESSED;
		lastToken = token;
		callCount++;
	}
	void onRelease(uint8_t token) override {
		lastCall = RELEASED;
		lastToken = token;
		callCount++;
	}
};
TestButtonHandler testHandler = TestButtonHandler();

void setUp(void) {
	testHandler.reset();
}

void reflects_input_change_once_for_zero_dropCount(void) {

	Button<uint8_t> button = Button<uint8_t>(TOKEN, INPUT_PIN, 0, &testHandler);
	testHandler.assertCallback(0);

	// press
	button.apply(true);

	testHandler.assertCallback(1, PRESSED);

	button.apply(true);

	testHandler.assertCallback(1);

	// release
	button.apply(false);

	testHandler.assertCallback(2, RELEASED);

	// press
	button.apply(true);

	testHandler.assertCallback(3, PRESSED);

	// release
	button.apply(false);

	testHandler.assertCallback(4, RELEASED);

	button.apply(false);

	testHandler.assertCallback(4);

	button.apply(false);

	testHandler.assertCallback(4);

	// press
	button.apply(true);

	testHandler.assertCallback(5, PRESSED);
}

void filters_input_flicker_for_positive_dropCount(void) {

	Button<uint8_t> button = Button<uint8_t>(TOKEN, INPUT_PIN, 2, &testHandler);
	testHandler.assertCallback(0);

	button.apply(true);

	testHandler.assertCallback(0);

	button.apply(false);

	testHandler.assertCallback(0);

	button.apply(true);

	testHandler.assertCallback(0);

	button.apply(true);

	testHandler.assertCallback(1, PRESSED);

	button.apply(false);

	testHandler.assertCallback(1);

	button.apply(false);

	testHandler.assertCallback(2, RELEASED);
}

void reflects_input_change_once_for_positive_dropCount(void) {

	Button<uint8_t> button = Button<uint8_t>(TOKEN, INPUT_PIN, 3, &testHandler);
	testHandler.assertCallback(0);

	button.apply(false);

	testHandler.assertCallback(0);

	button.apply(true);

	testHandler.assertCallback(0);

	button.apply(true);

	testHandler.assertCallback(0);

	button.apply(true);

	testHandler.assertCallback(1, PRESSED);

	button.apply(true);

	testHandler.assertCallback(1);

	button.apply(false);

	testHandler.assertCallback(1);

	button.apply(true);

	testHandler.assertCallback(1);

	button.apply(true);

	testHandler.assertCallback(1);

	button.apply(true);

	testHandler.assertCallback(1);

	button.apply(true);

	testHandler.assertCallback(1);

	button.apply(true);

	testHandler.assertCallback(1);

	button.apply(true);

	testHandler.assertCallback(1);

	button.apply(true);

	testHandler.assertCallback(1);
}

void release_only_after_press(void) {

	Button<uint8_t> button = Button<uint8_t>(TOKEN, INPUT_PIN, 0, &testHandler);
	testHandler.assertCallback(0);

	button.apply(false);

	testHandler.assertCallback(0);

	button.apply(true);

	testHandler.assertCallback(1, PRESSED);

	button.apply(false);

	testHandler.assertCallback(2, RELEASED);
}

void returns_given_inputPin(void) {
	Button<uint8_t> button = Button<uint8_t>(TOKEN, INPUT_PIN, 0, &testHandler);

	TEST_ASSERT_EQUAL_UINT8(INPUT_PIN, button.getInputPin());
}

int main(int argc, char **argv) {

	UNITY_BEGIN();

	RUN_TEST(reflects_input_change_once_for_zero_dropCount);
	RUN_TEST(filters_input_flicker_for_positive_dropCount);
	RUN_TEST(reflects_input_change_once_for_positive_dropCount);
	RUN_TEST(release_only_after_press);

	UNITY_END();

	return 0;
}
