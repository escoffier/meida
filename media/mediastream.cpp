#ifdef WINDOWS
#include <winsock2.h>
#include <windows.h>
#endif
#include "mediastream.h"
#include "zmd5.h"
#include <functional>
#include "threadpool.h"
#define WIN32_LEAN_AND_MEAN
#include "HCNetSDK.h"
#include "glog/logging.h"
#include "RTPSender.h"

FILE *streamfile = fopen("stream106", "wb");

void checkerror(int rtperr)
{
	if (rtperr < 0)
	{
		std::cout << "ERROR: " << jrtplib::RTPGetErrorString(rtperr) << std::endl;
		//exit(-1);
	}
}

// MediaStream::MediaStream(const std::string &id, const std::string &name, const std::string &pwd,
// 						 const std::string &ip, int port, const std::string &destIp, int destPort,
// 						 std::function<void(const ::Media::RealStreamRespParam &)> iceCB, std::function<void(::std::exception_ptr)> ecb,
// 						 std::shared_ptr<CamaraController> con) : id_(id), name_(name), pwd_(pwd), ip_(ip), port_(port), destIp_(destIp),
// 																  destPort_(destPort), iceCB_(iceCB), ecb_(ecb), isOpen_(false), isLogin_(false), buffer_(std::make_shared<Buffer>()), controller_(con)
// {
// 	//ThreadPool<PSBuffer>* pool = ThreadPool<PSBuffer>::getInstance();
// 	//pool->push_buffer(id_, buffer_);
// }

MediaStream::MediaStream(dt::OpenRealStreamParam &req, std::function<void(bool, const ::Media::RealStreamRespParam &)> iceCB,
						 /*std::function<void(::std::exception_ptr)> ecb,*/ std::shared_ptr<CamaraController> con)
{
}

void MediaStream::addDestHost(const std::string &destIp, int destPort)
{
}

std::string MediaStream::addsubStream(const std::string &callid, const std::string &destIp, int destPort,
									  int ssrc, int pt /*, jrtplib::RTPTransmitter* transmitter*/)
{
	std::lock_guard<std::mutex> lockGuard(mutex_);
	auto search = subStreams_.find(callid);
	if (search == subStreams_.end())
	{
		//subStreams_.emplace(std::pair<std::string, subStream>(md5str, ss));
		LOG(INFO) << "add substream : " << destIp << " - " << destPort << std::endl;
		subStream ss(destIp, destPort, "192.168.21.121", 1999, ssrc /*, transmitter_*/);

		std::shared_ptr<PaketSender> sender = std::make_shared<RTPSender>(destIp, destPort);
		sender->setParam("ssrc", "1111");
		sender->init();
		buffer_->addSender(callid, sender);

		//buffer_->addDestination(callid, ss.destipn_, destPort, ssrc, pt/*, transmitter*/);

		subStreams_.emplace(callid, std::move(ss));
	}
	return callid;
}

void MediaStream::removesubStream(const std::string &callid)
{
	{
		std::lock_guard<std::mutex> lockGuard(mutex_);
		subStreams_.erase(callid);
	}
	//buffer_->removeDestination(callid);
	buffer_->removeSender(callid);
}

size_t MediaStream::subStreamCount() const
{
	//std::lock_guard<std::mutex> lockGuard(mutex_);
	return subStreams_.size();
}

bool MediaStream::needClose()
{
	std::lock_guard<std::mutex> lockGuard(mutex_);
	return subStreams_.empty();
}

void MediaStream::processData(char *data, uint32_t len)
{
	LOG(WARNING) << "discard data";
	// std::shared_ptr<PSBuffer::BufferNode> node = buffer_->getFreeNode();
	// if (!node)
	// {
	// 	LOG(WARNING) << "discard data";
	// 	return;
	// }

	// memcpy(node->data_, data, len);
	// node->length_ = len;
	// buffer_->push(node);
}

void MediaStream::getNodeInfo(int &b, int &f)
{
	//buffer_->getNodeInfo(b, f);
}

RealSteam::RealSteam(dt::OpenRealStreamParam &req,
					 std::function<void(bool, const ::Media::RealStreamRespParam &)> iceCB,
					 std::shared_ptr<CamaraController> con) : MediaStream(req, iceCB, con)
{
}

RealSteam::~RealSteam()
{
}

bool RealSteam::openStream(const std::string &callid)
{
	//���������ȡ��Ƶ��

	if (controller_->openRealStream(id_, ip_, port_, name_, pwd_,
									[=](char *data, uint32_t len) { processData(data, len); }))
	{
		Media::RealStreamRespParam resp;
		//respinfo.callid = callid;
		//uint32_t ip = transParams.GetBindIP();
		//char strIp[16] = {0};
		//inet_ntop(AF_INET, (void*)&ip, strIp, 15);
		std::string strIp("192.168.254.233");
		resp.sourceip = strIp;
		resp.callid = callid;
		resp.id = id_;

		iceCB_(resp);
		return true;
	}
	else
	{
		//ecb_();
		return false;
	}
}

void RealSteam::closeStream(const std::string &callid)
{
	//std::lock_guard<std::mutex> lockGuard(mutex_);
	//auto search = subStreams_.find(callid);
	//if (search != subStreams_.end())
	//{
	//	size_t n =  subStreams_.count(callid);
	//	if (n == 0)
	//	{
	//		if (controller_->closeRealStream(search->second.id_))
	//		{
	//			LOG(ERROR) << "Hik sdk close stream failed, error code: " << NET_DVR_GetLastError();
	//		}
	//		else
	//		{
	//			LOG(INFO) << "Close stream: " << callid;
	//		}
	//
	//	}
	//	subStreams_.erase(search);
	//}

	return;
}

void RealSteam::closeStream()
{
	if (!controller_->closeRealStream(id_))
	{
		LOG(ERROR) << "Hik sdk close stream failed, error code: " << NET_DVR_GetLastError();
	}
	else
	{
		LOG(INFO) << "Close stream: " << id_;
	}
}

// VodSteam::VodSteam(const std::string &id, const std::string &name, const std::string &pwd,
// 				   const std::string &ip, int port, const std::string &destIp, int destPort,
// 				   std::function<void(const ::Media::RealStreamRespParam &)> iceCB, std::function<void(::std::exception_ptr)> ecb,
// 				   const std::string &startTime, const std::string &endTime, std::shared_ptr<CamaraController> con) : MediaStream(id, name, pwd, ip, port, destIp, destPort, iceCB, ecb, con), startTime_(startTime), endTime_(endTime)
VodSteam::VodSteam(dt::OpenRealStreamParam &req,
				   std::function<void(bool returnValue, const ::Media::RealStreamRespParam &)> iceCB,
				   std::shared_ptr<CamaraController> con) : MediaStream(req, iceCB, con)
{
}

VodSteam::~VodSteam()
{
}

bool VodSteam::openStream(const std::string &callid)
{
	return false;
}

void VodSteam::closeStream(const std::string &callid)
{
}

void VodSteam::closeStream()
{
}

StreamManager *StreamManager::instance_ = nullptr;
//template<>  ThreadPool<PSBuffer> * ThreadPool<PSBuffer>::instance_ = nullptr;

StreamManager *StreamManager::getInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new StreamManager;
	}

	return instance_;
}

StreamManager::StreamManager() : streams_(), msgthread_(), locker_(), /*rtpSender_(new RTPSender),*/ plugins_(new SDKPlugins),
								 avThreadPool_(std::make_shared<ThreadPool>(4))
{
	NET_DVR_Init();
};

std::shared_ptr<MediaStream> StreamManager::getStream(const std::string &id)
{
	auto search = streams_.find(id);
	if (search != streams_.end())
	{
		return search->second;
	}
	return nullptr;
}

// void StreamManager::addStream(Media::RealStreamReqParam &param,
// 							  const std::function<void(bool, const ::Media::RealStreamRespParam &)> iceCB,
// 							  std::function<void(::std::exception_ptr)> ecb)
// {
// 	//std::lock_guard<std::mutex> lockGuard(locker_);

// 	//auto search = streams_.find(id);
// 	//if (search == streams_.end())
// 	//{
// 	//	std::shared_ptr<MediaStream> ms = std::make_shared<RealSteam>(id, name, pwd, ip, port, destIp, destPort, iceCB, ecb);

// 	//    ms->addsubStream(destIp, destPort, ssrc, transmitter_);
// 	//	streams_.emplace(id, ms);
// 	//
// 	//	msgthread_.submit([=]() {
// 	//		openStream(id, callid);
// 	//	});
// 	//}
// 	//else
// 	//{
// 	//	//search->second->addDestHost(destIp, destPort);
// 	//	search->second->addsubStream(destIp, destPort, ssrc, transmitter_);
// 	//}
// }

void StreamManager::addStream(dt::OpenRealStreamParam &param, std::function<void(bool, const ::Media::RealStreamRespParam &)> iceCB)
{
	std::lock_guard<std::mutex> lockGuard(locker_);

	std::shared_ptr<CamaraController> controller;
	Media::RealStreamRespParam resp;

	auto search = streams_.find(param.id);
	if (search == streams_.end())
	{
		auto search = controllers_.find("hkdevice");

		if (search == controllers_.end())
		{
			controller = loadPlugin("hkdevice");
			if (!controller)
			{
				LOG(ERROR) << "load plugin failed";
				// Media::OpenStreamException ex;
				// ex.reason = "load plugin failed";
				// ex.callid = param.callid;
				
				iceCB(false, resp);
				//excb(make_exception_ptr(ex));
				return;
			}
		}
		else
		{
			controller = search->second;
		}

		std::shared_ptr<MediaStream> ms = std::make_shared<RealSteam>(param, iceCB, controller);

		ms->addsubStream(param.callid, param.destip, param.destport,
						 param.ssrc, param.pt);

		std::shared_ptr<Buffer> buf = std::make_shared<Buffer>();
		std::shared_ptr<PaketSender> sender = std::make_shared<RTPSender>(param.destip, param.destport);
		buf->addSender(param.callid, sender);

		avThreadPool_->attachBuffer(param.id, buf);

		streams_.emplace(param.id, ms);

		//msgthread_.submit([=]() {
		//openStream(param.id, param.callid, iceCB, excb);
		msgthread_.submit([=]() {
			//Media::RealStreamRespParam resp;
			if (!ms->openStream(param.callid))
			{
				LOG(ERROR) << "Cann't find stream: " << param.id << std::endl;
				iceCB(false, resp);
				return false;
			}
		});
	}
	else
	{
		std::shared_ptr<PaketSender> sender = std::make_shared<RTPSender>(param.destip, param.destport);
		//Media::RealStreamRespParam resp;
		resp.id = param.id;
		resp.callid = param.callid;
		resp.sourceip = "192.168.254.233";
		resp.sourceport = "18000";

        auto buf = avThreadPool_->getBuffer(param.id);
		if(buf != nullptr)
		{
			buf->addSender(param.callid, sender);
			search->second->addsubStream(param.callid, param.destip, param.destport, param.ssrc, param.pt);
			iceCB(true, resp);
		}
		else
		{
			iceCB(false, resp);
		}
	}
}

// bool StreamManager::openStream(std::string id, std::string callid, std::function<void(const ::Media::RealStreamRespParam &)> iceCB, std::function<void(::std::exception_ptr)> excb)
// {
// 	std::lock_guard<std::mutex> lockGuard(locker_);
// 	auto search = streams_.find(id);
// 	if (search == streams_.end())
// 	{
// 		LOG(ERROR) << "Cann't find stream: " << id << std::endl;
// 		Media::OpenStreamException ex;
// 		ex.reason = "Cann't find stream";
// 		excb(std::make_exception_ptr(ex));
// 		return false;
// 	}
// 	else
// 	{
// 		if (!search->second->openStream(callid))
// 		{
// 			LOG(ERROR) << "Cann't open stream: " << id << std::endl;

// 			//ThreadPool<PSBuffer>::getInstance()->remove_buffer(id);
// 			streams_.erase(id);

// 			Media::OpenStreamException ex;
// 			ex.reason = "Cann't open stream";
// 			excb(std::make_exception_ptr(ex));

// 			return false;
// 		}
// 	}
// 	Media::RealStreamRespParam resp;
// 	resp.id = id;
// 	resp.callid = callid;
// 	resp.sourceip = "192.168.254.233";
// 	resp.sourceport = "18000";
// 	iceCB(resp);
// 	return true;
// }

void StreamManager::closeStream(std::string id, std::string callid)
{
	std::lock_guard<std::mutex> lockGuard(locker_);
	auto search = streams_.find(id);
	if (search == streams_.end())
	{
		LOG(ERROR) << "Cann't find stream: " << id << std::endl;
		return;
	}
	else
	{
		search->second->removesubStream(callid);
		
        auto buf = avThreadPool_->getBuffer(param.id);
		if(buf != nullptr)
		{
            buf->removeSender(callid);
		}

		if (search->second->needClose())
		{
			//�����ǰ�������ֻ��һ·��Ƶ���������������streams_ժ��
			search->second->closeStream();
			avThreadPool_->removeBuffer(param.id);
			//ThreadPool<PSBuffer>::getInstance()->remove_buffer(id);
			//rtpSender_->removeBuffer(id);
			streams_.erase(search);
		}
	}
	return;
}

void StreamManager::getStreamStatic(std::string id, ::Media::StreamStatic &stat)
{
	std::lock_guard<std::mutex> lockGuard(locker_);
	auto search = streams_.find(id);
	if (search == streams_.end())
	{
		LOG(ERROR) << "(getStreamStatic)Cann't find stream: " << id << std::endl;
		return;
	}
	else
	{
		search->second->getNodeInfo(stat.busynode, stat.freenode);
	}
	return;
}

typedef CamaraController *(*CREATE_PTR)();

std::shared_ptr<CamaraController> StreamManager::loadPlugin(const std::string &name)
{
	if (!plugins_->Load("./", name.c_str()))
	{
		LOG(ERROR) << "Load " << name << ".dll failed!";
		return std::shared_ptr<CamaraController>();
	}

	CREATE_PTR func = (CREATE_PTR)plugins_->GetFuncAddr("GetController");
	if (func == nullptr)
	{
		LOG(ERROR) << "GetFuncAddr failed!";
		return std::shared_ptr<CamaraController>();
	}

	std::shared_ptr<CamaraController> controller = std::shared_ptr<CamaraController>(func());
	if (controller == nullptr)
	{
		LOG(ERROR) << "CamaraController is null!";
		return std::shared_ptr<CamaraController>();
	}

	controllers_.emplace(std::make_pair(name, controller));
	LOG(INFO) << "load plugin : " << name << ".dll";

	return controller;
}

std::shared_ptr<CamaraController> StreamManager::getController(const std::string &name)
{
	auto search = controllers_.find(name);
	std::shared_ptr<CamaraController> controller;

	if (search == controllers_.end())
	{
		controller = loadPlugin("hkdevice");
		if (!controller)
		{
			LOG(ERROR) << "load plugin failed";
			//Gateway::DeviceControlException ex;
			//ex.reason = "load plugin failed";
			//excb(make_exception_ptr(ex));
			return std::shared_ptr<CamaraController>();
			;
		}
	}
	else
	{
		controller = search->second;
	}

	return controller;
}

std::string StreamManager::buildCallId(const std::string &ip, int port)
{
	unsigned char buff[128] = {0};
	md5_state_t mdctx;
	md5_byte_t md_value[16];

	snprintf((char *)buff, 127, "%s%d", ip.c_str(), port);
	md5_init(&mdctx);
	md5_append(&mdctx, (const unsigned char *)(buff), strlen((const char *)buff));
	md5_finish(&mdctx, md_value);

	char md5sum[33];
	int i;
	int h, l;
	for (i = 0; i < 16; ++i)
	{
		h = md_value[i] & 0xf0;
		h >>= 4;
		l = md_value[i] & 0x0f;
		md5sum[i * 2] = (char)((h >= 0x0 && h <= 0x9) ? (h + 0x30) : (h + 0x57));
		md5sum[i * 2 + 1] = (char)((l >= 0x0 && l <= 0x9) ? (l + 0x30) : (l + 0x57));
	}
	md5sum[32] = '\0';

	std::string md5str(md5sum);
	return md5str;
}
