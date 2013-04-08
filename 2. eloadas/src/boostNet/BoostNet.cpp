
#include "BoostNet.h"

#include <boost/tokenizer.hpp>
#include <algorithm>

using namespace std;
using boost::asio::ip::tcp;

BoostNet::BoostNet(const std::string& serverIP, int serverPort)
	: callback(NULL)
	, serverIP(serverIP)
	, serverPort(serverPort)
	, io_service()
	, socket(io_service)
    , receiveThread(NULL)
    , running(false)
{
}

BoostNet::~BoostNet() {
}

void BoostNet::setCallback(NetCallback& callback) {
	this->callback = &callback;
}

void BoostNet::sendPing(int selfId, std::string selfName) {
	stringstream stream;
	stream << "PING " << selfId << " " << selfName << "\n";
	socket.send( boost::asio::buffer(stream.str()) );
}

void BoostNet::sendMessage(int selfId, std::string message) {
	stringstream stream;
	stream << "MSG " << selfId << " " << message << "\n";
	socket.send( boost::asio::buffer(stream.str()) );
}

void BoostNet::connect() {
	if (callback == NULL) {
		return;
	}

	// Connect to the server
	cout << "Connecting..." << endl;
	//TODO: Do connection

	// Start the thread
	cout << "Starting receiver thread ..." << endl;
    running = true;
	//TODO: Start receiver thread
}

void BoostNet::close() {
    running = false;
    socket.close(); // This would be much more elegant with async operation and cancel
	// TODO wait for the thread
}

void BoostNet::receiveThreadFunc() {
	cout << "boostnet receiver thread started " << endl;

	boost::asio::streambuf streambuf;
	istream stream(&streambuf);
	string message;
	// The endless loop
    while (running) {
        try {
            boost::asio::read_until(socket, streambuf, '\n');
            getline(stream, message);
            //	cout << "Received message " << message << endl;
            analyze(message);
        } catch (boost::system::system_error e) {
            cerr << "Exception while reading: " << e.what() << endl;
            sleep(5);
        }
	}
}

void BoostNet::analyze(std::string line) {

	boost::char_separator<char> separator(" ");
	boost::tokenizer< boost::char_separator<char> > tokenizer(line, separator);
	boost::tokenizer< boost::char_separator<char> >::iterator it = tokenizer.begin();

    string method = "";
    int userId;
    stringstream content;

    if (it != tokenizer.end()) {
        method = *it;
        it++;
    }

    if (method.empty()) {
        return;
    }

    if (it != tokenizer.end()) {
        userId = atoi(it->c_str());
        it++;
    }

    // Concat the rest of the message
	while (it != tokenizer.end()) {
		content << *it << " ";
		it++;
	}

    if (callback != NULL) {
		if (method == "PING") {
			callback -> onPing(userId, content.str());
		} else if (method == "MSG") {
			callback -> onMessage(userId, content.str());
		} else {
			cerr << "Unknown message method: " << method << endl;
		}
	} else {
		cerr << "Message callback is not set" << endl;
	}
}

