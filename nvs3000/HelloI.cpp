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

HelloI::HelloI(const WorkQueuePtr& workQueue) :
    _workQueue(workQueue)
{
}

HelloI::HelloI()
{
}

void
HelloI::sayHello_async(const Datang::AMD_Operation_sayHelloPtr& cb, int delay, const Ice::Current&)
{
    if(delay == 0)
    {
        cout << "Hello World!" << endl;
        cb->ice_response();
    }
    else
    {
        _workQueue->add(cb, delay);
    }
}

void HelloI::getName_async(const ::Datang::AMD_Operation_getNamePtr& cb, int id, const ::Ice::Current&)
{
	cout << "Get Name!" << endl;
	cb->ice_response("da tang!!!!");
}

void HelloI::getDeviceInfo_async(const ::Datang::AMD_Operation_getDeviceInfoPtr& cb, int, const ::Ice::Current&)
{
	
	cout << "get device infomation" << endl;
	Datang::DeviceInfo info;
	info.id = "1320000001230000000";
	info.name = "camara1";
	info.type = Datang::HAIKANG;
	cb->ice_response(info);

}

void HelloI::requsetCatalog_async(const::Datang::AMD_Operation_requsetCatalogPtr &, const std::string &, const::Ice::Current &)
{
}

void HelloI::openRealStream_async(const Datang::AMD_Operation_openRealStreamPtr &, const Datang::Catalog & ctg, const Ice::Current &)
{
	ProcesserManager::getInstance()->get("hik")->addStreamOperation();
}

void HelloI::ptzControl_async(const Datang::AMD_Operation_ptzControlPtr &, const Datang::Catalog & ctg, const std::string & cmd, const Ice::Current &)
{
	DeviceProcesser* processer = ProcesserManager::getInstance()->get(ctg.sdk);
	//processer->addPtzControl();
}

void
HelloI::shutdown(const Ice::Current& curr)
{
    cout << "Shutting down..." << endl;

    _workQueue->destroy();
    curr.adapter->getCommunicator()->shutdown();
}

bool HelloI::login(const std::string & user, const std::string & password, const::Ice::Current & current)
{
	//std::cout << "Receive connettion from: " << current.con->getEndpoint()->toString() << "\n";

	Ice::IPConnectionInfoPtr conninfo = Ice::IPConnectionInfoPtr::dynamicCast(current.con->getInfo());

	std::cout << "Receive connettion from: " << conninfo->remoteAddress << " : " << conninfo->remotePort << "\n";
	std::cout << user << " : " << password << "\n";
	Ice::ConnectionCallbackPtr conn = new ConnCallback();
	current.con->setCallback(conn);
	return true;
}

void ConnCallback::heartbeat(const::Ice::ConnectionPtr & conn)
{
	Ice::IPConnectionInfoPtr conninfo = Ice::IPConnectionInfoPtr::dynamicCast(conn->getInfo());
	std::cout << "rev heart beat " << conninfo->remoteAddress<<" : "<<conninfo ->remotePort<< "\n";
}

void ConnCallback::closed(const::Ice::ConnectionPtr & conn)
{
	try
	{
		Ice::IPConnectionInfoPtr conninfo = Ice::IPConnectionInfoPtr::dynamicCast(conn->getInfo());

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