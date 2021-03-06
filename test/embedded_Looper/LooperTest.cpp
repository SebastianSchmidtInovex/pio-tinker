#include <unity.h>

#include <Looper.h>

const uint16_t cycleMs = 20;

void reflects_input_directly_on_zero_cycleCount(void) {

	Looper looper(cycleMs);

	unsigned long before = millis();
	looper.initCycle();
	delay(7);
	looper.finishCycle();

	TEST_ASSERT_UINT32_WITHIN(1, cycleMs, millis() - before);

	before = millis();
	looper.initCycle();
	delay(12);
	looper.finishCycle();

	TEST_ASSERT_UINT32_WITHIN(1, cycleMs, millis() - before);

	before = millis();
	looper.initCycle();
	delay(3);
	looper.finishCycle();

	TEST_ASSERT_UINT32_WITHIN(1, cycleMs, millis() - before);

	before = millis();
	looper.initCycle();
	delay(17);
	looper.finishCycle();

	TEST_ASSERT_UINT32_WITHIN(1, cycleMs, millis() - before);

	before = millis();
	looper.initCycle();
	delay(25);
	looper.finishCycle();

	TEST_ASSERT_UINT32_WITHIN(1, 25, millis() - before);
}

void setup() {

	delay(2000);

	UNITY_BEGIN();
	RUN_TEST(reflects_input_directly_on_zero_cycleCount);
	UNITY_END();
}

void loop() {

	digitalWrite(LED_BUILTIN, HIGH);
	delay(500);
	digitalWrite(LED_BUILTIN, LOW);
	delay(500);
}

