#ifndef MORSETEXT_H
#define MORSETEXT_H

#include <string>
#include <vector>
#include <map>

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

    MorseText();

    /// Expects raw string
    MorseText(const std::string& rawString);

    /// Interprets high/low values
    MorseText(int signalUnitLength, const std::vector<int>& signalVector);

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

    void reduceNoise(std::vector<int>& signal);
};



#endif // MORSETEXT_H
