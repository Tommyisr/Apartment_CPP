#include "Publisher.h"
#include "SortedSet.h"


Publisher::Publisher(const int priority, BrokerIfc& b, std::ostream& ss):
	Client(priority,b,ss) {
}

void Publisher::publishTopic(const Topic& t)
{
	broker.publishTopic(*this,t);
	topics.insert(t);
}

void Publisher::unpublishTopic(const Topic& t)
{
	broker.unpublishTopic(*this, t);
	topics.remove(t);
}

void Publisher::unpublishAll()
{
	while (topics.size()>0) {
		unpublishTopic(*topics.begin());
	}
}

void Publisher::sendMessage(const std::string& message, const Topic& t )
{
	//this->
	if (topics.find(t)==topics.end()) {
		throw Client::NonPublishedTopic();
		return;
	}
	broker.publishMessage(t, message, *this);
}






