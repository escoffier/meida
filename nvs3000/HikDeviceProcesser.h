#pragma once

#include "DeviceProcesser.h"
class Device;
class HikDeviceProcesser : public DeviceProcesser
{
public:
	HikDeviceProcesser();
	~HikDeviceProcesser();
	virtual bool Login(std::shared_ptr<Device> device);
	virtual void run();
private:
	
private:
	//WorkorQueue queue_;
};


