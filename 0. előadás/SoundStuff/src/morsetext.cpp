#include "morsetext.h"

// For character check
#include <ctype.h>
#include <math.h>

// For debugging
#include <iostream>

using namespace std;
// http://en.wikipedia.org/wiki/Morse_code
map<char, vector<MorseText::Signal> > MorseText::signalMap = {
    {'a', {SHORT, LONG} },
    {'b', {LONG, SHORT, SHORT, SHORT} },
    {'c', {LONG, SHORT, LONG, SHORT} },
    {'d', {LONG, LONG, SHORT} },
    {'e', {SHORT} },
    {'f', {SHORT, SHORT, LONG, SHORT} },
    {'g', {LONG, LONG, SHORT} },
    {'h', {SHORT, SHORT, SHORT, SHORT} },
    {'i', {SHORT, SHORT} },
    {'j', {SHORT, LONG, LONG, LONG} },
    {'k', {LONG, SHORT, LONG} },
    {'l', {SHORT, LONG, SHORT, SHORT} },
    {'m', {LONG, LONG} },
    {'n', {LONG, SHORT} },
    {'o', {LONG, LONG, LONG} },
    {'p', {SHORT, LONG, LONG, SHORT} },
    {'q', {LONG, LONG, SHORT, LONG} },
    {'r', {SHORT, LONG, SHORT} },
    {'s', {SHORT, SHORT, SHORT} },
    {'t', {LONG} },
    {'u', {SHORT, SHORT, LONG} },
    {'v', {SHORT, SHORT, SHORT, LONG} },
    {'w', {SHORT, LONG, LONG} },
    {'x', {LONG, SHORT, SHORT, LONG} },
    {'y', {LONG, SHORT, LONG, LONG} },
    {'z', {LONG, LONG, SHORT, SHORT} },

    {'1', {SHORT, LONG, LONG, LONG, LONG} },
    {'2', {SHORT, SHORT, LONG, LONG, LONG} },
    {'3', {SHORT, SHORT, SHORT, LONG, SHORT} },
    {'4', {SHORT, SHORT, SHORT, SHORT, LONG} },
    {'5', {SHORT, SHORT, SHORT, SHORT, SHORT} },
    {'6', {LONG, SHORT, SHORT, SHORT, SHORT} },
    {'7', {LONG, LONG, SHORT, SHORT, SHORT} },
    {'8', {LONG, LONG, LONG, SHORT, SHORT} },
    {'9', {LONG, LONG, LONG, LONG, SHORT} },
    {'0', {LONG, LONG, LONG, LONG, LONG} }
};

MorseText::MorseText() : rawText() {}

/// Expects raw string
MorseText::MorseText(const string& rawString) : rawText(rawString) {}


class ParseState {
	int signalUnitLength;
	bool prevState;
	int count;

	MorseText::Signal lastSignal;

public:

	MorseText::Signal getLastSignal() {return lastSignal;}

	ParseState(int signalUnitLength)
		: signalUnitLength(signalUnitLength)
		, prevState(false)
		, count(0)
		, lastSignal(MorseText::PAUSE_WORD) {}

	bool feed(bool signal) {
		if (signal xor prevState) { // The signal has changed
			count = round((double)count/(double)signalUnitLength);
		//	cout << "Signal changed to "<< signal << ", count: " << count << endl;
			if (prevState) {
				if (count == 1 || count == 2) {
					lastSignal = MorseText::SHORT;
				} else {
					lastSignal = MorseText::LONG;
				}
			} else {
				if (count == 1) {
					lastSignal = MorseText::PAUSE_SIGNAL;
				} else if ( count < 4){
					lastSignal = MorseText::PAUSE_LETTER;
				} else {
					lastSignal = MorseText::PAUSE_WORD;
				}
			}
			count = 1;
			prevState = signal;
			return true;
		} else {
			count++;
			return false;
		}
	}
};

MorseText::MorseText(int signalUnitLength, const std::vector<int>& signalVector)
	: signalUnitLength(signalUnitLength)
	{

	vector<int> copiedVector = signalVector;
	reduceNoise(copiedVector);

	// Interpret a letter
	vector<Signal> letter;
	ParseState state(signalUnitLength);

	for (auto s : copiedVector) {
		//cout << (s ? "+" : "-");
		bool changed  = state.feed(s);
		if (changed) {
			letter.push_back(state.getLastSignal());
			//cout << "last signal: " << state.getLastSignal() << endl;
		}
	}
	//cout << endl;

	// Find the next big pause
	auto beginit = letter.begin();
	auto endit = letter.begin();

	while (true) {
		while (endit != letter.end()) {
			if (*endit == PAUSE_LETTER || (*endit == PAUSE_WORD)) {
				++endit;
				break;
			}
			++endit;
		}

		// Find match
		auto word = vector < Signal > (beginit, endit);
		//Clear the pauses
		auto wordClear = vector<Signal>();
		for (auto s : word) {
			if (s == SHORT || s == LONG) {
				wordClear.push_back(s);
			}
		}

		bool found = false;
		for (auto l : signalMap) {
			if (l.second == wordClear) {
				rawText.append(1, l.first);
				found = true;
				break;
			}
		}
		if (found) {
			rawText.append(1, ' ');
		}

		if (endit == letter.end() ) {
			break; // The endless loop
		} else {
			beginit = endit;
		}

	}

}

/// Returns raw string representation
string  MorseText::toString() {
    return rawText;
}

void MorseText::toSignals(vector<Signal>& appendTo) {
    for (auto c : rawText) {
        encode(c, appendTo);
    }
}

void MorseText::toSignals(std::vector<bool>& appendTo) {
	vector<Signal> temp;
	toSignals(temp);
	for (auto s : temp) {
		switch (s) {
		case PAUSE_SIGNAL:
			appendTo.push_back(false);
			break;
		case PAUSE_LETTER:
			appendTo.push_back(false);
			appendTo.push_back(false);
			appendTo.push_back(false);
			break;
		case PAUSE_WORD:
			appendTo.push_back(false);
			appendTo.push_back(false);
			appendTo.push_back(false);
			appendTo.push_back(false);
			appendTo.push_back(false);
			appendTo.push_back(false);
			break;

		case SHORT:
			appendTo.push_back(true);
			appendTo.push_back(false);
			break;
		case LONG:
			appendTo.push_back(true);
			appendTo.push_back(true);
			appendTo.push_back(true);
			appendTo.push_back(false);
			break;
		}
	}
}

void MorseText::encode(char c, vector<Signal>& signal) {
    // Precheck
    if (isspace(c)) {
        signal.push_back(PAUSE_WORD);
        return;
    }

    if (!isalnum(c)) {
        return;
    }

    c = tolower(c);

    // Get from the map
    for (auto s : signalMap[c]) {
        signal.push_back(s);
    }
    signal.push_back(PAUSE_LETTER);
}

void MorseText::reduceNoise(vector<int>& signals) {
	if (signals.size() < 3) {
		return;
	}

	/*auto it = signals.begin()+2;
	while (it != signals.end()) {
		if (*(it - 2) == *(it)) {
			*(it - 1) = *it;
		}
		it++;
	}*/

	int signalsSize = signals.size();
	int b0;
	int b1 = signals[0];
	int b2 = signals[1];

	for (int i = 2; i < signalsSize; ++i) {
		b0=b1;
		b1=b2;
		b2=signals[i];
		if (b0 == b2) {
			signals[i-1] = b1 = b0;
		}
	}

}

