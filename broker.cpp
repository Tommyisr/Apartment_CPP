#include <map>
#include <list>
#include "SortedSet.h"
#include "Client.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "BrokerIfc.h"
#include "Broker.h"
#include "EncryptionSubscriber.h"
#include "EncryptionPublisher.h"
#include <typeinfo>
bool Broker::CompareClients::operator() (const Client& c1, const Client& c2) const {
	if (c1.getPriority()==c2.getPriority()) {
		return (c1.getId()<c2.getId());
	}
	else {
		return (c1.getPriority()<c2.getPriority());
	}
}

bool Broker::CompareClientsPtr::operator() (const Client* const c1, const Client* const c2) const {
	return CompareClients()(*c1, *c2);
}

Broker::Broker() :
	map() {
}

void Broker::subscribeToTopic(const Subscriber& sub, const Topic& t) {
	if (map.find(t)==map.end()) {
		auto& set=map[t];
		set.insert((Client* const)&sub);
		map.insert(make_pair(t,set));
		return;
	}
	auto& set=map[t];
	set.insert((Client*)&sub);
}

void Broker::unsubscribeToTopic(const Subscriber& sub, const Topic& t) {
	if (map.find(t)==map.end()) {
		throw Client::NonSubscribedTopic(); // fix
		return;
	}
	auto& set=map[t];
	if (set.remove((Client*const)&sub)==false) {
		throw Client::NonSubscribedTopic();
	}
}

void Broker::publishTopic(const Publisher& pub, const Topic& t) {
	if (map.find(t)==map.end()) {
		auto& set=map[t];
		set.insert((Client* const)&pub);
		map.insert(make_pair(t,set));
		return;
	}
	auto& set=map[t];
	set.insert((Client* const)&pub);
}

void Broker::unpublishTopic(const Publisher& pub, const Topic& t) {
	if (map.find(t)!=map.end()) {
		auto& set=map[t];
		if (set.remove((Client* const)&pub)==false) {
			throw Client::NonPublishedTopic();
			return;
		}
	}
	else
		{
		throw Client::NonPublishedTopic();
		}
}

void Broker::publishMessage(const Topic& t, const std::string& message, const Client& sender) const {
	if (this->map.find(t)==this->map.end()) {
		throw Client::NonPublishedTopic();
		return;
	}
	auto& set=map.find(t)->second;
	//const EncryptionPublisher&  encrypt_pub =  dynamic_cast<const EncryptionPublisher& >(sender) ;
	for (auto it=set.begin(); it!=set.end(); ++it) {
		Subscriber* const sub_i=dynamic_cast<Subscriber* const>(*it);
		EncryptionSubscriber* const encrypt_sub = dynamic_cast<EncryptionSubscriber* const>(*it);
		if (sub_i!=NULL) {

			if (encrypt_sub!=NULL)
			{
				encrypt_sub->recieveMessage(message,t,sender);
			}

			else {sub_i->receiveMessage(message,t,sender);};


			//if (const EncryptionPublisher&  encrypt_pub =  dynamic_cast<const EncryptionPublisher& >(sender));
/*
				if (encrypt_sub!=NULL)
				{
					try
					{
					const EncryptionPublisher&  encrypt_pub =  dynamic_cast<const EncryptionPublisher& >(sender);
					//cout << "ASD" << endl;
					encrypt_sub->receiveMessage(message,t,sender); /// doesn't work
					}
					catch (const std::bad_cast& e)
					{

					}
					}
				else {
					*/

				}
			//}
		}
	//}
}

void Broker::sendMaintenanceMessage(std::string message, SortedSet<Client* const, CompareClientsPtr> set) {
	for (auto it=set.begin(); it!=set.end(); ++it) {
		//Subscriber* const sub_i=dynamic_cast<Subscriber* const>(*it);
		//if (sub_i!=NULL) {
			//sub_i->receiveMaintenanceMessage(message);
	//}
		(*it)->receiveMaintenanceMessage(message);
}
}

void Broker::sendMaintenanceMessageAny(std::list<Topic> topic, const std::string message) {
	auto first=*topic.begin();
	auto set=map[first];
	for (auto topic_i=topic.begin(); topic_i!=topic.end(); ++topic_i) {
		auto set2=set|map[*topic_i];
		set=set2;
	}
	sendMaintenanceMessage(message,set);
}

void Broker::sendMaintenanceMessageAll(std::list<Topic> topic, const std::string message) {
	Topic first=*topic.begin();
	auto set=map[first];
	for (auto topic_i= topic.begin(); topic_i!=topic.end(); topic_i++) {
		auto set3=map[*topic_i];
		auto set2=set&set3;
		set=set2;

	}
	sendMaintenanceMessage(message, set);
}


