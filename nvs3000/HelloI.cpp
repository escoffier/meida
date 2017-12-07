// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "HelloI.h"
#include "ProcesserManager.h"
#include "DeviceProcesser.h"
#include "glog\logging.h"

using namespace std;

//CamaraOperation::CamaraOperation(const WorkQueuePtr& workQueue) :
//    _workQueue(workQueue)
//{
//}
static std::string makeCallid(std::string id, std::string ip, int port)
{
	std::string callid(id);
	callid += "@";
	callid += ip;
	callid += ":";
	char strPort[64] = { 0 };
	itoa(port, strPort,10);
	callid += strPort ;
	callid += "-real";

	return callid;
}

CamaraOperation::CamaraOperation()
{
}

//void CamaraOperation::requsetCatalogAsync(::std::string id, ::std::function<void(const::Gateway::CatalogList&)> cb, ::std::function<void(::std::exception_ptr)> e, const::Ice::Current &)
//{
//}

void CamaraOperation::openRealStreamAsync(::Gateway::RealStreamReqParam param, ::std::function<void(const::Gateway::RealStreamRespParam&)> cb, ::std::function<void(::std::exception_ptr)> excb, const::Ice::Current &current)
{
	//
	std::shared_ptr<Ice::IPConnectionInfo> conninfo = std::dynamic_pointer_cast<Ice::IPConnectionInfo>(current.con->getInfo());

	LOG(INFO) <<"openRealStreamAsync remote: " << conninfo->remoteAddress << "-" << conninfo->remotePort;


	std::shared_ptr<CCatalog> ctg = CatalogManager::getInstance()->find(param.id);
	if (!ctg)
	{
		Gateway::OpenStreamException e;
		e.reason = "camara does not exist!";
		excb(std::make_exception_ptr(e));
		return;
	}
	int port = atoi(ctg->GetPort().c_str());
	dt::OpenRealStream streamParam;
	streamParam.id = param.id;
	streamParam.ip = ctg->GetIp();
	streamParam.port = port;
	streamParam.name = ctg->GetName();
	streamParam.pwd = ctg->GetPassword();
	streamParam.destip = param.destip;
	streamParam.destport = param.destport;
	streamParam.ssrc = param.ssrc;
	streamParam.pt = param.pt;

	if (param.callid.empty())
	{
		streamParam.callid = makeCallid(streamParam.id, streamParam.ip, streamParam.port);
	}
	else
	{
		streamParam.callid = param.callid;
	}
	
	current.con->setCloseCallback(
		[=](const::std::shared_ptr<::Ice::Connection>& con) { closed(con, streamParam.callid, streamParam.id); });

	ControllerManager::getInstance()->openRealStream(streamParam, cb, excb);
}

void CamaraOperation::closeStreamAsync(::std::string callid, string id, ::std::function<void()> cb, 
	                                   ::std::function<void(::std::exception_ptr)>, const::Ice::Current &)
{
	cb();
	ControllerManager::getInstance()->closeStream(callid, id);
}

void CamaraOperation::ptzControlAsync(std::string id, ::std::string cmd, ::std::function<void()> cb, 
	                                  ::std::function<void(::std::exception_ptr)> excb, const::Ice::Current &)
{
	ControllerManager::getInstance()->ptzControl(id, cmd, cb, excb);
}

void CamaraOperation::getDeviceInfoAsync(std::string id, ::std::function<void(const::Gateway::DeviceInfo&)>, ::std::function<void(::std::exception_ptr)>, const::Ice::Current &)
{
}

void CamaraOperation::getDeviceStatusAsync(std::string id, ::std::function<void(const::Gateway::DeviceStatus&)> cb, ::std::function<void(::std::exception_ptr)> excb, const::Ice::Current &)
{
	ControllerManager::getInstance()->getDeviceStatusAsync(id, cb, excb);
}



//void HelloI::getDeviceInfo_async(const ::Gateway::AMD_Operation_getDeviceInfoPtr& cb, int, const ::Ice::Current&)
//{
//	
//	cout << "get device infomation" << endl;
//	Gateway::DeviceInfo info;
//	info.id = "1320000001230000000";
//	info.name = "camara1";
//	info.type = Gateway::HAIKANG;
//	cb->ice_response(info);
//
//}
//
//void HelloI::requsetCatalog_async(const::Gateway::AMD_Operation_requsetCatalogPtr &, const std::string &, const::Ice::Current &)
//{
//}
//
//void HelloI::openRealStream_async(const Gateway::AMD_Operation_openRealStreamPtr &, const Gateway::Catalog & ctg, const Ice::Current &)
//{
//	//ProcesserManager::getInstance()->get("hik")->addStreamOperation();
//}
//
//void HelloI::openRealStream_async(const::Gateway::AMD_Operation_openRealStreamPtr &, const::Gateway::RealStreamReqParam &, const::Ice::Current &)
//{
//}
//
//void HelloI::ptzControl_async(const Gateway::AMD_Operation_ptzControlPtr &, const Gateway::Catalog & ctg, const std::string & cmd, const Ice::Current &)
//{
//	DeviceProcesser* processer = ProcesserManager::getInstance()->get(ctg.sdk);
//	//processer->addPtzControl();
//}

void
CamaraOperation::shutdown(const Ice::Current& curr)
{
    cout << "Shutting down..." << endl;

    //_workQueue->destroy();
    curr.adapter->getCommunicator()->shutdown();
}

void CamaraOperation::heartbeat(const::std::shared_ptr<::Ice::Connection>& con)
{
}

void CamaraOperation::closed(const::std::shared_ptr<::Ice::Connection>& con, std::string callid, std::string id)
{
	try
	{
		LOG(INFO) << "close :" << con->getEndpoint()->toString();

		//ControllerManager::getInstance()->closeStream(callid, id);
	}
	catch (const Ice::ConnectionLostException & e)
	{
		LOG(INFO) << e.what();
	}
}

bool CamaraOperation::login(std::string user,  std::string password, const::Ice::Current & current)
{
	//std::cout << "Receive connettion from: " << current.con->getEndpoint()->toString() << "\n";

	std::shared_ptr<Ice::IPConnectionInfo> conninfo = std::dynamic_pointer_cast<Ice::IPConnectionInfo>(current.con->getInfo());

	std::cout << "Receive connettion from: " << conninfo->remoteAddress << " : " << conninfo->remotePort << "\n";
	std::cout << user << " : " << password << "\n";



	//auto closecb = [=](const::std::shared_ptr<::Ice::Connection>& con) { closed(con, conninfo->remoteAddress, conninfo->remotePort); };
	//current.con->setCloseCallback(closecb);
	//
	//auto hbcb = std::bind(&ConnCallback::heartbeat, placeholders::_2);
	return true;
}

//void ConnCallback::heartbeat(const ::std::shared_ptr<::Ice::Connection>& con)
//{
//	std::shared_ptr<Ice::IPConnectionInfo> conninfo = std::dynamic_pointer_cast<Ice::IPConnectionInfo>(con->getInfo());
//	std::cout << "rev heart beat " << conninfo->remoteAddress<<" : "<<conninfo ->remotePort<< "\n";
//}
//
//void ConnCallback::closed(const ::std::shared_ptr<::Ice::Connection>& conn)
//{
//	try
//	{
//		std::shared_ptr<Ice::IPConnectionInfo> conninfo = std::dynamic_pointer_cast<Ice::IPConnectionInfo>(conn->getInfo());
//
//		std::cout << "close :" << conn->getEndpoint()->toString() << "remote: " << conninfo->remoteAddress << "-" << conninfo->remotePort << "\n";
//	}
//	/*catch (const Ice::Exception& e) 
//	{
//		cerr << e << endl;
//	}*/
//	catch (const Ice::CloseConnectionException & e)
//	{
//		cerr << e << endl;
//	}
//
//}