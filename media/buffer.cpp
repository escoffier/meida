#include "buffer.h"

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

void Buffer::addSender(const std::string &callid, std::shared_ptr<PaketSender> sender)
{
	std::lock_guard<std::mutex> lk(destsmutex_);
	senders_.emplace(callid, sender);
}

void Buffer::removeSender(const std::string &callid)
{
	std::lock_guard<std::mutex> lk(destsmutex_);
	senders_.erase(callid);
}

void Buffer::operator()()
{
}

void Buffer::clearSenders()
{
	std::lock_guard<std::mutex> lk(destsmutex_);
	senders_.clear();
}
int Buffer::senderNumber()
{
	std::lock_guard<std::mutex> lk(destsmutex_);
	return senders_.size();
}
void Buffer::processData()
{
	std::lock_guard<std::mutex> lk(destsmutex_);
	for (auto &sender : senders_)
	{
		//sender.send()
	}
}