#include "Subscriber.h"
#include "EncryptionSubscriber.h"

EncryptionSubscriber::EncryptionSubscriber(int priority, BrokerIfc& broker, char key, std::ostream& messagesSink) :
	Subscriber(priority,broker,messagesSink), key(key){
}

void EncryptionSubscriber::recieveMessage(const std::string& message, const Topic& t, const Client& sender ) {
	string message2(message);
	for(char& c : message2) {
		//c='s';
		c=(char)key^c;
	}
	Subscriber::receiveMessage(message2,t,sender);
}
