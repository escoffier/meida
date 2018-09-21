// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#ifndef HELLO_I_H
#define HELLO_I_H

#include <Gateway.h>

//#include "WorkQueue.h"
class StreamI :public Media::Stream
{
public:
	StreamI();

	virtual void openRealStreamAsync(::Media::RealStreamReqParam param, ::std::function<void(const ::Media::RealStreamRespParam&)> cb, 
		                             ::std::function<void(::std::exception_ptr)> e, const ::Ice::Current&);
	virtual void closeStreamAsync(::std::string, std::string id, ::std::function<void()>, ::std::function<void(::std::exception_ptr)>, 
		                          const ::Ice::Current&);
	virtual void getRecordFiles(::std::string, ::std::string, const ::Ice::Current&) {}
	virtual void openVodStream(::Media::RealStreamReqParam, ::Media::RealStreamRespParam&, const ::Ice::Current&){}
	virtual void closeVodStream(::std::string, ::std::string, const ::Ice::Current&){}
	virtual void controlVodStream(::std::string, ::std::string, ::std::string, const ::Ice::Current&){}
	virtual void getStreamStatic(::std::string, ::Media::StreamStatic&, const ::Ice::Current&) {}

};

class CamaraControl : public Gateway::DeviceControl
{
public:
	CamaraControl();

	virtual void ptzControlAsync(std::string id, ::std::string, ::std::function<void()> cb, ::std::function<void(::std::exception_ptr)> excb, const ::Ice::Current&);
	virtual void getDeviceInfoAsync(std::string id, ::std::function<void(const ::Gateway::DeviceInfo&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&);
	virtual void getDeviceStatusAsync(std::string id, ::std::function<void(const ::Gateway::DeviceStatus&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&);
	virtual bool login(::std::string , ::std::string, const ::Ice::Current&);
	virtual void shutdown(const ::Ice::Current&);
	virtual void Timing(::std::string, const ::Ice::Current&) {}
	virtual void setGuard(::std::string, const ::Ice::Current&){}
	virtual void resetGuard(::std::string, const ::Ice::Current&){}
	virtual void subscribe(::std::string, const ::Ice::Current&){}
	virtual void reboot(::std::string, const ::Ice::Current&){}

	void heartbeat(const ::std::shared_ptr<::Ice::Connection>& con);
	void closed(const ::std::shared_ptr<::Ice::Connection>& con, std::string callid, std::string id);
};


#endif
