

#CXX=clang++
CXX=g++
CXXFLAGS = -O3 -std=c++11
LDFLAGS=-lpthread -lboost_system -lboost_thread

OBJS=main.o Peer.o RelayServer.o
HEADERS=Callback.h Peer.h RelayServer.h

all: RelayServer

%.o: %.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

RelayServer: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) 

clean:
	rm $(OBJS) RelayServer
