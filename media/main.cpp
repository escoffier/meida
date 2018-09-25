// media.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <Ice/Ice.h>
#include "streamI.h"
#include "glog/logging.h"

class MediaServer : public Ice::Application
{
  public:
	MediaServer();
	~MediaServer();
	virtual int run(int, char *[]);
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

	try
	{

#ifdef STANDALONE
		Ice::Identity id = Ice::stringToIdentity("stream");
#else
		Ice::PropertiesPtr properties = communicator()->getProperties();
		LOG(INFO) << "Property is : " <<properties->getProperty("Identity") <<std::endl;
		Ice::Identity id = Ice::stringToIdentity(properties->getProperty("Identity"));
#endif // !STANDALONE

		Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("Stream");

		adapter->add(std::make_shared<StreamI>(), id);
		adapter->activate();
	}
	catch (const Ice::Exception &e)
	{
		//initiated_ = false;
		LOG(ERROR) << e.what();
		return EXIT_SUCCESS;
	}
	catch (const std::exception &e)
	{
		LOG(ERROR) << e.what();
		return EXIT_SUCCESS;
	}

	communicator()->waitForShutdown();
	return EXIT_SUCCESS;
}

void MediaServer::interruptCallback(int)
{
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	FLAGS_log_dir = "./log";
	FLAGS_stderrthreshold = 0;

	MediaServer app;
#ifdef STANDALONE
	int status = app.main(argc, argv, "config.mediaserver");
#else
	int status = app.main(argc, argv);
#endif // STANDALONE

	return status;
}
