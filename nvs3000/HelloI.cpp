// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "HelloI.h"
#include "ProcesserManager.h"
#include "DeviceProcesser.h"

using namespace std;

CamaraOperation::CamaraOperation(const WorkQueuePtr& workQueue) :
    _workQueue(workQueue)
{
}

CamaraOperation::CamaraOperation()
{
}

void CamaraOperation::requsetCatalogAsync(::std::string id, ::std::function<void(const::Datang::CatalogList&)> cb, ::std::function<void(::std::exception_ptr)>, const::Ice::Current &)
{
}

void CamaraOperation::openRealStreamAsync(::Datang::RealStreamReqParam param, ::std::function<void(const::Datang::RealStreamRespParam&)> cb, ::std::function<void(::std::exception_ptr)>, const::Ice::Current &)
{
	ProcesserManager::getInstance()->openRealStream(param, cb);
}

void CamaraOperation::ptzControlAsync(std::string id, ::std::string cmd, ::std::function<void()> cb, ::std::function<void(::std::exception_ptr)>, const::Ice::Current &)
{
	DeviceProcesser* processer = ProcesserManager::getInstance()->get("");

	//processer->addPtzControl();
}

void CamaraOperation::getDeviceInfoAsync(int, ::std::function<void(const::Datang::DeviceInfo&)>, ::std::function<void(::std::exception_ptr)>, const::Ice::Current &)
{
}



//void HelloI::getDeviceInfo_async(const ::Datang::AMD_Operation_getDeviceInfoPtr& cb, int, const ::Ice::Current&)
//{
//	
//	cout << "get device infomation" << endl;
//	Datang::DeviceInfo info;
//	info.id = "1320000001230000000";
//	info.name = "camara1";
//	info.type = Datang::HAIKANG;
//	cb->ice_response(info);
//
//}
//
//void HelloI::requsetCatalog_async(const::Datang::AMD_Operation_requsetCatalogPtr &, const std::string &, const::Ice::Current &)
//{
//}
//
//void HelloI::openRealStream_async(const Datang::AMD_Operation_openRealStreamPtr &, const Datang::Catalog & ctg, const Ice::Current &)
//{
//	//ProcesserManager::getInstance()->get("hik")->addStreamOperation();
//}
//
//void HelloI::openRealStream_async(const::Datang::AMD_Operation_openRealStreamPtr &, const::Datang::RealStreamReqParam &, const::Ice::Current &)
//{
//}
//
//void HelloI::ptzControl_async(const Datang::AMD_Operation_ptzControlPtr &, const Datang::Catalog & ctg, const std::string & cmd, const Ice::Current &)
//{
//	DeviceProcesser* processer = ProcesserManager::getInstance()->get(ctg.sdk);
//	//processer->addPtzControl();
//}

void
CamaraOperation::shutdown(const Ice::Current& curr)
{
    cout << "Shutting down..." << endl;

    _workQueue->destroy();
    curr.adapter->getCommunicator()->shutdown();
}

bool CamaraOperation::login(std::string user,  std::string password, const::Ice::Current & current)
{
	//std::cout << "Receive connettion from: " << current.con->getEndpoint()->toString() << "\n";

	std::shared_ptr<Ice::IPConnectionInfo> conninfo = std::dynamic_pointer_cast<Ice::IPConnectionInfo>(current.con->getInfo());

	std::cout << "Receive connettion from: " << conninfo->remoteAddress << " : " << conninfo->remotePort << "\n";
	std::cout << user << " : " << password << "\n";

	ConnCallback *cb = new ConnCallback;
	auto closecb = std::bind(&ConnCallback::closed, cb, placeholders::_2);
	//current.con->setCloseCallback(closecb);
	
	auto hbcb = std::bind(&ConnCallback::heartbeat, placeholders::_2);
	//current.con->setHeartbeatCallback(hbcb);
	return true;
}

void ConnCallback::heartbeat(const ::std::shared_ptr<::Ice::Connection>& con)
{
	std::shared_ptr<Ice::IPConnectionInfo> conninfo = std::dynamic_pointer_cast<Ice::IPConnectionInfo>(con->getInfo());
	std::cout << "rev heart beat " << conninfo->remoteAddress<<" : "<<conninfo ->remotePort<< "\n";
}

void ConnCallback::closed(const ::std::shared_ptr<::Ice::Connection>& conn)
{
	try
	{
		std::shared_ptr<Ice::IPConnectionInfo> conninfo = std::dynamic_pointer_cast<Ice::IPConnectionInfo>(conn->getInfo());

		std::cout << "close :" << conn->getEndpoint()->toString() << "remote: " << conninfo->remoteAddress << "-" << conninfo->remotePort << "\n";
	}
	/*catch (const Ice::Exception& e) 
	{
		cerr << e << endl;
	}*/
	catch (const Ice::CloseConnectionException & e)
	{
		cerr << e << endl;
	}

}