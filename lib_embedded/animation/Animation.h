#ifndef LIB_SGS_ANIMATION_H
#define LIB_SGS_ANIMATION_H

#include <FastLED.h>

class Animator {
protected:
	CRGB *pixel;
	uint8_t numPixels;

	bool active = false;

	Animator(CRGB *pixel, uint8_t numPixels);

public:
	virtual ~Animator() {
	}
	virtual bool changed() =0;
};

class SwooshAnimator: public Animator {

private:
	uint8_t horizon;

	uint8_t pos = 0;
	uint8_t colorIndex = 0;
	CRGB rainbow[32];

public:
	SwooshAnimator(CRGB *pixel, uint8_t numPixels);
	void start(uint8_t colorIndex);

	bool changed() override;
};

class StateDisplay: public Animator {

private:
	uint8_t state = 0;

	void setPixel(uint8_t index, bool value);

public:
	StateDisplay(CRGB *pixel);
	void show(uint8_t state);

	bool changed() override;
};

#endif /* LIB_SGS_ANIMATION_H */
