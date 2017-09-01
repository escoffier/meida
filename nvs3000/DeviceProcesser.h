#pragma once
#include "WorkorQueue.h"
#include "AbstractOperation.h"
#include "Device.h"

class DeviceProcesser
{
public:
	DeviceProcesser() : queue_() {};
	~DeviceProcesser() {};
	using DataProcFunc = std::function<void(/*std::shared_ptr<Device> device,*/std::string id, unsigned long dwDataType, unsigned char *pBuffer, unsigned long dwBufSize)>;
	using ResponseFunc = std::function<void(std::string, int)>;

	virtual bool Login(std::shared_ptr<Device> device) { return false; };
	virtual void run() {};
	virtual void addOperation(std::shared_ptr<AbstractOperation> op) {};
	virtual void addLogin(std::shared_ptr<Device> device) {};
	virtual void addPtzControl(std::shared_ptr<Device> device, std::string ptzcmd, std::function<void(std::string, int )> func) {};
	//virtual void addStreamOperation(std::shared_ptr<Device> device, std::function<void(std::string, int)> response, std::function<void(/*std::shared_ptr<Device> device,*/std::string id, unsigned long dwDataType, unsigned char *pBuffer, unsigned long dwBufSize)> ) {};
	virtual void addStreamOperation(std::shared_ptr<Device> device, ResponseFunc response, DataProcFunc dataProc) {}
protected:
	WorkorQueue queue_;
};

