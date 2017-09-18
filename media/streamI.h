#pragma once

#include <stream.h>
#include <memory>

class StreamManager;

class StreamI : public Media::Stream
{
public:
	StreamI();
	~StreamI();
	 virtual void openRealStreamAsync(::Media::RealStreamReqParam, ::std::function<void(const ::Media::RealStreamRespParam&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&);

private:
	std::unique_ptr<StreamManager> sm_;
};