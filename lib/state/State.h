#ifndef LIB_STATE_STATE_H
#define LIB_STATE_STATE_H

#include <stdint.h>

class State {
private:
	bool dirty = false;
	uint8_t state = 0;

public:
	void switchBit(uint8_t position);
	bool changePending();
	uint8_t value();
};

#endif /* LIB_STATE_STATE_H */
