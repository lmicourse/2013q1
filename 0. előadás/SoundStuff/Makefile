

BINDIR=bin
SRCDIR=src
LIBDIR=lib

CXX=g++-4.7
CXXFLAGS = -std=c++11 -O3 -I$(LIBDIR)
LDFLAGS= 

OBJS=$(SRCDIR)/morsetext.o $(SRCDIR)/SoundSample.o $(LIBDIR)/fft/fft.o $(LIBDIR)/fft/complex.o
HEADERS=morsetext.h SoundSample.h type.h $(LIBDIR)/fft/fft.h $(LIBDIR)/fft/complex.h

all: $(BINDIR)/SoundTest $(BINDIR)/SoundStuff

$(SRCDIR)/%.o: %.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) -o $@ &<

$(BINDIR)/SoundTest: $(SRCDIR)/main-1.o $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^

$(BINDIR)/SoundStuff: $(SRCDIR)/main.o $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^
	
clean:
	rm $(OBJS) $(SRCDIR)/main.o $(BINDIR)/SoundStuff $(SRCDIR)/main-1.o $(BINDIR)/SoundTest
