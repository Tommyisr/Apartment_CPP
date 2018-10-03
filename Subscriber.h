#ifndef MTM4_SUBSCRIBER_H
#define MTM4_SUBSCRIBER_H


#include "Client.h"

class Subscriber : public Client {
public:
    Subscriber(int priority, BrokerIfc& b, std::ostream& ss = std::cout);
    void subscribeToTopic(const Topic& topic);
    void unsubscribeToTopic(const Topic& topic);
    void unsubscribeAll();
    virtual void receiveMessage(const string message, const Topic& topic, const Client& sender);
};


#endif //MTM4_SUBSCRIBER_H
