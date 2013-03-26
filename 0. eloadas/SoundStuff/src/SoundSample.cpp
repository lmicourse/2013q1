/*
 * SoundSample.cpp
 *
 *  Created on: 2013.03.19.
 *      Author: varrocs
 */

#include <algorithm>
#include <iostream>

#include "SoundSample.h"
#include <fft/complex.h>
#include <fft/fft.h>

using namespace std;
using namespace soundstuff;

//#define TRACE

// Has to be the power of 2 because of fft
const int SoundSample::sampleLength = 1024;


SoundSample::SoundSample(int rate) : rate(rate), samples() {
	sampleFreq = rate / sampleLength;	// 48000 / 1024 = 46,875Hz. Normal The block number of 1000hz is 21, 440hz is block 9
}

void SoundSample::append(sample_t sample) {
	samples.push_back(sample);
}

bool SoundSample::findFrequency(int frequency) {
	// Transform to complex*
	vector<complex> complexVector;
	complexVector.resize(samples.size()); // To fit the result of the transformation
		transform(
				samples.begin(),
				samples.end(),
				complexVector.begin(),
				[](sample_t t){return complex(t);}
				);
	samples.clear();

	// Hack to make it a regular pointer needed by the FFT lib
	complex* temp = &complexVector[0];
	bool ok = CFFT::Forward(temp, complexVector.size());
	if (!ok) {
		throw exception();
	}

	// Find the strongest freq
	int counter = 0;
	int strongest = 0;
	double strongestValue = 0.0;
	for (auto c : complexVector) {
		if (counter == 0) {
			++counter;
			continue;	// Noise reduction
		}
		if (strongestValue < c.norm()) {
			strongestValue = c.norm();
			strongest = counter;
		}
		++counter;
	}

	int freqToFind = frequency / sampleFreq;
#ifdef TRACE
	cout << "Target postion " << freqToFind << endl;
	cout << "Strongest value: " << strongestValue << " @ " << strongest << endl;
#endif

	return strongest == freqToFind || strongest == (sampleLength - freqToFind);

	return true;
}
