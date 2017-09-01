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
	virtual void addOperation(std::shared_ptr<AbstractOperation> op);
	virtual void addLogin(std::shared_ptr<Device> device);
	virtual void addPtzControl(std::shared_ptr<Device> device, std::string ptzcmd, std::function<void(std::string, int)> func);
	//virtual void addStreamOperation(std::shared_ptr<Device> device, std::function<void(std::string, int)> response, std::function<void(/*std::shared_ptr<Device> device,*/std::string id, unsigned long dwDataType, unsigned char *pBuffer, unsigned long dwBufSize)>);
	virtual void addStreamOperation(std::shared_ptr<Device> device, ResponseFunc response, DataProcFunc dataProc);
private:
	
private:
	//WorkorQueue queue_;
};


