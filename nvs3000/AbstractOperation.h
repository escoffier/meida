#pragma once
//#include "DeviceProcesser.h"
#include "Catalog.h"
#include <memory>
class AbstractOperation
{
public:
	//AbstractOperation(std::shared_ptr<Device> device, std::shared_ptr<DeviceProcesser> processer):
	//	device_(device), processer_(processer)
	//{ }
	AbstractOperation(std::shared_ptr<CCatalog> device):device_(device){};
	~AbstractOperation()
	{

	}
	virtual void Process() {};
protected:
	std::shared_ptr<CCatalog> device_;
	//std::shared_ptr<DeviceProcesser> processer_;
};