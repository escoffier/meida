// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "HelloI.h"
#include "ProcesserManager.h"
#include "DeviceProcesser.h"
#include "glog/logging.h"

using namespace std;

static std::string makeCallid(std::string id, std::string ip, int port)
{
	std::string callid(id);
	callid += "@";
	callid += ip;
	callid += ":";
	char strPort[64] = { 0 };
	sprintf(strPort, "%d", port);
	//std::itoa(port, strPort,10);
	callid += strPort ;
	callid += "-real";

	return callid;
}

CamaraControl::CamaraControl()
{
}

//void CamaraOperation::openRealStreamAsync(::Gateway::RealStreamReqParam param, ::std::function<void(const::Gateway::RealStreamRespParam&)> cb, ::std::function<void(::std::exception_ptr)> excb, const::Ice::Current &current)
//{
//	//
//	std::shared_ptr<Ice::IPConnectionInfo> conninfo = std::dynamic_pointer_cast<Ice::IPConnectionInfo>(current.con->getInfo());
//
//	LOG(INFO) <<"openRealStreamAsync remote: " << conninfo->remoteAddress << "-" << conninfo->remotePort;
//
//
//	std::shared_ptr<CCatalog> ctg = CatalogManager::getInstance()->find(param.id);
//	if (!ctg)
//	{
//		Gateway::OpenStreamException e;
//		e.reason = "camara does not exist!";
//		excb(std::make_exception_ptr(e));
//		return;
//	}
//	//int port = atoi(ctg->GetPort().c_str());
//	dt::OpenRealStream streamParam(param, ctg, cb, excb);
//	//streamParam.id = param.id;
//	//streamParam.ip = ctg->GetIp();
//	//streamParam.port = port;
//	//streamParam.name = ctg->GetName();
//	//streamParam.pwd = ctg->GetPassword();
//	//streamParam.destip = param.destip;
//	//streamParam.destport = param.destport;
//	//streamParam.ssrc = param.ssrc;
//	//streamParam.pt = param.pt;
//
//	if (param.callid.empty())
//	{
//		streamParam.callid = makeCallid(streamParam.id, streamParam.destip, streamParam.destport);
//	}
//	else
//	{
//		streamParam.callid = param.callid;
//	}
//	
//	current.con->setCloseCallback(
//		[=](const::std::shared_ptr<::Ice::Connection>& con) { closed(con, streamParam.callid, streamParam.id); });
//
//	ControllerManager::getInstance()->openRealStream(streamParam, cb, excb);
//}

void CamaraControl::ptzControlAsync(std::string id, ::std::string cmd, ::std::function<void()> cb,
	                                  ::std::function<void(::std::exception_ptr)> excb, const::Ice::Current &)
{
	std::shared_ptr<CCatalog> ctg = CatalogManager::getInstance()->find(id);
	if (!ctg)
	{
		Gateway::DeviceControlException e;
		e.reason = "camara does not exist!";
		excb(std::make_exception_ptr(e));
		return;
	}
	
	ControllerManager::getInstance()->ptzControl(id, cmd, cb, excb);
}

void CamaraControl::getDeviceInfoAsync(std::string id, ::std::function<void(const::Gateway::DeviceInfo&)>, ::std::function<void(::std::exception_ptr)>, const::Ice::Current &)
{
}

void CamaraControl::getDeviceStatusAsync(std::string id, ::std::function<void(const::Gateway::DeviceStatus&)> cb, ::std::function<void(::std::exception_ptr)> excb, const::Ice::Current &)
{
	ControllerManager::getInstance()->getDeviceStatusAsync(id, cb, excb);
}

void
CamaraControl::shutdown(const Ice::Current& curr)
{
    cout << "Shutting down..." << endl;

    curr.adapter->getCommunicator()->shutdown();
}

void CamaraControl::heartbeat(const::std::shared_ptr<::Ice::Connection>& con)
{
}

void CamaraControl::closed(const::std::shared_ptr<::Ice::Connection>& con, std::string callid, std::string id)
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

bool CamaraControl::login(std::string user,  std::string password, const::Ice::Current & current)
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

StreamI::StreamI()
{
}

void StreamI::openRealStreamAsync(::Media::RealStreamReqParam param, ::std::function<void(const::Media::RealStreamRespParam&)> cb,
	                                     ::std::function<void(::std::exception_ptr)> excb, const::Ice::Current &current)
{
	std::shared_ptr<Ice::IPConnectionInfo> conninfo = std::dynamic_pointer_cast<Ice::IPConnectionInfo>(current.con->getInfo());

	LOG(INFO) << "openRealStreamAsync remote: " << conninfo->remoteAddress << "-" << conninfo->remotePort;

	std::shared_ptr<CCatalog> ctg = CatalogManager::getInstance()->find(param.id);
	if (!ctg)
	{
		Media::OpenStreamException e;
		e.reason = "camara does not exist!";
		excb(std::make_exception_ptr(e));
		return;
	}
	dt::OpenRealStream streamParam(param, ctg, cb, excb);

	if (streamParam.callid.empty())
	{
		streamParam.callid = makeCallid(streamParam.id, streamParam.destip, streamParam.destport);
	}


	//current.con->setCloseCallback(
		//[=](const::std::shared_ptr<::Ice::Connection>& con) { closed(con, streamParam.callid, streamParam.id); });
	//std::function<void()>
	ControllerManager::getInstance()->openRealStream(streamParam);
}

void StreamI::closeStreamAsync(::std::string callid, std::string id, ::std::function<void()> cb, ::std::function<void(::std::exception_ptr)>, const::Ice::Current &)
{
	cb();
	ControllerManager::getInstance()->closeStream(callid, id);
}
