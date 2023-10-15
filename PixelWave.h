/*
 * PixelWave.h
 *
 *  Created on: Apr 27, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_NIXIEMISC_PIXELWAVE_H_
#define LIBRARIES_NIXIEMISC_PIXELWAVE_H_

class PixelWave {
public:
	PixelWave(const int numBuckets, const int numLEDs) : levels(16) {
		init(numBuckets, numLEDs);
	}

	PixelWave(const int numBuckets, const int numLEDs, int levels) : levels(levels) {
		init(numBuckets, numLEDs);
	}

	~PixelWave() {
		for (int i=0; i<this->numBuckets; i++) {
			delete[] values[i];
		}

		delete[] values;
	}

	int getLevels() {
		return levels;
	}

	void reInit(const int numBuckets, const int numLEDs) {
		if (this->numLEDs != numLEDs || this->numBuckets != numBuckets) {
			for (int i=0; i<this->numBuckets; i++) {
				delete[] values[i];
			}

			delete[] values;

			init(numBuckets, numLEDs);
		}
	}

	void calculateValues(int pos16, int width, int bucket, byte minValue, byte maxValue) {
		int i = pos16 / levels; // convert from pos to raw pixel number
		int frac = (pos16 & (levels - 1)); // extract the 'factional' part of the position
		if (minValue != 0) {
			frac = frac * ((maxValue+1) - minValue) / (maxValue+1);
		}
		// brightness of the first pixel in the bar is 1.0 - (fractional part of position)
		// e.g., if the light bar starts drawing at pixel "57.9", then
		// pixel #57 should only be lit at 10% brightness, because only 1/10th of it
		// is "in" the light bar:
		//
		//                       57.9 . . . . . . . . . . . . . . . . . 61.9
		//                        v                                      v
		//  ---+---56----+---57----+---58----+---59----+---60----+---61----+---62---->
		//     |         |        X|XXXXXXXXX|XXXXXXXXX|XXXXXXXXX|XXXXXXXX |
		//  ---+---------+---------+---------+---------+---------+---------+--------->
		//                   10%       100%      100%      100%      90%
		//
		// the fraction we get is in 16ths and needs to be converted to 256ths,
		// so we multiply by 16.  We subtract from 255 because we want a high
		// fraction (e.g. 0.9) to turn into a low brightness (e.g. 0.1)
		frac = frac * ((maxValue + 1) / levels);

		uint8_t firstPixelValue = maxValue - frac;

		// if the bar is of integer length, the last pixel's brightness is the
		// reverse of the first pixel's; see illustration above.
		uint8_t lastPixelValue = frac + minValue;

		// For a bar of width "N", the code has to consider "N+1" pixel positions,
		// which is why the "<= width" below instead of "< width".

		for (int j = 0; j < numLEDs; j++) {
			values[bucket][j] = minValue;
		}

		uint8_t value;
		for (int n = 0; n <= width; n++) {
			if (n == 0) {
				// first pixel in the bar
				value = firstPixelValue;
			} else if (n == width) {
				// last pixel in the bar
				value = lastPixelValue;
			} else {
				// middle pixels
				value = maxValue;
			}

			values[bucket][i] = value;
			i++;
			if (i == numLEDs)
				i = 0; // wrap around
		}
	}

	void calculateValues(int pos16, int width, int bucket, byte minValue) {
		calculateValues(pos16, width, bucket, minValue, 255);
	}

	uint8_t getValue(int bucket, int index) {
		return values[bucket][index];
	}

private:
	void init(const int numBuckets, const int numLEDs) {
		this->numBuckets = numBuckets;
		this->numLEDs = numLEDs;

		values = new uint8_t*[numBuckets];
		for (int i=0; i<numBuckets; i++) {
			values[i] = new uint8_t[numLEDs];
		}

	}

	int numLEDs;
	int numBuckets;
	int levels;
	uint8_t **values;
};

#endif /* LIBRARIES_NIXIEMISC_PIXELWAVE_H_ */
