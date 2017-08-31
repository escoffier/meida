// media.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Ice/Ice.h>
#include "streamI.h"
#include "glog\logging.h"

class MediaServer : public Ice::Application
{
public:
	MediaServer();
	~MediaServer();
	virtual int run(int, char*[]);
	virtual void interruptCallback(int);
private:

};

MediaServer::MediaServer()
{
}

MediaServer ::~MediaServer()
{
}
int MediaServer::run(int argc, char *[])
{
	if (argc > 1)
	{
		std::cerr << appName() << ": too many arguments" << std::endl;
		return EXIT_FAILURE;
	}

	Ice::PropertiesPtr properties = communicator()->getProperties();
	Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("Stream");
	Ice::Identity id = communicator()->stringToIdentity(properties->getProperty("Identity"));
	//Demo::PricingEnginePtr pricing = new PricingI(properties->getPropertyAsList("Currencies"));
	Media::StreamPtr stream = new StreamI;
	adapter->add(stream, id);
	adapter->activate();
	communicator()->waitForShutdown();
	return EXIT_SUCCESS;
}

void MediaServer::interruptCallback(int)
{
}

int main(int argc, char* argv[])
{
	google::InitGoogleLogging(argv[0]);
	FLAGS_log_dir = "./log";
	FLAGS_stderrthreshold = 0;

	MediaServer app;
	int status = app.main(argc, argv);
	return status;
    //return 0;
}

