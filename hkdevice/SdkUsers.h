#pragma once
#include <map>
#include<memory>
#include <atomic>
#include <functional>
#include <Windows.h>
#include "glog\logging.h"

class SdkUser
{
public:
	typedef std::function<void(/*std::shared_ptr<Device> device,*/std::string id, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize)> ProcFunc;
	SdkUser();
	~SdkUser();
	long GetUserId() const { return sdkUserId_; }
	long GetChannelId() const { return sdkChannelId_; }
	long GetPlayHandle() const { return sdkPlayHandle_; }
	ProcFunc DataProcFunc() { return dataProc_; }
	std::string GetDeviceId() { return deviceId_; }

	void SetUserId(long id)  { sdkUserId_ = id; }
	void SetChannelId(long id) { sdkChannelId_ = id; }
	void SetPlayHandle(long handle) { sdkPlayHandle_ = handle; }
	void SetDataProc(ProcFunc dataProc) { dataProc_ = dataProc; }
	void SetDeviceId(std::string id) { deviceId_ = id; }
	bool IsOnline() {
		return isOnline_;}
	bool IsPlaying() { return isPlaying_.load(); }

	void Online(bool online) { isOnline_ = online; }
	void Playing(bool playing) { isPlaying_ = playing; }
	void IncrePlayCount() {
		playCount_.fetch_add(1);
		LOG(INFO)<<"playCount_: "<<playCount_.load(); 
		isPlaying_.store( true);
	}
	void DecrePlayCount() 
	{ 
		int cunt = playCount_.fetch_sub(1);
		if (cunt == 0)
		{
			isPlaying_.store(false);
		}
		else if (cunt < 0)
		{
			playCount_.store(0);
			isPlaying_.store( false);
		}
	}

	bool operator==(const SdkUser &);
	bool operator!=(const SdkUser &);
private:
	long sdkUserId_;
	long sdkChannelId_;
	bool isOnline_;
	long sdkPlayHandle_;
	//bool isPlaying_;
	std::atomic_bool isPlaying_;
	std::atomic_int playCount_;
	std::string deviceId_;
	ProcFunc dataProc_;
	//std::map<std::string, CallInfo> callInfo_;
};

class SdkUserManager
{
public:
	static SdkUserManager* GetInstance();
	void Insert(std::string id, std::shared_ptr<SdkUser>);
	void Update(std::string id, std::shared_ptr<SdkUser>);
	std::shared_ptr<SdkUser> GetSdkUser(std::string id);
private:
	SdkUserManager();
	~SdkUserManager();
	SdkUserManager(const SdkUserManager &) = delete;
	SdkUserManager& operator=(const SdkUserManager &) = delete;
private:
	static SdkUserManager* instance_;
	std::map<std::string, std::shared_ptr<SdkUser>> users_;
};




