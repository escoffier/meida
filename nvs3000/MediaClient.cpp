#include "mediaclient.h"
#include <Ice/Ice.h>

MediaClient::MediaClient()
{
	Ice::CommunicatorPtr communicator = Ice::initialize();
	Ice::PropertiesPtr props = communicator->getProperties();
	props->load("config.client");

}

MediaClient::~MediaClient()
{
}

bool MediaClient::init()
{
	Ice::CommunicatorPtr communicator = Ice::initialize();
	Ice::PropertiesPtr props = communicator->getProperties();
	props->load("config.client");

	stream_ = Ice::checkedCast<Media::StreamPrx>( communicator->propertyToProxy("Stream.Proxy"));
	if (!stream_)
	{
		//std::cerr << argv[0] << ": couldn't find a `::Demo::PricingEngine' object." << std::endl;
		return false;
	}

	initiated_ = true;
	return true;
}

void MediaClient::openRealStream(string id, string ip, int port, string name, string pwd, 
	                             string destip, int destport,int ssrc, 
	                             std::function<void(const::Datang::RealStreamRespParam&)> cb)
{
	//CallbackPtr cb = new Callback(ptr);

	Media::RealStreamReqParam st;
	st.id = id;
	string callid = "ip@port";
	
	realcbmaps.emplace(make_pair<string, std::function<void(const::Datang::RealStreamRespParam&)> >(std::move(callid), std::move(cb)) );
	stream_->openRealStreamAsync(st, std::bind(&MediaClient::response, this, std::placeholders::_1));
	//stream_->begin_openRealStream(st, Media::newCallback_Stream_openRealStream(cb, &Callback::response, &Callback::exception));
}
