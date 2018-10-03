#ifndef MTM4_CLIENT_H
#define MTM4_CLIENT_H


#include <exception>
#include <string>
#include <iostream>
#include "BrokerIfc.h"
#include "SortedSet.h"

class Client {
	int priority;
	int id;
	static int cnt;
protected:
	BrokerIfc& broker;
	SortedSet<const Topic> topics;
	std::ostream& messagesSink;
public:
    class ClientException : public std::exception {};
    class IllegalPriority : public ClientException {};
    class NonSubscribedTopic : public ClientException {};
    class NonPublishedTopic : public ClientException {};

    Client(int priority, BrokerIfc& broker, std::ostream& messagesSink = std::cout);

    Client(const Client& c) = delete;

    Client& operator=(const Client&) = delete;

    virtual ~Client()=default;

    int getPriority() const;

    int getId() const;

    void receiveMaintenanceMessage(const std::string& s) const;

};


#endif //MTM4_CLIENT_H
