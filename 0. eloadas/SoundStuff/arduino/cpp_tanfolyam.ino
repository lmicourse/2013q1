#include <StandardCplusplus.h>
#include <string>
#include <vector>
#include <map>
#include <ctype.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////////////
// Found here: http://glade.googlecode.com/svn-history/r31/trunk/trunk/Glade/cppfix.h
///////////////////////////////////////////////////////////////////////////////////////

#ifndef cppfix
#define cppfix

/*__extension__ typedef int __guard __attribute__((mode (__DI__)));

void * operator new(size_t size);
void operator delete(void * ptr); */

/*int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {}; 
*/
/*void * operator new(size_t size)
{
  return malloc(size);
}

void operator delete(void * ptr)
{
  free(ptr);
} */

#endif 

///////////////////////////////////////////////////////////////////////////////////////
// NORMAL C++ CODE
///////////////////////////////////////////////////////////////////////////////////////


class MorseText
{
public:

    enum Signal {
        LONG,	//0, 3
        SHORT,	//1, 1
        PAUSE_SIGNAL, //2, 1
        PAUSE_LETTER, //3, 3
        PAUSE_WORD	//4, 7
    };

    static void initSignalMap();

    

    MorseText();

    /// Expects raw string
    MorseText(const std::string& rawString);

    /// Interprets high/low values
    MorseText(int signalUnitLength, const std::vector<bool>& signalVector);

    /// Returns raw string representation
    std::string toString();

    void toSignals(std::vector<Signal>& appendTo);
    void toSignals(std::vector<bool>& appendTo);

    MorseText& operator<<(const std::string& rawString);
    MorseText& operator<<(const char c);


private:
    std::string rawText;
    int signalUnitLength;	// In millisec
    static std::map<char, std::vector<Signal> > signalMap;
    void encode(char c, std::vector<Signal>& signal);

    void reduceNoise(std::vector<bool>& signal);
};



using namespace std;
// http://en.wikipedia.org/wiki/Morse_code
std::map<char, vector<MorseText::Signal> > MorseText::signalMap; /*= {
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
};*/

void MorseText::initSignalMap() {
  
//    static const Signal tomba[] = {SHORT, LONG};
//    signalMap['a']= vector<Signal>( tomba, tomba+sizeof(tomba)/sizeof(tomba[0]));
    
  //  static const Signal tombb[] = {LONG, SHORT, SHORT, SHORT};
  //  signalMap['b']= vector<Signal>( tombb, tombb+sizeof(tombb)/sizeof(tombb[0]));
  //  static const Signal tombc[] = {LONG, SHORT, LONG, SHORT};
//    signalMap['c']= vector<Signal>( tombc, tombc+sizeof(tombc)/sizeof(tombc[0]));
    static const Signal tombd[] = {LONG, LONG, SHORT};
    signalMap['d']= vector<Signal>( tombd, tombd+sizeof(tombd)/sizeof(tombd[0]));
  
    static const Signal tombe[] = {SHORT};
    signalMap['e']= vector<Signal>( tombe, tombe+sizeof(tombe)/sizeof(tombe[0]));
       
 /*   static const Signal tombf[] = {SHORT, SHORT, LONG, SHORT} ;
    signalMap['f']= vector<Signal>( tombf, tombf+sizeof(tombf)/sizeof(tombf[0]));
static const Signal tombg[] = {LONG, LONG, SHORT};
    signalMap['g']= vector<Signal>( tombg, tombg+sizeof(tombg)/sizeof(tombg[0]));
    */
static const Signal tombh[] = {SHORT, SHORT, SHORT, SHORT} ;
    signalMap['h']= vector<Signal>( tombh, tombh+sizeof(tombh)/sizeof(tombh[0]));
    /*
static const Signal tombi[] = {SHORT, SHORT};
    signalMap['i']= vector<Signal>( tombi, tombi+sizeof(tombi)/sizeof(tombi[0]));
static const Signal tombj[] = {SHORT, LONG, LONG, LONG} ;
    signalMap['j']= vector<Signal>( tombj, tombj+sizeof(tombj)/sizeof(tombj[0]));
static const Signal tombk[] = {LONG, SHORT, LONG};

    signalMap['k']= vector<Signal>( tombk, tombk+sizeof(tombk)/sizeof(tombk[0]));
    */
static const Signal tombl[] = {SHORT, LONG, SHORT, SHORT};
    signalMap['l']= vector<Signal>( tombl, tombl+sizeof(tombl)/sizeof(tombl[0]));
//static const Signal tombm[] = {LONG, LONG} ;
 //   signalMap['m']= vector<Signal>( tombm, tombm+sizeof(tombm)/sizeof(tombm[0]));
//static const Signal tombn[] = {LONG, SHORT} ;
//    signalMap['n']= vector<Signal>( tombn, tombn+sizeof(tombn)/sizeof(tombn[0]));
static const Signal tombo[] = {LONG, LONG, LONG};
    signalMap['o']= vector<Signal>( tombo, tombo+sizeof(tombo)/sizeof(tombo[0]));
/*static const Signal tombp[] = {SHORT, LONG, LONG, SHORT} ;
    signalMap['p']= vector<Signal>( tombp, tombp+sizeof(tombp)/sizeof(tombp[0]));
static const Signal tombq[] = {LONG, LONG, SHORT, LONG};
    signalMap['q']= vector<Signal>( tombq, tombq+sizeof(tombq)/sizeof(tombq[0]));
*/
static const Signal tombr[] = {SHORT, LONG, SHORT};
    signalMap['r']= vector<Signal>( tombr, tombr+sizeof(tombr)/sizeof(tombr[0]));
/*
static const Signal tombs[] = {SHORT, SHORT, SHORT} ;
    signalMap['s']= vector<Signal>( tombs, tombs+sizeof(tombs)/sizeof(tombs[0]));

static const Signal tombt[] = {LONG};
    signalMap['t']= vector<Signal>( tombt, tombt+sizeof(tombt)/sizeof(tombt[0]));

static const Signal tombu[] = {SHORT, SHORT, LONG} ;
    signalMap['u']= vector<Signal>( tombu, tombu+sizeof(tombu)/sizeof(tombu[0]));

static const Signal tombv[] = {SHORT, SHORT, SHORT, LONG};
    signalMap['v']= vector<Signal>( tombv, tombv+sizeof(tombv)/sizeof(tombv[0]));
*/
static const Signal tombw[] = {SHORT, LONG, LONG};
    signalMap['w']= vector<Signal>( tombw, tombw+sizeof(tombw)/sizeof(tombw[0]));
/*
static const Signal tombx[] = {LONG, SHORT, SHORT, LONG};
    signalMap['x']= vector<Signal>( tombx, tombx+sizeof(tombx)/sizeof(tombx[0]));

static const Signal tomby[] = {LONG, SHORT, LONG, LONG};
    signalMap['y']= vector<Signal>( tomby, tomby+sizeof(tomby)/sizeof(tomby[0]));

static const Signal tombz[] ={LONG, LONG, SHORT, SHORT};
    signalMap['z']= vector<Signal>( tombz, tombz+sizeof(tombz)/sizeof(tombz[0]));

static const Signal tomb1[] = {SHORT, LONG, LONG, LONG, LONG} ;
    signalMap['1']= vector<Signal>( tomb1, tomb1+sizeof(tomb1)/sizeof(tomb1[0]));
static const Signal tomb2[] = {SHORT, SHORT, LONG, LONG, LONG} ;
    signalMap['2']= vector<Signal>( tomb2, tomb2+sizeof(tomb2)/sizeof(tomb2[0]));
static const Signal tomb3[] = {SHORT, SHORT, SHORT, LONG, LONG} ;
    signalMap['3']= vector<Signal>( tomb3, tomb3+sizeof(tomb3)/sizeof(tomb3[0]));
static const Signal tomb4[] = {SHORT, SHORT, SHORT, SHORT, LONG} ;
    signalMap['4']= vector<Signal>( tomb4, tomb4+sizeof(tomb4)/sizeof(tomb4[0]));
static const Signal tomb5[] = {SHORT, SHORT, SHORT, SHORT, SHORT} ;
    signalMap['5']= vector<Signal>( tomb5, tomb5+sizeof(tomb5)/sizeof(tomb5[0]));
static const Signal tomb6[] = {LONG, SHORT, SHORT, SHORT, SHORT} ;
    signalMap['6']= vector<Signal>( tomb6, tomb6+sizeof(tomb6)/sizeof(tomb6[0]));
static const Signal tomb7[] = {LONG, LONG, SHORT, SHORT, SHORT} ;
    signalMap['7']= vector<Signal>( tomb7, tomb7+sizeof(tomb7)/sizeof(tomb7[0]));
static const Signal tomb8[] = {LONG, LONG, LONG, SHORT, SHORT} ;
    signalMap['8']= vector<Signal>( tomb8, tomb8+sizeof(tomb8)/sizeof(tomb8[0]));
static const Signal tomb9[] = {LONG, LONG, LONG, LONG, SHORT} ;
    signalMap['9']= vector<Signal>( tomb9, tomb9+sizeof(tomb9)/sizeof(tomb9[0]));
static const Signal tomb0[] = {LONG, LONG, LONG, LONG, LONG} ;
    signalMap['0']= vector<Signal>( tomb0, tomb0+sizeof(tomb0)/sizeof(tomb0[0]));
    */
} 

MorseText::MorseText() : rawText() {initSignalMap();}

/// Expects raw string
MorseText::MorseText(const string& rawString) : rawText(rawString) {initSignalMap();}


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

// Commented out because of auto
//MorseText::MorseText(int signalUnitLength, const std::vector<bool>& signalVector)
//	: signalUnitLength(signalUnitLength)
//	{
//
//	vector<bool> copiedVector = signalVector;
//	reduceNoise(copiedVector);
//
//	// Interpret a letter
//	vector<Signal> letter;
//	ParseState state(signalUnitLength);
//
//	for (auto s : copiedVector) {
//		bool changed  = state.feed(s);
//		if (changed) {
//			letter.push_back(state.getLastSignal());
//		}
//	}
//
//	// Find the next big pause
//	auto beginit = letter.begin();
//	auto endit = letter.begin();
//
//	while (true) {
//		while (endit != letter.end()) {
//			if (*endit == PAUSE_LETTER || (*endit == PAUSE_WORD)) {
//				++endit;
//				break;
//			}
//			++endit;
//		}
//
//		// Find match
//		auto word = vector < Signal > (beginit, endit);
//		//Clear the pauses
//		auto wordClear = vector<Signal>();
//		for (auto s : word) {
//			if (s == SHORT || s == LONG) {
//				wordClear.push_back(s);
//			}
//		}
//		/*
//		cout << "WordClear: ";
//		for (auto s : wordClear) {
//			cout << s << " ";
//		}
//		cout << endl;
//		*/
//		bool found = false;
//		for (auto l : signalMap) {
//			if (l.second == wordClear) {
//				rawText.append(1, l.first);
//				//cout << "Found: "<< l.first << endl;
//				found = true;
//				break;
//			}
//		}
//		if (found) {
//			rawText.append(1, ' ');
//		}
//
//		if (endit == letter.end() ) {
//			break; // The endless loop
//		} else {
//			beginit = endit;
//		}
//
//	}
//
//}

/// Returns raw string representation
string  MorseText::toString() {
    return rawText;
}

void MorseText::toSignals(vector<Signal>& appendTo) {
    //for (auto c : rawText) {
    //    encode(c, appendTo);
    //}
    
    for (string::iterator it = rawText.begin(); it != rawText.end(); ++it) {
      encode(*it, appendTo);
    }  
}

void MorseText::toSignals(std::vector<bool>& appendTo) {
	vector<Signal> temp;
	toSignals(temp);
       	//for (auto s : temp) {
        for (vector<Signal>::iterator it = temp.begin(); it != temp.end(); ++it) {
                const Signal& s = *it;
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
    
//    for (auto s : signalMap[c]) {
//        signal.push_back(s);
//    }
     for (vector<Signal>::iterator it = signalMap[c].begin(); it != signalMap[c].end(); ++it) {
       signal.push_back(*it);
     }
    signal.push_back(PAUSE_LETTER);
}

//void MorseText::reduceNoise(vector<bool>& signals) {
//	if (signals.size() < 3) {
//		return;
//	}
//
//	auto it = signals.begin()+2;
//	while (it != signals.end()) {
//		if (*(it - 2) == *(it)) {
//			*(it - 1) = *it;
//		}
//		it++;
//	}
//
//}

/******************************************************************************
************************* ARDUINO SPECIFIC ************************************
******************************************************************************/

const int TONE_PIN = 10;
const int TONE_DURATION = 200; //ms
const int TONE = 440; //ms

void setup() {

  MorseText t("HelloWorld");
  vector<bool> signals;
  t.toSignals(signals);
    
  
  for (vector<bool>::iterator it = signals.begin(); it != signals.end(); ++it) {
    if (*it) {
      tone(TONE_PIN, TONE);
    } else {
      noTone(TONE_PIN);
    }
    delay(TONE_DURATION);
  }
    
    noTone(TONE_PIN);
}


void loop() {
  
  
}
