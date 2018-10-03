#include "Publisher.h"
#include "EncryptionPublisher.h"

EncryptionPublisher::EncryptionPublisher(int priority, BrokerIfc& broker, char key, std::ostream& messagesSink):
	Publisher(priority,broker,messagesSink), key(key){
}

void EncryptionPublisher::sendMessage(const std::string& message, const Topic& t ) {
	string message2(message);
	for(char& c : message2) {
		c=(char)c^key;
	}
	//this->
	Publisher::sendMessage(message2, t);
}
