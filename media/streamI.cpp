#include "streamI.h"
#include "mediastream.h"

StreamI::StreamI()
	:sm_(std::make_shared<StreamManager>())
{
	
}

StreamI::~StreamI()
{
}

void StreamI::openRealStream_async(const Media::AMD_Stream_openRealStreamPtr &cb, const Media::Catalog &, const Ice::Current &)
{
	Media::StreamInfo stm;
	stm.ip = "111111";
	cb->ice_response(stm);
}

