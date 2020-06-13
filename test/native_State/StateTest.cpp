#include <unity.h>
#include <string.h>

#include <State.h>

//void setUp(void) {}

void state_value_reflects_changed_bits(void) {

	State state = State();

	TEST_ASSERT_EQUAL_UINT8(0, state.value());

	state.switchBit(1);

	TEST_ASSERT_EQUAL_UINT8(2, state.value());

	state.switchBit(0);

	TEST_ASSERT_EQUAL_UINT8(3, state.value());

	state.switchBit(4);

	TEST_ASSERT_EQUAL_UINT8(19, state.value());

	state.switchBit(0);

	TEST_ASSERT_EQUAL_UINT8(18, state.value());

	state.switchBit(1);

	TEST_ASSERT_EQUAL_UINT8(16, state.value());
}

void state_ignores_bits_out_of_range(void) {

	State state = State();

	TEST_ASSERT_EQUAL_UINT8(0, state.value());

	state.switchBit(8);

	TEST_ASSERT_EQUAL_UINT8(0, state.value());

	state.switchBit(0);

	TEST_ASSERT_EQUAL_UINT8(1, state.value());

	state.switchBit(6);

	TEST_ASSERT_EQUAL_UINT8(65, state.value());

	state.switchBit(17);

	TEST_ASSERT_EQUAL_UINT8(65, state.value());
}

void state_processes_change_indicator(void) {

	State state = State();

	TEST_ASSERT_FALSE(state.changePending());

	state.switchBit(0);

	TEST_ASSERT_TRUE(state.changePending());
	// request settles pending change
	TEST_ASSERT_FALSE(state.changePending());
	TEST_ASSERT_FALSE(state.changePending());
	TEST_ASSERT_FALSE(state.changePending());

	state.switchBit(0);

	TEST_ASSERT_TRUE(state.changePending());
	TEST_ASSERT_FALSE(state.changePending());
}

int main(int argc, char **argv) {

	UNITY_BEGIN();

	RUN_TEST(state_value_reflects_changed_bits);
	RUN_TEST(state_ignores_bits_out_of_range);
	RUN_TEST(state_processes_change_indicator);

	UNITY_END();

	return 0;
}
