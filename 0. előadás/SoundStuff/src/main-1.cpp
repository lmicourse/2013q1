
#include <iostream>
#include "types.h"
#include "SoundSample.h"
#include "morsetext.h"
using namespace std;
using namespace soundstuff;

const int DEFAULT_SAMPLE_RATE = 48000;
const int DEFAULT_TARGET_FREQ = 440;
const int DEFAULT_SIGNAL_UNIT_LENGTH = 200;

struct Config {
	int sampeRate = DEFAULT_SAMPLE_RATE;
	int targetFreq = DEFAULT_TARGET_FREQ;
	int signalUnitLength = DEFAULT_SIGNAL_UNIT_LENGTH ;
};

Config parseConfig(int argc, char** argv);

int main(int argc, char**argv) {
	Config config = parseConfig(argc, argv);
	cout << "SR: "<<config.sampeRate << ", TF: "<<config.targetFreq << ", SUL: " << config.signalUnitLength<< endl;

	sample_t sample;
	SoundSample samples(config.sampeRate);

	vector<int> signals; // Used as bool

	while (!cin.eof()) {
		for (int i = 0; i < SoundSample::sampleLength; ++i) {
			cin >> sample;
			samples.append(sample);
		}
		try {
			bool isSignal = samples.findFrequency(config.targetFreq);
			if (isSignal) {
				cout << "Signal" << endl;
			}
			/*
			signals.push_back(isSignal);
			double signalUnitLength = config.sampeRate / SoundSample::sampleLength * ((double) (config.signalUnitLength) / 1000.0);
			MorseText morse(signalUnitLength, signals);
			//cout << morse.toString() << endl << string(40, '-') << endl;
			cout << "\r" << morse.toString();
			*/

		} catch (exception& e) {
			cerr << "Problem with " << e.what() << endl;
			exit(1);
		}
	}

	return 0;
}

Config parseConfig(int argc, char** argv) {

	Config result;
	if (argc > 1) {
		result.sampeRate = atoi(argv[1]);
	}
	if (argc > 2) {
		result.targetFreq = atoi(argv[2]);
	}
	if (argc > 3) {
		result.signalUnitLength = atoi(argv[3]);
	}

	return result;
}

