#pragma once
//#include "DeviceProcesser.h"
#include "Device.h"
#include <memory>
class AbstractOperation
{
public:
	//AbstractOperation(std::shared_ptr<Device> device, std::shared_ptr<DeviceProcesser> processer):
	//	device_(device), processer_(processer)
	//{ }
	AbstractOperation(std::shared_ptr<Device> device):device_(device){};
	~AbstractOperation()
	{

	}
	virtual void Process() {};
protected:
	std::shared_ptr<Device> device_;
	//std::shared_ptr<DeviceProcesser> processer_;
};