#include "RTPSender.h"
#include "glog/logging.h"
#include "PSBuffer.h"

static void checkerror(int rtperr)
{
	if (rtperr < 0)
	{
		LOG(ERROR) << "jrtplib error: " << jrtplib::RTPGetErrorString(rtperr);
	}
}

void RTPSender::sendRTPPacket()
{
	while (true)
	{
		std::lock_guard<std::mutex> lk(mutex_);
		
		if (bufferMap_.empty())
		{
			std::this_thread::yield();
		}

		auto it = bufferMap_.begin();
		while (it != bufferMap_.end())
		{
			it->second->processData();
			it++;	
		}
	}
}

#define RTP_MAX_PACKET_LEN 1450

RTPSender::RTPSender():
	mutex_()//, buffer_(std::make_shared<PSBuffer>())
{
#ifdef RTP_SOCKETTYPE_WINSOCK
	WSADATA dat;
	WSAStartup(MAKEWORD(2, 2), &dat);
#endif // RTP_SOCKETTYPE_WINSOCK
	transParams_ = new jrtplib::RTPUDPv4TransmissionParams;
	transParams_->SetRTPSendBuffer(65535); // default: 32768
	transParams_->SetPortbase(16000);
	uint32_t localip;
	localip = inet_addr("192.168.21.221");
	localip = ntohl(localip);

	transParams_->SetBindIP(localip);
	transmitter_ = new jrtplib::RTPUDPv4Transmitter(nullptr);
	int ret = transmitter_->Init(true);
	checkerror(ret);
	ret = transmitter_->Create(1400, transParams_);
	checkerror(ret);

	senderThread_ = std::thread(&RTPSender::sendRTPPacket, this);
}

void RTPSender::addBuffer(std::string id, std::shared_ptr<PSBuffer> buf)
{
	std::lock_guard<std::mutex> lk(mutex_);
	bufferMap_.emplace(std::make_pair(id, buf));
}

void RTPSender::removeBuffer(std::string id)
{
	std::lock_guard<std::mutex> lk(mutex_);
	bufferMap_.erase(id);
}
