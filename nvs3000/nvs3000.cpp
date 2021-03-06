// nvs3000.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
#include <Ice/Ice.h>
#include "HelloI.h"
#include "WorkQueue.h"
#include "glog/logging.h"
//#include "HikDeviceProcesser.h"
//#include "LoginOperatoin.h"
//#include "CallInfo.h"
#include "OperationServer.h"
#include <future>
#include "ProcesserManager.h"
using namespace std;


typedef CamaraController* (*CREATE_PTR)();

class CLoadPlugins
{
private:
	void* plxhandle;
public:
	CLoadPlugins()
	{
		plxhandle = nullptr;
	}
	bool Load(const char* plxpath, const char* libname)
	{
		plxhandle = 0;
		// First we need to add ./ and end with .so.
		size_t len = strlen(libname);
		len += 6; // Add room for ./, .so, and null.
		char path[260] = { 0 };
		sprintf(path, "%s%s", plxpath, libname);
#ifdef WINDOWS
		strcat(path, ".dll");
		plxhandle = LoadLibraryA(path);
#else
		strcat(path, ".so");
		plxhandle = dlopen(path, RTLD_LAZY);
#endif
		return plxhandle == nullptr ? false : true;
	}
	bool UnLoad()
	{
		if (plxhandle)
		{
#ifdef WINDOWS
			return FreeLibrary((HINSTANCE)plxhandle);
#else
			return dlclose(plxhandle);
#endif
		}
		return true;
	}
	~CLoadPlugins()
	{
		if (plxhandle)
		{
#ifdef WINDOWS
			FreeLibrary((HINSTANCE)plxhandle);
#else
			dlclose(plxhandle);
#endif
		}
	}

	void* GetFuncAddr(char* funcName)
	{
		void* func = 0;
		if (plxhandle) {
#ifdef WINDOWS
			func = GetProcAddress((HINSTANCE)plxhandle, funcName);
#else
			func = dlsym(plxhandle, funcName);
#endif
		}
		return func;

	}
};

// void datareceive(std::string id, int dwDataType, ch
// {

// }
class AsyncServer : public Ice::Application
{
public:

	virtual int run(int, char*[]);
	virtual void interruptCallback(int);
};																																																																																																																																																																												

void printresponse(std::string id, int error)
{
	LOG(INFO) << id << " : " << error;
}
void dataProcess(std::string id, int dwDataType, char *pBuffer, int dwBufSize)
{
	//LOG(INFO) <<"dataProcess: "<< id <<" - "<< dwDataType << " - " << dwBufSize;
}


int main(int argc, char* argv[])
{
	google::InitGoogleLogging(argv[0]);
	FLAGS_log_dir = "./log";
	FLAGS_stderrthreshold = 0;
	int status = 0;
	//std::multimap<std::string, CallInfo> callinfos_;
	//std::shared_ptr<DeviceProcesser> processor = std::make_shared<HikDeviceProcesser>();
#if 0



	CLoadPlugins plugins;
	if (!plugins.Load("./", "hkdevice"))
	{
		LOG(ERROR) << "Load dll failed!";
		return 0;
	}

	CREATE_PTR func = (CREATE_PTR)plugins.GetFuncAddr("GetController");
	if (func == nullptr)
	{
		LOG(ERROR) << "GetFuncAddr failed!";
		return 0;
	}

	

	//CamaraController * Controller = func();
	std::shared_ptr<CamaraController> Controller(func);
	if (Controller == nullptr)
	{
		LOG(ERROR) << "processor is null!";
		return 0;
	}

	ControllerManager::getInstance()->add("hik", Controller);
#endif // 0



	//std::shared_ptr<DeviceProcesser> processor = std::make_shared<HKde>func();
	//std::thread processthread(&DeviceProcesser::run, processor);
	//auto process = std::async(std::launch::async, &DeviceProcesser::run, processor);

	std::shared_ptr<CCatalog> ctg = std::make_shared<CCatalog>();
	ctg->SetID("60000000001310001430");
	ctg->SetIp("192.168.21.236");
	ctg->Setport("8000");
	ctg->SetPassword("dtnvs3000");
	ctg->SetName("admin");
	CatalogManager::getInstance()->insert(ctg);

#if 0
	std::shared_ptr<Device> dev = std::make_shared<Device>();
	dev->userId_ = "15100000001310000001";
	dev->userIp_ = "192.168.254.106";
	dev->userPort_ = "8000";
	dev->userName_ = "admin";
	dev->loginName_ = "admin";
	dev->loginPassword_ = "dtnvs3000";

	std::shared_ptr<Device> dev1 = std::make_shared<Device>();
	dev1->userId_ = "15100000001310000001";
	dev1->userIp_ = "192.168.254.106";
	dev1->userPort_ = "8000";
	dev1->userName_ = "admin";
	dev1->loginName_ = "admin";
	dev1->loginPassword_ = "dtnvs3000";
#endif // 0



	//std::shared_ptr<AbstractOperation> op = std::make_shared<LoginOperatoin>(dev);
	//processor->addLogin(dev);
	//processor->addStreamOperation(dev, printresponse, std::bind(dataProcess, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

	//processor->addStreamOperation(dev1, printresponse, std::bind(dataProcess, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	//std::function<void(std::string, int)> response = printresponse;
	//processor->addPtzControl(dev, "A50F0108001F00DC", response);
	//processthread.join();
	//try
	//{

	//	Ice::CommunicatorPtr communicator = Ice::initialize(argc, argv);
	//	Ice::PropertiesPtr props = communicator->getProperties();
	//	props->load("config.server");
	//	//callbackOnInterrupt();

	//	Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapter("Hello");
	//	
	//	WorkQueuePtr _workQueue = new WorkQueue();
	//	Demo::HelloPtr hello = new HelloI(_workQueue);
	//	adapter->add(hello, communicator->stringToIdentity("hello"));

	//	
	//	_workQueue->start();
	//	adapter->activate();

	//	communicator->waitForShutdown();
	//	_workQueue->getThreadControl().join();

	//}
	//catch (const Ice::Exception& e) {
	//	cerr << e << endl;
	//	status = 1;
	//}
	//catch (const std::string& msg) {
	//	cerr << msg << endl;
	//	status = 1;
	//}
	//catch (const char* msg) {
	//	cerr << msg << endl;
	//	status = 1;
	//}
	//return status;

	AsyncServer app;
	return app.main(argc, argv, "config.server");
}

int AsyncServer::run(int argc, char*[])
{
	if (argc > 1)
	{
		cerr << appName() << ": too many arguments" << endl;
		return EXIT_FAILURE;
	}

	callbackOnInterrupt();

	try
	{
		Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("DeviceControl");

		adapter->add(std::make_shared<CamaraControl>(), Ice::stringToIdentity("DeviceControl"));

		adapter->add(std::make_shared<StreamI>(), Ice::stringToIdentity("Stream"));

		adapter->activate();

		communicator()->waitForShutdown();
	}
	catch (const Ice::Exception& e) {
		LOG(INFO) << e.what();
	}
	catch (const std::exception& e)
	{
		LOG(INFO) << e.what();
	}

	return EXIT_SUCCESS;
}

void
AsyncServer::interruptCallback(int)
{
	communicator()->shutdown();
}