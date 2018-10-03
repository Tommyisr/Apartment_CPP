#ifndef MTM4_ENCRYPTIONSUBSCRIBER_H
#define MTM4_ENCRYPTIONSUBSCRIBER_H


#include "Subscriber.h"

class EncryptionSubscriber : public Subscriber {
	char key;
public:
	EncryptionSubscriber(int priority, BrokerIfc& broker, char key, std::ostream& messagesSink = std::cout);
	  void recieveMessage(const std::string& message, const Topic& t, const Client& sender ) ;
};


#endif //MTM4_ENCRYPTIONSUBSCRIBER_H
