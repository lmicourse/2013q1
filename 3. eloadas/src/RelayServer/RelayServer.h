
#ifndef RELAYSERVER_H_
#define RELAYSERVER_H_

#include <list>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Peer.h"
#include "Callback.h"

class RelayServer : public Callback {
public:
	RelayServer(int port);
	virtual ~RelayServer();

	void start();

	// From callback
	virtual void onRead(std::string line, Peer* peer);
	virtual void onError(Peer* peer);

private:

	void waitForNewConnection();
	void peerAccepted(Peer* newPeer, const boost::system::error_code& errorCode);

	int port;

    boost::mutex mtx_peerList;
	std::list<Peer*> peerList;

	boost::asio::io_service ioService;
	boost::asio::ip::tcp::acceptor* serverSocket;

};

#endif /* RELAYSERVER_H_ */
