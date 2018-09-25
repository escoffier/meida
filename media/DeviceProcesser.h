#pragma once
//#include "WorkorQueue.h"
//#include "AbstractOperation.h"
#include "Catalog.h"
//#include "ControlParam.h"
#include "utility.h"
#include <functional>
#include <memory>

class CamaraController
{
public:
	CamaraController()  /*queue_()*/ {};
	virtual ~CamaraController() {};

	virtual bool Login(std::shared_ptr<CCatalog> ctg) { return false; };
	//virtual void Login(std::shared_ptr<CCatalog> ctg, std::function<void(bool)> cb) {  };
	virtual bool isLogin() const { return false; } 
	virtual void ptzControl(std::shared_ptr<CCatalog> ctg, std::string cmd) {  };
	//virtual void getDeviceStatusAsync(std::shared_ptr<CCatalog> ctg, std::function<void(int)> cb) {  };
	virtual void getDeviceStatus(std::shared_ptr<CCatalog> ctg, dt::DeviceStatus &st) {};
	virtual bool openRealStream(const std::string& id_, const std::string& ip_, int port_, 
	                            const std::string& name_, const std::string& pwd_, 
						        std::function<void(char *, uint32_t)> cb) {};
								
	virtual bool closeRealStream(const std::string& id) {};
	virtual void setDataCallback(std::function<void(char *, uint32_t)> cb) {};
	//virtual void getDeviceStatus(QueryStatusReq req, dt::DeviceStatus &st)

protected:
	//ThreadsafeQueue queue_;

};

