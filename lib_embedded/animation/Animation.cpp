#include <Animation.h>

SwooshAnimator::SwooshAnimator(CRGB *pixel, uint8_t numPixels) :
		pixel(pixel),
		numPixels(numPixels),
		horizon(2 * numPixels) {}

void SwooshAnimator::start() {
	active = true;
}

bool SwooshAnimator::changed() {
	bool changed = false;

	if (active) {
			if (pos < numPixels) {
				pixel[pos] = CRGB::Teal;
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
