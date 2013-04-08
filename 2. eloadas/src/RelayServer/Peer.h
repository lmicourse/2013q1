/*
 * Peer.h
 *
 *  Created on: 2013.04.06.
 *      Author: varrocs
 */

#ifndef PEER_H_
#define PEER_H_

#include <boost/asio.hpp>
#include "Callback.h"


class Peer {
public:
	Peer(Callback* callback, boost::asio::ip::tcp::socket* socket);
	virtual ~Peer();

	void doRead();

	boost::asio::ip::tcp::endpoint* getEndpoint();
	boost::asio::ip::tcp::socket* getSocket();

private:

	void onRead(const boost::system::error_code& error, std::size_t length);


	Callback* callback;

	boost::asio::streambuf streamBuf;
	boost::asio::ip::tcp::socket* socket;
	boost::asio::ip::tcp::endpoint endpoint;
};

#endif /* PEER_H_ */
