
#include <boost/bind.hpp>
#include "Peer.h"

using namespace std;

Peer::Peer(Callback* callback, boost::asio::ip::tcp::socket* socket)
	: callback(callback)
	, streamBuf()
	, socket(socket)
	, endpoint()
{
}

Peer::~Peer() {
}

void Peer::doRead() {
	cout << "Waiting for a line " << endl;
	boost::asio::async_read_until(
			*socket,
			streamBuf,
			'\n',
			boost::bind(&Peer::onRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
	);
}

void Peer::onRead(const boost::system::error_code& error, std::size_t length) {
	cout << "Data receieved, error " << error.value() << ", length: "<< length << endl;
	if (!error) {
		string line;
		istream stream(&streamBuf);
		getline(stream, line);
		callback -> onRead(line, this);
		doRead();
	} else {
		cout << "Error happened while reading, code: " << error.value() << endl;
		callback -> onError(this);
	}
}

boost::asio::ip::tcp::endpoint* Peer::getEndpoint() {
	return &endpoint;
}
boost::asio::ip::tcp::socket* Peer::getSocket() {
	return socket;
}

