
#include "ConsoleApplication.h"
#include <iostream>
#include <ctime>

using namespace std;


ConsoleApplication::ConsoleApplication(NetInterface& netIface, string username)
	: selfUser(0, username)
	, userList()
	, netIface(&netIface)
	, pingThread()
	, running(false)
{
    srand(time(NULL));  // Randomize
	selfUser.setId( rand() % 100000 );	// Generate random id
}

ConsoleApplication::~ConsoleApplication() {

}

void ConsoleApplication::start() {
    cout << "Starting threads" << endl;

	// TODO: Start threads
    //pingThread = ...
    //maintenanceThread = ...
	running = true;

    // Main loop
	string message;
	cout << "Type EXIT to exit" << endl;
	while (running) {
		getline(cin, message);

		if (message == "EXIT") {
			break;
		}

		netIface->sendMessage(selfUser.getId(), message);
	}

	stop();
}

// Exiting
void ConsoleApplication::stop() {
    cout << "Stopping the application" << endl;
	running = false;
    netIface->close();
	cout << "Waiting for the threads to exit" << endl;
	// TODO: Wait for threads
}

void ConsoleApplication::onMessage(int userId, string message) {
	cout << "From " << userId << ", message: "<< message << endl;
	// TODO: do name lookup
}

void ConsoleApplication::onPing(int id, string userName) {
	time_t currentTime = time(0);
	User u(id, userName);
	u.setLastPinged(currentTime);

	list<User>::iterator it = find(userList.begin(), userList.end(), u);
    if (it == userList.end()) { // Add the new user
        //	cout << "New user ping " << endl;
		userList.push_back(u);
    } else {    // Update the user
        //	cout << "Existing user ping " << id << endl;
		*it = u;
	}
	// TODO: do client reorder
}

void ConsoleApplication::pingThreadFunc() {
	cout << "Send ping thread started " << endl;
	while (running) {
		netIface -> sendPing(selfUser.getId(), selfUser.getName());
		sleep(3);	// sec
	}

	cout << "Send ping thread exit" << endl;
}

void ConsoleApplication::maintenanceFunc() {
	cout << "Maintenance thread running" << endl;
	while (running) {
        // TODO maintenance ...
		sleep(10);	// sec
	}
	cout << "Maintenance thread exit" << endl;
}
