// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#ifndef HELLO_I_H
#define HELLO_I_H

#include <Gateway.h>
//#include "WorkQueue.h"

class CamaraOperation : public Gateway::DeviceControl
{
public:

	//CamaraOperation(const WorkQueuePtr&);

	CamaraOperation();

	//virtual void requsetCatalogAsync(::std::string id, ::std::function<void(const ::Gateway::CatalogList&)> cb, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&);
	virtual void openRealStreamAsync(::Gateway::RealStreamReqParam param, ::std::function<void(const ::Gateway::RealStreamRespParam&)> cb, ::std::function<void(::std::exception_ptr)> e, const ::Ice::Current&) ;
	virtual void closeStreamAsync(::std::string, std::string id, ::std::function<void()>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&);
	virtual void ptzControlAsync(std::string id, ::std::string, ::std::function<void()> cb, ::std::function<void(::std::exception_ptr)> excb, const ::Ice::Current&);
	virtual void getDeviceInfoAsync(std::string id, ::std::function<void(const ::Gateway::DeviceInfo&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&);
	virtual void getDeviceStatusAsync(std::string id, ::std::function<void(const ::Gateway::DeviceStatus&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&);
	virtual bool login(::std::string , ::std::string, const ::Ice::Current&);
	virtual void shutdown(const ::Ice::Current&);


	virtual void CallSipUserReqAsync(::std::string, int, ::std::string, int, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void beatHeartAsync(::std::string, ::std::function<void(const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void CalibrationTimeReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void HolderOperReqAsync(::std::string, ::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void RecordingOperReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void StopRecordingOperReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void StartVoideRecoingFileAsync(::std::string, int, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void RecordingFileReqAsync(::std::string, ::std::string, ::std::string, int, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void LoadRecordingFileAsync(::std::string, ::std::string, ::std::string, int, ::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void FindRecordingFileReqAsync(::std::string, ::std::string, ::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void DataPlayStopOrStartReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void SetupAlarmReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void CloseAlarmReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void RestorConfigReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void RebootReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void RemoteControlReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void MsgStartVioceReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void MsgStopVioceReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void MsgQueryDeviceIpcStatusReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void MsgQueryDeviceIpcInfoReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void MsgStartPropertyServerReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void MsgStopPropertyServerReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void DeviceRefreshReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void DeviceShareNotifyAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};
	virtual void GatewayRerootReqAsync(::std::string, ::std::function<void(int, const ::std::string&)>, ::std::function<void(::std::exception_ptr)>, const ::Ice::Current&) {};

	void heartbeat(const ::std::shared_ptr<::Ice::Connection>& con);
	void closed(const ::std::shared_ptr<::Ice::Connection>& con, std::string callid, std::string id);

private:

   // WorkQueuePtr _workQueue;
};

//class ConnCallback
//{
//public:
//	virtual void heartbeat(const ::std::shared_ptr<::Ice::Connection>& con);
//
//	virtual void closed(const ::std::shared_ptr<::Ice::Connection>& con);
//};

#endif
