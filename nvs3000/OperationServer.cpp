#include "OperationServer.h"
#include "HelloI.h"
#include "glog/logging.h"
#include "ProcesserManager.h"
int NvsServer::run(int argc, char *[])
{
	if (argc > 1)
	{
		std::cerr << appName() << ": too many arguments" << std::endl;
		return EXIT_FAILURE;
	}

	callbackOnInterrupt();
	try
	{
		Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("Operation");

		adapter->activate();

		communicator()->waitForShutdown();
	}
	catch (const Ice::Exception& e)
	{
		LOG(ERROR) << e.what();
		//	status = 1;
	}
	catch (const std::exception& e)
	{
		LOG(ERROR) << e.what();
		//	status = 1;
	}
	catch (const std::string& msg) {
		LOG(ERROR) << msg;
		//status = 1;
	}
	catch (const char* msg) {
		LOG(ERROR) << msg;
		//status = 1;
	}
	//_workQueue->getThreadControl().join();
	return EXIT_SUCCESS;
}

void NvsServer::interruptCallback(int)
{
	//_workQueue->destroy();
	communicator()->shutdown();
}
