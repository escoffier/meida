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

void StreamI::openRealStream_async(const Media::AMD_Stream_openRealStreamPtr &cb, const Media::RealStream & ctg, const Ice::Current &)
{
	sm_->addStream(ctg.id,ctg.name, ctg.pwd, ctg.ip, ctg.port, ctg.destip, ctg.destport, cb);
	//Media::StreamInfo stm;
	//stm.ip = "111111";
	//cb->ice_response(stm);
}

