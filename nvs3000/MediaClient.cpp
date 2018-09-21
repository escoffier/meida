#include "mediaclient.h"
#include <Ice/Ice.h>
#include <IceGrid/IceGrid.h>
#include "glog/logging.h"

MediaClient::MediaClient():
	initiated_(false), stream_(nullptr), realcbmaps()
{
}

MediaClient::~MediaClient()
{
}

bool MediaClient::init()
{

	//Ice::CommunicatorPtr communicator = Ice::initialize();
	//Ice::PropertiesPtr props = communicator->getProperties();

	//catch (const Ice::Exception& e)
	//{
	//	initiated_ = false;
	//	LOG(ERROR) << e.what();
	//	return false;
 //    }
	//catch (const std::exception& e)
	//{
	//	initiated_ = false;
	//	LOG(ERROR) << e.what();
	//	return false;
	//}
	shared_ptr<Ice::Communicator> communicator = Ice::initialize("config.mediaclient");
	try
	{
#ifdef STANDALONE
		props->load("config.media");
		stream_ = Ice::checkedCast<Media::StreamPrx>(communicator->propertyToProxy("Stream.Proxy"));
	}
	if (!stream_)
	{
		LOG(ERROR) << " couldn't find a Media::StreamPrx object.";
		initiated_ = false;
		return false;
	}

	initiated_ = true;
	return true;
#else
		//props->load("config.mediaclient");
		stream_ = Ice::checkedCast<Media::StreamPrx>(communicator->stringToProxy("stream"));
	}
	catch (const Ice::NotRegisteredException&)
	{
		auto query = Ice::checkedCast<IceGrid::QueryPrx>(communicator->stringToProxy("MediaGrid/Query"));
		stream_ = Ice::checkedCast<Media::StreamPrx>(query->findObjectByType("::Media::Stream"));
	}
	catch (const Ice::NoEndpointException &e)
	{
		LOG(ERROR) << e.what();
	}

	if (!stream_)
	{
		LOG(ERROR) << " couldn't find a Media::StreamPrx object.";
		return false;
	}

	stream_->ice_connectionCached(false);
	stream_->ice_getConnection()->setACM(30, Ice::nullopt, Ice::ACMHeartbeat::HeartbeatOnIdle);
	initiated_ = true;
	return true;
#endif
}

void MediaClient::openRealStream(string id, string ip, int port, string name, string pwd, 
	                             string destip, int destport,int ssrc, 
	                             std::function<void(const::Media::RealStreamRespParam&)> cb,
	                             std::function<void(::std::exception_ptr)> ecb)
{
	if (!initiated_)
	{
		Media::OpenStreamException e;
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

	try {
		stream_->openRealStreamAsync(st, [=](Media::RealStreamRespParam param) { response(param); },
			[=](std::exception_ptr ex) { exception(callid, ex); });
	}
	catch (const Ice::Exception& e)
	{
		initiated_ = false;
		LOG(ERROR) << e.what();
		return ;
	}
	catch (const std::exception& e)
	{
		initiated_ = false;
		LOG(ERROR) << e.what();
		return ;
	}


}

void MediaClient::openRealStream(dt::OpenRealStream streamParam, std::function<void(const::Media::RealStreamRespParam&)> cb, std::function<void(::std::exception_ptr)> ecb)
{
	if (!initiated_)
	{
		Media::OpenStreamException e;
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

void MediaClient::openRealStream(dt::OpenRealStream streamParam)
{
	if (!initiated_)
	{
		Media::OpenStreamException e;
		e.reason = "not connected to media server!";
		streamParam.excb_(std::make_exception_ptr(e));
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
	cbs.respcb_ = streamParam.cb_;
	cbs.excb_ = streamParam.excb_;
	realcallbacks_.emplace(make_pair<string, callback>(string(stream.callid), std::move(cbs)));

	stream_->openRealStreamAsync(stream, [=](Media::RealStreamRespParam param) { response(param); },
			[=](std::exception_ptr ex) { exception(stream.callid, ex); });

}

void MediaClient::closeStream(std::string callid, string id)
{
	stream_->closeStreamAsync(callid, id);
}

void MediaClient::emplacecallback(std::function<void(const::Media::RealStreamRespParam&)> respcb, std::function<void(::std::exception_ptr)> excb)
{
	callback cb;
	cb.respcb_ = respcb;
	cb.excb_ = excb;
	realcallbacks_.emplace();
}
