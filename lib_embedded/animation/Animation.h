#ifndef LIB_SGS_ANIMATION_H
#define LIB_SGS_ANIMATION_H

#include <FastLED.h>

class Animator {

public:
	virtual ~Animator() {
	}
	virtual bool changed() =0;
};

class SwooshAnimator: public Animator {

private:
	CRGB *pixel;
	uint8_t numPixels;
	uint8_t horizon;

	uint8_t pos = 0;
	bool active = false;

public:
	SwooshAnimator(CRGB *pixel, uint8_t numPixels);
	void start();
	bool changed();
};

#endif /* LIB_SGS_ANIMATION_H */
