#ifndef MTM4_ENCRYPTIONPUBLISHER_H
#define MTM4_ENCRYPTIONPUBLISHER_H


#include "Publisher.h"

class EncryptionPublisher : public Publisher {
	char key;
public:
	EncryptionPublisher(int priority, BrokerIfc& broker, char key, std::ostream& messagesSink = std::cout);
	virtual void sendMessage(const std::string& message, const Topic& t ) override;
};


#endif //MTM4_ENCRYPTIONPUBLISHER_H
