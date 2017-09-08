#pragma once
//#include <winsock2.h>
#include <string>
#include <memory>
#include "stream.h"
//#include "WorkorQueue.h"
#include "msgthread.h"
#include "jrtplib3\rtpsession.h"

//class RTPSession;
class MediaStream
{
public:
	MediaStream(const std::string &id, const std::string &name, const std::string &pwd, 
		        const std::string &ip, int port, const std::string &destIp_, int destPort,
		        const Media::AMD_Stream_openRealStreamPtr &iceCB);
	MediaStream(const std::string &id);
	virtual ~MediaStream()
	{

	}

	void addDestHost(const std::string& destIp, int destPort);
	std::string addsubStream(const std::string& destIp, int destPort);
	virtual bool openStream() = 0;
	virtual bool openStream(const std::string &callid) = 0;
	virtual void closeStream(const std::string &callid) = 0;
protected:
	std::string id_;
	std::string name_;
	std::string pwd_;
	std::string ip_;
	int port_;
	std::string destIp_;
	int destPort_;
	Media::AMD_Stream_openRealStreamPtr iceCB_;
	struct subStream
	{
		subStream(const std::string& destIp, int destPort, const std::string& ip,int port) :
			destIp_(destIp), ip_(),destPort_(destPort), port_(port)
		{
		}
		subStream(const subStream &ss):
			destIp_(ss.destIp_), ip_(ss.ip_), destPort_(ss.destPort_), port_(ss.port_)
		{
			destIp_ = ss.destIp_;
			destPort_ = ss.destPort_;
		}

		subStream(subStream&& ss):
			destIp_(std::move(ss.destIp_)), ip_(std::move(ss.ip_)),destPort_(ss.destPort_), port_(ss.port_)
		{

		}

		~subStream()
		{}

		std::string destIp_;
		std::string ip_;
		int destPort_;
		int port_;
	};

	//std::vector<subStream> subStreams_;
	std::map<std::string, subStream> subStreams_;
	bool isOpen_;
	bool isLogin_;
	std::unique_ptr<jrtplib::RTPSession> rtpss_;
};


class RealSteam : public MediaStream
{
public:
	RealSteam(const std::string &id, const std::string &name, const std::string &pwd,
		      const std::string &ip, int port, const std::string &destIp_, int destPort,
		      const Media::AMD_Stream_openRealStreamPtr &iceCB);
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
		     const Media::AMD_Stream_openRealStreamPtr &iceCB ,const std::string &startTime, 
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
	//using Process = std::function<bool(const std::string &)>;
	using Process = std::function<bool()>;

	StreamManager();
	//	streams_(), msgthread_()//, queue_()
	//{};
	~StreamManager()
	{

	}
	std::shared_ptr<MediaStream> getStream(const std::string &id);

	void addStream(const std::string &id, const std::string &name, const std::string &pwd,
		const std::string &ip, int port, const std::string &destIp_, int destPort,
		const Media::AMD_Stream_openRealStreamPtr &iceCB);

	//bool openStream(const std::string &id, const std::string &callid);
	bool openStream( std::string id,  std::string callid);
private:
	std::map<std::string, std::shared_ptr<MediaStream>> streams_;

	MessageThread msgthread_;
	//WorkorQueue<std::function<bool()>> queue_;
	//WorkorQueue<function_wrapper> queue_;
};