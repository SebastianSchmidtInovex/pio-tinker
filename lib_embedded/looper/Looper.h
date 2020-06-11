#ifndef LIB_SGS_LOOPER_H
#define LIB_SGS_LOOPER_H

#include <Arduino.h>

class Looper {

private:
	uint16_t cycleMs;

	unsigned long cycleStart = 0;

public:
	Looper(uint16_t cycleMs);

	void initCycle(void);
	void finishCycle(void);

};

#endif /* LIB_SGS_LOOPER_H */
