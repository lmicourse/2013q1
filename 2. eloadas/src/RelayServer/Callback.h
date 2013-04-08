
#pragma once

#include <string>

class Peer;

class Callback {
public:
	virtual void onRead(std::string line, Peer* peer) = 0;
	virtual void onError(Peer* peer) = 0;
};
