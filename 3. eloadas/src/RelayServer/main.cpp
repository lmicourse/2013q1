
#include <iostream>
#include "RelayServer.h"

using namespace std;


int main() {
	cout << "Starting relay server" << endl;
	RelayServer server(50002);
	server.start();
	cout << "Relay server ended" << endl;
}


