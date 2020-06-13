#include <Animation.h>

Animator::Animator(CRGB *pixel, uint8_t numPixels) :
		pixel(pixel),
				numPixels(numPixels) {
}

SwooshAnimator::SwooshAnimator(CRGB *pixel, uint8_t numPixels) :
		Animator(pixel, numPixels),
				horizon(2 * numPixels) {
	fill_rainbow(rainbow, 32, 0);
}

void SwooshAnimator::start(uint8_t colorIndex) {
	active = true;
	this->colorIndex = colorIndex;
}

bool SwooshAnimator::changed() {
	bool changed = false;

	if (active) {
			if (pos < numPixels) {
			pixel[pos] = rainbow[colorIndex];
				changed = true;
			} else if (pos < horizon) {
				pixel[horizon - 1 - pos] = CRGB::Black;
				changed = true;
			}

			if (pos == horizon - 1) {
				pos = 0;
				active = false;
			} else {
				++pos;
			}
		}

	return changed;
}

StateDisplay::StateDisplay(CRGB *pixel) :
		Animator(pixel, 13) {
}

void StateDisplay::show(uint8_t state) {
	active = true;
	this->state = state;
}

void StateDisplay::setPixel(uint8_t index, bool value) {

	pixel[index] = value ? CRGB::Turquoise : CRGB::Black;
}

bool StateDisplay::changed() {

	if (active) {
		for (uint8_t index = 0; index < 5; ++index) {
			uint8_t mask = 1 << index;
			setPixel(index * 3, (state & mask) != 0);
		}

		return true;
	}

	return false;
}
