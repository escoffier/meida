// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#ifndef HELLO_I_H
#define HELLO_I_H

#include <Operation.h>
#include "WorkQueue.h"

class CamaraOperation : public Datang::Operation
{
public:

	CamaraOperation(const WorkQueuePtr&);
	CamaraOperation();

	virtual void requsetCatalogAsync(::std::string id, ::std::function<void(const ::Datang::CatalogList&)> cb, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&);
	virtual void openRealStreamAsync(::Datang::RealStreamReqParam param, ::std::function<void(const ::Datang::RealStreamRespParam&)> cb, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) ;
	virtual void ptzControlAsync(std::string id, ::std::string, ::std::function<void()> cb, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&);
	virtual void getDeviceInfoAsync(int, ::std::function<void(const ::Datang::DeviceInfo&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&);
	virtual bool login(::std::string , ::std::string, const ::Ice::Current&);
	virtual void shutdown(const ::Ice::Current&);

private:

    WorkQueuePtr _workQueue;
};

class ConnCallback
{
public:
	virtual void heartbeat(const ::std::shared_ptr<::Ice::Connection>& con);

	virtual void closed(const ::std::shared_ptr<::Ice::Connection>& con);
};

#endif
