#ifdef WINDOWS
#include <winsock2.h>
#include<windows.h>
#endif
#include "streamI.h"
//#define WIN32_LEAN_AND_MEAN
#include "mediastream.h"
#include "utility.h"
#include "glog/logging.h"

StreamI::StreamI()
	//:sm_(new StreamManager())
{
	
}

StreamI::~StreamI()
{
}

void StreamI::openRealStreamAsync(::Media::RealStreamReqParam param, ::std::function<void(const::Media::RealStreamRespParam&)> cb, ::std::function<void(::std::exception_ptr)> ecb, const::Ice::Current &)
{
	LOG(INFO) << param.callid;
	StreamManager::getInstance()->addStream(param, cb, ecb);
	//sm_->addStream(param.id, param.callid,param.name, param.pwd, param.ip, param.port, param.destip,  param.destport, param.ssrc, cb, ecb);
}

void StreamI::closeStreamAsync(::std::string callid, ::std::string id, ::std::function<void()> cb, ::std::function<void(::std::exception_ptr)> excb, const::Ice::Current &)
{
	
	StreamManager::getInstance()->closeStream(id, callid);
	cb();
}

void StreamI::getStreamStatic(::std::string id, ::Media::StreamStatic & stat, const::Ice::Current &)
{
	StreamManager::getInstance()->getStreamStatic(id, stat);
}

//void StreamI::openRealStream_async(const Media::AMD_Stream_openRealStreamPtr &cb, const Media::RealStream & ctg, const Ice::Current &)
//{
//	sm_->addStream(ctg.id,ctg.name, ctg.pwd, ctg.ip, ctg.port, ctg.destip, ctg.destport, ctg.ssrc, cb);
//	//Media::StreamInfo stm;
//	//stm.ip = "111111";
//	//cb->ice_response(stm);
//}

