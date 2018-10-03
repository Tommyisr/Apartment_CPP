#ifndef MTM4_BROKER_H
#define MTM4_BROKER_H

#include <map>
#include <list>
#include "SortedSet.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "BrokerIfc.h"
#include <iostream>
#include <sstream>
using namespace std;

class Broker : public BrokerIfc {
private:
    friend class Subscriber;
    friend class Publisher;
    friend class EncryptionSubscriber;
    class CompareClients {
    public:
        bool operator()(const Client& c1, const Client& c2) const;
    };
    class CompareClientsPtr {
    public:
    	bool operator() (const Client* const c1, const Client* const c2) const;
    };

    std::map<Topic, SortedSet<Client* const,CompareClientsPtr>> map;

    virtual void subscribeToTopic(const Subscriber& sub, const Topic& t) ;

    virtual void unsubscribeToTopic(const Subscriber& sub, const Topic& t) ;

    virtual void publishTopic(const Publisher& pub, const Topic& t) ;

    virtual void unpublishTopic(const Publisher& pub, const Topic& t) ;

    virtual void publishMessage(const Topic& t, const std::string& message, const Client& sender) const ;

    void sendMaintenanceMessage(std::string message, SortedSet<Client* const, Broker::CompareClientsPtr> set);
public:
    Broker();
    ~Broker()=default;
    void sendMaintenanceMessageAny(std::list<Topic> topic, const std::string message);
    void sendMaintenanceMessageAll(std::list<Topic> topic, const std::string message);
};


#endif //MTM4_BROKER_H
