#pragma once

#include "stream.h"
#include <memory>

class StreamManager;

class StreamI : public Media::Stream
{
public:
	StreamI();
	~StreamI();
	void  openRealStream_async(const Media::AMD_Stream_openRealStreamPtr &, const Media::RealStream &, const Ice::Current &);

private:
	std::unique_ptr<StreamManager> sm_;
};