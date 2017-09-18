#pragma once
//#include <winsock2.h>
#include <string>
#include <memory>
#include <map>
#include <stream.h>
//#include "WorkorQueue.h"
#include "msgthread.h"
#include "jrtplib3\rtpsession.h"
#include "jrtplib3\rtpudpv4transmitter.h"
#include "jrtplib3\rtpipv4address.h"
#include "jrtplib3\rtpsessionparams.h"
//class RTPSession;
class MediaStream
{
public:
	using RTPTransmitterPtr = std::shared_ptr<jrtplib::RTPTransmitter> ;

	MediaStream(const std::string &id, const std::string &name, const std::string &pwd, 
		        const std::string &ip, int port, const std::string &destIp, int destPort,
		        std::function<void(const::Media::RealStreamRespParam&)> iceCB);
	MediaStream(const std::string &id);
	virtual ~MediaStream()
	{

	}

	void addDestHost(const std::string& destIp, int destPort);
	std::string addsubStream(const std::string& destIp, int destPort, int ssrc, RTPTransmitterPtr transmitter);
	virtual bool openStream() = 0;
	virtual bool openStream(const std::string &callid) = 0;
	virtual void closeStream(const std::string &callid) = 0;
	void sendPacket(unsigned char* data, unsigned int len );
protected:
	std::string id_;
	std::string name_;
	std::string pwd_;
	std::string ip_;
	int port_;
	std::string destIp_;
	int destPort_;
	std::function<void(const::Media::RealStreamRespParam&)> iceCB_;
	struct subStream
	{
#define RTP_MAX_PACKET_LEN 1450
		subStream(const std::string& destIp, int destPort, const std::string& ip,int port, int ssrc, RTPTransmitterPtr transmitter) :
			destIp_(destIp), ip_(),destPort_(destPort), port_(port), ssrc_(ssrc),rtpss_(new jrtplib::RTPSession), transmitter_(transmitter)
		{
			destipn_ = inet_addr(destIp_.c_str());
			destipn_ = ntohl(destipn_);
		}
		subStream(const subStream &ss) = delete;
		//subStream(const subStream &ss):
		//	destIp_(ss.destIp_), ip_(ss.ip_), destPort_(ss.destPort_),
		//	port_(ss.port_), ssrc_(ss.ssrc_), rtpss_(std::move(ss.rtpss_))
		//{
		//	destIp_ = ss.destIp_;
		//	destPort_ = ss.destPort_;
		//}

		subStream(subStream&& ss):
			destIp_(std::move(ss.destIp_)), ip_(std::move(ss.ip_)),destPort_(ss.destPort_), 
			port_(ss.port_), ssrc_(ss.ssrc_), rtpss_(std::move(ss.rtpss_))
		{
			destipn_ = inet_addr(destIp_.c_str());
			destipn_ = ntohl(destipn_);
		}

		void checkerror(int rtperr)
		{
			if (rtperr < 0)
			{
				std::cout << "ERROR: " << jrtplib::RTPGetErrorString(rtperr) << std::endl;
				//exit(-1);
			}
		}

		int createRTPSession()
		{
			//jrtplib::RTPUDPv4TransmissionParams transParams;
			jrtplib::RTPSessionParams sessionParams;
			sessionParams.SetOwnTimestampUnit(1.0 / 90000.0);//RTP_TIMESTAMP_UNIT);
			sessionParams.SetAcceptOwnPackets(true);
			sessionParams.SetMaximumPacketSize(RTP_MAX_PACKET_LEN);
			sessionParams.SetPredefinedSSRC(ssrc_);

			//int rtpret = rtpss_->Create(sessionParams, &transParams);
			int rtpret = rtpss_->Create(sessionParams, transmitter_.get() );
			checkerror(rtpret);

			rtpret = rtpss_->SetDefaultPayloadType(96);
			//checkerror(rtpret);
			rtpret = rtpss_->SetDefaultMark(false);
			//checkerror(rtpret);
			rtpret = rtpss_->SetDefaultTimestampIncrement(3600);
			//checkerror(rtpret);

			uint32_t destip;
			destip = inet_addr(destIp_.c_str());
			destip = ntohl(destip);

			std::cout << "addsubStream---" << destIp_ << " : " << destPort_ << std::endl;

			jrtplib::RTPIPv4Address addr(destip, destPort_);
			rtpret = rtpss_->AddDestination(addr);
			//checkerror(rtpret);
			return rtpret;
		}
		
		int sendRtpPack(uint8_t * data, uint32_t len);

		
		~subStream()
		{
			//rtpss_->Destroy();
		}

		std::string destIp_;
		std::string ip_;
		int destPort_;
		int port_;
		int ssrc_;
		std::unique_ptr<jrtplib::RTPSession> rtpss_;
		RTPTransmitterPtr transmitter_;
		uint32_t destipn_;
		
	};

	//std::vector<subStream> subStreams_;
	std::map<std::string, subStream> subStreams_;
	bool isOpen_;
	bool isLogin_;
	//std::unique_ptr<jrtplib::RTPSession> rtpss_;
};


class RealSteam : public MediaStream
{
public:
	RealSteam(const std::string &id, const std::string &name, const std::string &pwd,
		      const std::string &ip, int port, const std::string &destIp_, int destPort,
		      std::function<void(const::Media::RealStreamRespParam&)> iceCB);
	//RealSteam();
	~RealSteam();

	virtual bool openStream();
	virtual bool openStream(const std::string &callid);
	virtual void closeStream(const std::string &callid);
private:


	
};

class VodSteam : public MediaStream
{
public:
	VodSteam(const std::string &id, const std::string &name, const std::string &pwd,
		     const std::string &ip, int port, const std::string &destIp, int destPort,
		     std::function<void(const::Media::RealStreamRespParam&)> iceCB ,const std::string &startTime,
		     const std::string &endTime);
	~VodSteam();

	virtual bool openStream();

private:
	std::string startTime_;
	std::string endTime_;


};



// 流对象管理器
class StreamManager
{
public:
	using RTPTransmitterPtr = std::shared_ptr<jrtplib::RTPTransmitter>;
	using Process = std::function<bool()>;

	StreamManager();
	//	streams_(), msgthread_()//, queue_()
	//{};
	~StreamManager()
	{
		if (transParams_)
		{
			delete transParams_;
		}
	}
	std::shared_ptr<MediaStream> getStream(const std::string &id);

	void addStream(const std::string &id, const std::string &name, const std::string &pwd,
		const std::string &ip, int port, const std::string &destIp_, int destPort, int ssrc,
		std::function<void(const::Media::RealStreamRespParam&)> iceCB);

	//bool openStream(const std::string &id, const std::string &callid);
	bool openStream( std::string id,  std::string callid);
private:
	std::map<std::string, std::shared_ptr<MediaStream>> streams_;
	RTPTransmitterPtr transmitter_;
	jrtplib::RTPUDPv4TransmissionParams * transParams_;
	MessageThread msgthread_;
	//WorkorQueue<std::function<bool()>> queue_;
	//WorkorQueue<function_wrapper> queue_;
};