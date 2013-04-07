#include "LoopbackNetworkAdapter.h"

LoopbackNetworkAdapter::LoopbackNetworkAdapter()
    : INetworkAdapter()
{}

void LoopbackNetworkAdapter::login(const User &user)
{
    emit loggedIn(user);
}

void LoopbackNetworkAdapter::logout(const User &user)
{
    emit loggedOut(user);
}

void LoopbackNetworkAdapter::sendMessage(const Message &message)
{
    emit messageReceived(message);
}
