#include "mediaclient.h"
#include <Ice/Ice.h>
#include "glog\logging.h"

MediaClient::MediaClient():
	initiated_(false), stream_(nullptr), realcbmaps()
{
}

MediaClient::~MediaClient()
{
}

bool MediaClient::init()
{
	try
	{
		Ice::CommunicatorPtr communicator = Ice::initialize();
		Ice::PropertiesPtr props = communicator->getProperties();
		props->load("config.media");

		stream_ = Ice::checkedCast<Media::StreamPrx>(communicator->propertyToProxy("Stream.Proxy"));
		if (!stream_)
		{
			LOG(ERROR) << " couldn't find a Media::StreamPrx object.";
			initiated_ = false;
			return false;
		}

		initiated_ = true;
		return true;
	}
	catch (const Ice::Exception& e)
	{
		initiated_ = false;
		LOG(ERROR) << e.what();
		return false;
	}
	catch (const std::exception& e)
	{
		initiated_ = false;
		LOG(ERROR) << e.what();
		return false;
	}
}

void MediaClient::openRealStream(string id, string ip, int port, string name, string pwd, 
	                             string destip, int destport,int ssrc, 
	                             std::function<void(const::Gateway::RealStreamRespParam&)> cb,
	                             std::function<void(::std::exception_ptr)> ecb)
{
	if (!initiated_)
	{
		Gateway::OpenStreamException e;
		e.reason = "not connected to media server!";
		ecb(std::make_exception_ptr(e));
		return;
	}
	Media::RealStreamReqParam st;
	st.id = id;
	st.ip = ip;
	st.name = name;
	st.pwd = pwd;
	st.port = port;
	st.destip = destip;
	st.destport = destport;
	st.ssrc = ssrc;
	string callid = "ip@port-real";
	st.callid = callid;
	callback cbs;
	cbs.respcb_ = cb;
	cbs.excb_ = ecb;
	realcallbacks_.emplace(make_pair<string, callback>(string(callid), std::move(cbs)));

	stream_->openRealStreamAsync(st, [=](Media::RealStreamRespParam param) { response(param); }, 
		                         [=](std::exception_ptr ex) { exception(callid, ex); });

}

void MediaClient::openRealStream(dt::OpenRealStream streamParam, std::function<void(const::Gateway::RealStreamRespParam&)> cb, std::function<void(::std::exception_ptr)> ecb)
{
	if (!initiated_)
	{
		Gateway::OpenStreamException e;
		e.reason = "not connected to media server!";
		ecb(std::make_exception_ptr(e));
		return;
	}

	Media::RealStreamReqParam stream;
	stream.id = streamParam.id;
	stream.ip = streamParam.ip;
	stream.name = streamParam.name;
	stream.pwd = streamParam.pwd;
	stream.port = streamParam.port;
	stream.destip = streamParam.destip;
	stream.destport = streamParam.destport;
	stream.ssrc = streamParam.ssrc;
	stream.callid = streamParam.callid;
	stream.pt = streamParam.pt;

	callback cbs;
	cbs.respcb_ = cb;
	cbs.excb_ = ecb;
	realcallbacks_.emplace(make_pair<string, callback>(string(stream.callid), std::move(cbs)));

	stream_->openRealStreamAsync(stream, [=](Media::RealStreamRespParam param) { response(param); },
		[=](std::exception_ptr ex) { exception(stream.callid, ex); });
}

void MediaClient::closeStream(std::string callid, string id)
{
	stream_->closeStreamAsync(callid, id);
}

void MediaClient::emplacecallback(std::function<void(const::Gateway::RealStreamRespParam&)> respcb, std::function<void(::std::exception_ptr)> excb)
{
	callback cb;
	cb.respcb_ = respcb;
	cb.excb_ = excb;
	realcallbacks_.emplace();
}
