// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#ifndef HELLO_I_H
#define HELLO_I_H

#include <Operation.h>
#include "WorkQueue.h"

class HelloI : public Datang::Operation
{
public:

    HelloI(const WorkQueuePtr&);
	HelloI();
    virtual void sayHello_async(const Datang::AMD_Operation_sayHelloPtr&, int, const Ice::Current&);
	virtual void getName_async(const ::Datang::AMD_Operation_getNamePtr&, int, const ::Ice::Current& );
	virtual void getDeviceInfo_async(const ::Datang::AMD_Operation_getDeviceInfoPtr&, int, const ::Ice::Current&);
	virtual void requsetCatalog_async(const ::Datang::AMD_Operation_requsetCatalogPtr&, const std::string&, const ::Ice::Current&);
	void  openRealStream_async(const Datang::AMD_Operation_openRealStreamPtr &, const Datang::Catalog &, const Ice::Current &);
	void  ptzControl_async(const Datang::AMD_Operation_ptzControlPtr &, const Datang::Catalog &, const std::string &, const Ice::Current &);
    virtual void shutdown(const Ice::Current&);
	virtual bool login(const std::string& user, const std::string& password, const ::Ice::Current& );

private:

    WorkQueuePtr _workQueue;
};

class ConnCallback :public Ice::ConnectionCallback
{
	virtual void heartbeat(const ::Ice::ConnectionPtr&);

	virtual void closed(const ::Ice::ConnectionPtr&);
};

#endif
