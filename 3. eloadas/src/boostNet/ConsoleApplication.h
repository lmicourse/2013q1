
#ifndef CONSOLEAPPLICATION_H_
#define CONSOLEAPPLICATION_H_

#include <list>
#include <string>
#include <boost/thread.hpp>

#include "NetInterface.h"
#include "User.h"

class ConsoleApplication : public NetCallback {
public:
	ConsoleApplication(NetInterface& netIface, std::string username);
	virtual ~ConsoleApplication();

	void start();
	void stop();

	virtual void onMessage(int userid, std::string message);
	virtual void onPing(int id, std::string userName);

private:

    void pingThreadFunc();
	void maintenanceFunc();

	User selfUser;

	std::list<User> userList;
	NetInterface* netIface;

	boost::thread* pingThread;
	boost::thread* maintenanceThread;
	bool running;
};

#endif /* CONSOLEAPPLICATION_H_ */
