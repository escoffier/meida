#include "PSBuffer.h"
#include<condition_variable>
#include <iostream>
#include <glog\logging.h>
#include "jrtplib3\rtpsessionparams.h"
//#include "jrtplib3\rtpudpv4transmitter.h"
#include "jrtplib3\rtpipv4address.h"
//#include "jrtplib3\rtpsessionparams.h"

PSBuffer::PSBuffer()
	//freeChain_(10)
{
	auto start = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < 100; i++)
	{
		BufferNode node;
		freeChain_.push(std::move(node));
	}
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	LOG(INFO) << "PSBuffer elapse  " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << " microseconds";
}

PSBuffer::~PSBuffer()
{
}

void PSBuffer::push(char * data, uint32_t len)
{
}

std::shared_ptr<PSBuffer::BufferNode> PSBuffer::getFreeNode()
{
	//LOG(INFO) << "busyChain_ : " << busyChain_.size() << "    freeChain_: " << freeChain_.size();

	std::shared_ptr<PSBuffer::BufferNode> node = freeChain_.try_pop();
	if (!node)
	{
		//空闲队列为空，需要创建新的节点
		LOG(INFO) << "too much datas";
		//node = std::make_shared<BufferNode>();
	}

	return node;
	//std::lock_guard<std::mutex> lk(freemutex_);
	//std::shared_ptr<PSBuffer::BufferNode> node;
	//if (freeChain_.size()%100 == 0 )
	//{
	//	std::cout << "freeChain_ size: " << freeChain_.size()<< std::endl;
	//	std::cout << "busyChain_ size: " << busyChain_.size() << std::endl;
	//}

	//if (freeChain_.empty())
	//{
	//	//空闲队列为空，需要创建新的节点
	//    node = std::make_shared<BufferNode>();	
	//}
	//else
	//{
	//	node = freeChain_.front();
	//	freeChain_.pop();
	//}
	//return node;
}

void PSBuffer::push(std::shared_ptr<BufferNode> node)
{
	busyChain_.push(std::move(*node));
}

void PSBuffer::addDestination(std::string callid, uint32_t destip, uint32_t destport, 
	                          uint32_t ssrc, uint8_t pt, jrtplib::RTPTransmitter* transmitter)
{
	PSBuffer::Destination dest;
	dest.destip_ = destip;
	dest.destport_ = destport;
	dest.ssrc_ = ssrc;
	dest.pt_ = pt;
	dest.createRTPSession(dest.ssrc_, transmitter);

	std::lock_guard<std::mutex> lk(destsmutex_);
	dests_.emplace(std::make_pair(callid,std::move(dest)));
}

void PSBuffer::removeDestination(const std::string & callid)
{
	std::lock_guard<std::mutex> lk(destsmutex_);
	 dests_.erase(callid); 
}

void PSBuffer::processData()
{
	//std::unique_lock<std::mutex> lk(busymutex_);
	//LOG(INFO) << "busyChain_ : " << busyChain_.size() << "    freeChain_: " << freeChain_.size();
	if (!busyChain_.empty())
	{
		std::shared_ptr<BufferNode> node = busyChain_.try_pop();
		if (!node)
		{
			return;
		}

		{
			std::lock_guard<std::mutex> lk(destsmutex_);
			auto it = dests_.begin();
			while (it != dests_.end() )
			{
				it->second.rtpsession_->ClearDestinations();
				jrtplib::RTPIPv4Address addr(it->second.destip_, it->second.destport_);
				it->second.rtpsession_->AddDestination(addr);

				uint32_t len = node->length_;
				uint8_t * data = node->data_;
				while (len > 1400)
				{
					int rtpret = it->second.rtpsession_->SendPacket(data, 1400, 96, false, 0);
					//fwrite(data, 1, 1400, streamfile);
					//checkerror(rtpret);
					data += 1400;
					len -= 1400;
				}

				if (len > 0)
				{
					it->second.rtpsession_->SendPacket(data, len, 96, false, 3600);
					//fwrite(data, 1, len, streamfile);
				}
				++it;
			}
		}
		freeChain_.push(std::move(*node));
	}
	return;
}

#define RTP_MAX_PACKET_LEN 1450

static void checkerror(int rtperr)
{
	if (rtperr < 0)
	{
		LOG(ERROR) << "jrtplib error: " << jrtplib::RTPGetErrorString(rtperr);
	}
}

int PSBuffer::Destination::createRTPSession(uint32_t ssrc, jrtplib::RTPTransmitter * transmitter)
{
	jrtplib::RTPSessionParams sessionParams;
	sessionParams.SetOwnTimestampUnit(1.0 / 90000.0);//RTP_TIMESTAMP_UNIT);
	sessionParams.SetAcceptOwnPackets(true);
	sessionParams.SetMaximumPacketSize(RTP_MAX_PACKET_LEN);
	sessionParams.SetPredefinedSSRC(ssrc);

	//RTPSessionPrt rtpss_(new jrtplib::RTPSession);
	int rtpret = rtpsession_->Create(sessionParams, transmitter);
	checkerror(rtpret);

	rtpret = rtpsession_->SetDefaultPayloadType(96);
	checkerror(rtpret);
	rtpret = rtpsession_->SetDefaultMark(false);
	checkerror(rtpret);
	rtpret = rtpsession_->SetDefaultTimestampIncrement(3600);
	checkerror(rtpret);
	return rtpret;
}
