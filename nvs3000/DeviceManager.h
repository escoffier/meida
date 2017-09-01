#pragma once
#include "SipDevice.h"
#include <map>
#include <memory>

class DeviceManager
{
public:
	static DeviceManager * GetInstance();

	void LoadDevice();
	bool UpdateDevice(const SIPDevice& device);
	bool UpdateDevice(const std::string& id, const std::string& ip, const std::string& port );
	std::string GetDeviceUrl(const std::string & id);
private:
	DeviceManager();
	~DeviceManager();

private:
	static DeviceManager * instance_;

	std::map<std::string, std::shared_ptr<SIPDevice>> devices_;
};


