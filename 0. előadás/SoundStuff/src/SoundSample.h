/*
 * SoundSample.h
 *
 *  Created on: 2013.03.19.
 *      Author: varrocs
 */

#ifndef SOUNDSAMPLE_H_
#define SOUNDSAMPLE_H_

#include <vector>
#include "types.h"

namespace soundstuff {

class SoundSample {
public:
	SoundSample(int rate);
	static const int sampleLength;
	void append(sample_t sample);
	bool findFrequency(int frequency);
private:
	int rate;
	double sampleFreq;
	std::vector<sample_t> samples;
};

}


#endif /* SOUNDSAMPLE_H_ */
