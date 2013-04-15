
#include "RelayServer.h"
#include <iostream>
#include <boost/bind.hpp>
#include <algorithm>

using boost::asio::ip::tcp;
using namespace std;

RelayServer::RelayServer(int port)
	: port(port)
    , mtx_peerList()
	, peerList()
	, ioService()
	, serverSocket(0)
{
}

RelayServer::~RelayServer() {
	for (auto peer : peerList) {
		delete peer;
	}
}

void RelayServer::waitForNewConnection() {
	cout << "Waiting for new connection " << endl;

	// Create a new peer
	tcp::socket* peerSocket = new tcp::socket(ioService);

	Peer* newPeer = new Peer((Callback*)this, peerSocket);
	// Async accept
	serverSocket->async_accept(
            *newPeer->getSocket(),      // Going to contain the socket of the peer
            *newPeer->getEndpoint(),    // Going to contain the address of the peer
             bind(&RelayServer::peerAccepted, this, newPeer, boost::asio::placeholders::error)
    );
}

void RelayServer::peerAccepted(Peer* newPeer, const  boost::system::error_code& errorCode) {
	cout << "Peer accepted from " << newPeer->getEndpoint()->address().to_string() <<
			", port: " << newPeer->getEndpoint()->port() << endl;
	// Handle the new peer
	if (! errorCode) {
        boost::lock_guard<boost::mutex> scopeLock(mtx_peerList);
		peerList.push_back(newPeer);
		newPeer->doRead();
	}

	// Start a new waiting
	waitForNewConnection();
}


void RelayServer::start() {
	cout << "Bindind to port " << port << endl;
    // asio::ip::address address =  asio::ip::address::from_string("127.0.0.1");
//	tcp::endpoint socketAddress(address, port);
	tcp::endpoint socketAddress(tcp::v4(), port);
	serverSocket = new tcp::acceptor(ioService, socketAddress);

	waitForNewConnection();
	cout << "Staring io service" << endl;
	ioService.run();
}

void RelayServer::onRead(string line, Peer* sender) {
	cout << "Read line: " << line << endl;
    list<Peer*> errorPeers;
    boost::lock_guard<boost::mutex> scopeLock(mtx_peerList);
    for (list<Peer*>::iterator it = peerList.begin(); it != peerList.end(); ++it) {
        Peer* peer = *it;
        if (peer == sender) {	// Do not send back to the sender
            continue;
        }
        line.append("\n");
        //cout << " Sending to peer: " << peer->getEndpoint()->address().to_string() << ":" << peer->getEndpoint()->port(); << endl;
        try {
            peer->getSocket()->send(  boost::asio::buffer(line) );
        } catch ( boost::system::system_error& e) {
            cout << " Exception while sending to peer: " << peer->getEndpoint()->address().to_string();
            errorPeers.push_back(peer);
        }
    }

    // Removing bad peers
    for (list<Peer*>::iterator it = errorPeers.begin(); it != errorPeers.end(); ++it) {
        peerList.remove(*it);
        onError(*it);
    }
}

void RelayServer::onError(Peer* peer) {
	cout << "Removing peer " << peer->getEndpoint()->address().to_string()
		 << ":"              << peer->getEndpoint()->port()
		 << endl;
    boost::lock_guard<boost::mutex> scopeLock(mtx_peerList);
    peerList.remove(peer);
}


