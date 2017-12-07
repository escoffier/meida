#pragma once
//#include "WorkorQueue.h"
//#include "AbstractOperation.h"
#include "Catalog.h"
//#include "ControlParam.h"
#include "utility.h"
#include <functional>

class CamaraController
{
public:
	CamaraController()  /*queue_()*/ {};
	virtual ~CamaraController() {};
	//using DataProcFunc = std::function<void(/*std::shared_ptr<Device> device,*/std::string id, unsigned long dwDataType, unsigned char *pBuffer, unsigned long dwBufSize)>;
	//using ResponseFunc = std::function<void(std::string, int)>;

	//virtual bool Login(std::shared_ptr<Device> device) { return false; };
	//virtual void run() {};
	//virtual void addOperation(std::shared_ptr<AbstractOperation> op) {};
	//virtual void addLogin(std::shared_ptr<Device> device) {};
	//virtual void addPtzControl(std::shared_ptr<Device> device, std::string ptzcmd, std::function<void(std::string, int )> func) {};
	//virtual void addStreamOperation(std::shared_ptr<Device> device, ResponseFunc response, DataProcFunc dataProc) {}
	//virtual void addStreamOperation(std::shared_ptr<Device> device ) {}


	virtual bool Login(std::shared_ptr<CCatalog> ctg) { return false; };
	//virtual void Login(std::shared_ptr<CCatalog> ctg, std::function<void(bool)> cb) {  };
	virtual bool isLogin() const { return false; } 
	virtual void ptzControl(std::shared_ptr<CCatalog> ctg, std::string cmd) {  };
	//virtual void getDeviceStatusAsync(std::shared_ptr<CCatalog> ctg, std::function<void(int)> cb) {  };
	virtual void getDeviceStatus(std::shared_ptr<CCatalog> ctg, dt::DeviceStatus &st) {};
	virtual bool openRealStream(const dt::OpenRealStream& param) {};
	virtual bool closeRealStream(const std::string& id) {};
	virtual void setDataCallback(std::function<void(char *, uint32_t)> cb) {};
	//virtual void getDeviceStatus(QueryStatusReq req, dt::DeviceStatus &st)

protected:
	//ThreadsafeQueue queue_;

};

