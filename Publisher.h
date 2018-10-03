#ifndef MTM4_PUBLISHER_H
#define MTM4_PUBLISHER_H

#include "Client.h"
#include "Broker.h"
#include "SortedSet.h"

class Publisher : public Client {
	public:
		Publisher(const int priority, BrokerIfc& b, std::ostream& messagesSink = std::cout);
		~Publisher()=default;
		void publishTopic(const Topic& t);
		void unpublishTopic(const Topic& t);
		void unpublishAll();
		virtual void sendMessage(const std::string& message, const Topic& t );
};


#endif //MTM4_PUBLISHER_H
