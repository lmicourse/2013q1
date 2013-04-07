
#ifndef NETINTERFACE_H_
#define NETINTERFACE_H_


class NetCallback {
public:
	virtual void onMessage(int id, std::string message) = 0;
	virtual void onPing(int id, std::string userName) = 0;
};

class NetInterface {
public:

	virtual void connect() = 0;
	virtual void close() = 0;

	virtual void setCallback(NetCallback& callback) = 0;
	virtual void sendPing(int selfId, std::string selfName) = 0;
	virtual void sendMessage(int selfId, std::string message) = 0;
};

#endif /* NETINTERFACE_H_ */
