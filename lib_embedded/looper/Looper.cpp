#include <Looper.h>

Looper::Looper(uint16_t cycleMs) :
		cycleMs(cycleMs) {
}

void Looper::initCycle() {
	cycleStart = millis();
}
void Looper::finishCycle() {
	unsigned long duration = millis() - cycleStart;
	if (cycleMs > duration) {
		delay(cycleMs - duration);
	}
}

