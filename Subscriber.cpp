#include "Subscriber.h"
#include "SortedSet.h"
#include "Client.h"
#include "EncryptionSubscriber.h"
#include "EncryptionPublisher.h"

Subscriber::Subscriber(const int priority, BrokerIfc& b, std::ostream& ss):
	Client(priority,b,ss) {
}

void Subscriber::subscribeToTopic(const Topic& t)
{
	broker.subscribeToTopic(*this,t);
	topics.insert(t);
}

void Subscriber::unsubscribeToTopic(const Topic& t)
{
	broker.unsubscribeToTopic(*this, t);
	topics.remove(t);
}

void Subscriber::unsubscribeAll()
{
	while (topics.size()>0) {
		unsubscribeToTopic(*topics.begin());
	}
}

void Subscriber::receiveMessage(const string message, const Topic& topic, const Client& sender)
{
	if (topics.find(topic)==topics.end()) {
		throw Client::NonSubscribedTopic();
		return;
	}
	messagesSink << "Topic: " << topic << ". Sender: #" << (sender.getId()) << ". Receiver: #" << getId()
			<<". Message: " << message << endl;
}





