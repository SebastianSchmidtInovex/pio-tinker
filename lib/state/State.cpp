#include <State.h>

void State::switchBit(uint8_t position) {
	if (position < 8) {
		uint8_t mask = 1 << position;
		state ^= mask;	// XOR-assignment with bit mask
		dirty = true;
	}
}

bool State::changePending() {
	if (dirty) {
		dirty = false;
		return true;
	}
	return false;
}

uint8_t State::value() {
	return state;
}

