#include <winsock2.h>
#include<windows.h>
#include "streamI.h"
//#define WIN32_LEAN_AND_MEAN
#include "mediastream.h"

StreamI::StreamI()
	:sm_(new StreamManager())
{
	
}

StreamI::~StreamI()
{
}

void StreamI::openRealStreamAsync(::Media::RealStreamReqParam param, ::std::function<void(const::Media::RealStreamRespParam&)> cb, ::std::function<void(::std::exception_ptr)>, const::Ice::Current &)
{
	sm_->addStream(param.id, param.name, param.pwd, param.ip, param.port, param.destip,  param.destport, param.ssrc, cb);
}

//void StreamI::openRealStream_async(const Media::AMD_Stream_openRealStreamPtr &cb, const Media::RealStream & ctg, const Ice::Current &)
//{
//	sm_->addStream(ctg.id,ctg.name, ctg.pwd, ctg.ip, ctg.port, ctg.destip, ctg.destport, ctg.ssrc, cb);
//	//Media::StreamInfo stm;
//	//stm.ip = "111111";
//	//cb->ice_response(stm);
//}

