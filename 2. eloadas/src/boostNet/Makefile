

CXX=g++
CXXFLAGS = -O3 -I../../include
LDFLAGS=-lpthread -lboost_system -lboost_thread

OBJS=BoostNet.o  ConsoleApplication.o  main.o  User.o
HEADERS=BoostNet.h  ConsoleApplication.h  NetInterface.h  User.h

all: boostNetClient

%.o: %.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

boostNetClient: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) 

clean:
	rm $(OBJS) boostNetClient
