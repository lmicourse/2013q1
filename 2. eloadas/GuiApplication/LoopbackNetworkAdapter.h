#ifndef LOOPBACKNETWORKADAPTER_H
#define LOOPBACKNETWORKADAPTER_H

#include "INetworkAdapter.h"

class LoopbackNetworkAdapter : public INetworkAdapter
{
public:
    LoopbackNetworkAdapter();

public slots:
    virtual void login(const User &user);
    virtual void logout(const User &user);
    virtual void sendMessage(const Message &message);
};

#endif // LOOPBACKNETWORKADAPTER_H
