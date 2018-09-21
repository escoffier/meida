#pragma once
//#include "jrtplib3\rtpsession.h"
#include "jrtplib3/rtpudpv4transmitter.h"
#include "jrtplib3/rtpipv4address.h"
#include "jrtplib3/rtpsessionparams.h"
#include <memory>
#include <map>
#include <mutex>
#include "PSBuffer.h"
#include "threadsafequeue.h"
#include <thread>

class RTPSender
{
public:
	//using RTPTransmitterPtr = std::shared_ptr<jrtplib::RTPTransmitter>;
	//using RTPSessionPrt = std::unique_ptr<jrtplib::RTPSession>;
	RTPSender();


	~RTPSender()
	{
		if (transmitter_)
		{
			delete transmitter_;
		}
	}

	void sendRTPPacket();
	jrtplib::RTPTransmitter *getRTPTransmitter() { return transmitter_; };

	void addBuffer(std::string, std::shared_ptr<PSBuffer> buf);
	void removeBuffer(std::string id);

private:
	jrtplib::RTPTransmitter* transmitter_;
	jrtplib::RTPUDPv4TransmissionParams * transParams_;
	std::map<std::string, std::shared_ptr<PSBuffer> > bufferMap_;
	//std::list< std::shared_ptr<PSBuffer> > bufferMap_;
	threadsafe_queue<std::shared_ptr<PSBuffer> > bufferQueue_;
	std::mutex mutex_;
	std::thread senderThread_;
};