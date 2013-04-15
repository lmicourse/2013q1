

#include "BoostNet.h"
#include "ConsoleApplication.h"

using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char** argv) {
	// Constructors & bindings
	BoostNet net("127.0.0.1", 50002);

	string username;
	if (argc > 1) {
		username = argv[1];
	} else {
		username = "anonymous";
	}

	ConsoleApplication app(net, username);

	// Bindings
	net.setCallback(app);

	// Initializers
	net.connect();
	app.start();


}


