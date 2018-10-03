#include <exception>
#include <string>
#include "BrokerIfc.h"
#include "Client.h"
#include "SortedSet.h"

int Client::cnt=0;

Client::Client(int priority, BrokerIfc& broker, std::ostream& messagesSink) :
	priority(priority),  id(cnt), broker(broker), messagesSink(messagesSink){
	if (priority<0)
	{
		throw Client::IllegalPriority();
		return;
	}
	cnt++;
}

int Client::getPriority() const {
	return priority;
}

int Client::getId() const {
	return id;
}

void Client::receiveMaintenanceMessage(const std::string& s) const {
	messagesSink << "Client #" << getId() << " received maintenance message: " << s << endl;
}
