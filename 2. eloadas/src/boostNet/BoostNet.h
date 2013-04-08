
#ifndef BOOSTNET_H_
#define BOOSTNET_H_


#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "NetInterface.h"

class BoostNet : public NetInterface {
public:
	BoostNet(const std::string& serverIP, int port);
	virtual ~BoostNet();

	virtual void connect();
	virtual void close();

	virtual void setCallback(NetCallback& callback);
	virtual void sendPing(int selfId, std::string selfName);
	virtual void sendMessage(int selfId, std::string message);

private:
	void receiveThreadFunc();
	void analyze(std::string line);

	NetCallback* callback;
	std::string serverIP;
	int serverPort;

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket;

	boost::thread* receiveThread;

    bool running;
};



#endif /* BOOSTNET_H_ */
