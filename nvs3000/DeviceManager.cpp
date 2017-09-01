#include "DeviceManager.h"

DeviceManager * DeviceManager::instance_ = nullptr;

DeviceManager * DeviceManager::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new DeviceManager;
	}
	return instance_;
}

void DeviceManager::LoadDevice()
{
	std::shared_ptr<SIPDevice> device(new SIPDevice);
	device->userName_ = "15010000002000000211";
	device->userPassword_ = "12345678";
	devices_.insert( std::pair<std::string, std::shared_ptr<SIPDevice> >(device->userName_, device ));
}

bool DeviceManager::UpdateDevice(const SIPDevice & device)
{
	std::map<std::string, std::shared_ptr<SIPDevice>>::iterator  it = devices_.find(device.userName_);
	if (it != devices_.end())
	{
		it->second->userIp_ = device.userIp_;
		it->second->userPort_ = device.userPort_;
		return true;
	}
	return false;
}

bool DeviceManager::UpdateDevice(const std::string & id, const std::string & ip, const std::string& port)
{
	std::map<std::string, std::shared_ptr<SIPDevice>>::iterator  it = devices_.find(id);
	if (it != devices_.end())
	{
		it->second->userIp_ = ip;
		it->second->userPort_ = port;
		return true;
	}
	return false;
}

std::string DeviceManager::GetDeviceUrl(const std::string & id)
{
	std::string destUrl;
	std::map<std::string, std::shared_ptr<SIPDevice>>::iterator  it = devices_.find(id);
	if (it != devices_.end())
	{
		destUrl += "sip:";
		destUrl += id + "@";
		destUrl += it->second->userIp_ + ":";
		destUrl += it->second->userPort_;
	}

	return destUrl;
}



DeviceManager::DeviceManager()
{
}

DeviceManager::~DeviceManager()
{
}