#include "ProcesserManager.h"
#include "DeviceProcesser.h"
#include <Gateway.h>
#include "ControlParam.h"
#include "Catalog.h"
#include "glog\logging.h"

ControllerManager* ControllerManager::instance_ = nullptr;

ControllerManager::ControllerManager():
	controllers_(), msgThread_(), mediaClient_(new MediaClient), plugins_(new SDKPlugins)
{
	mediaClient_->init();
}

ControllerManager * ControllerManager::getInstance()
{
	if (instance_ == nullptr)
	{
		instance_ =  new ControllerManager;
	}
	return instance_;
}

ControllerManager::~ControllerManager()
{
}

std::shared_ptr<CamaraController> ControllerManager::get(const std::string & name)
{
	std::map<std::string, std::shared_ptr<CamaraController> >::iterator it = controllers_.find(name);
	if (it != controllers_.end())
		return it->second;
	return std::shared_ptr<CamaraController>();
}

void ControllerManager::add(const std::string & name, std::shared_ptr<CamaraController> p)
{
	controllers_.emplace(std::make_pair(name, p));
}

void ControllerManager::openRealStream(const dt::OpenRealStream & params, std::function<void(const::Gateway::RealStreamRespParam&)> cb, std::function<void(::std::exception_ptr)> excb)
{
	//std::shared_ptr<CCatalog> ctg = CatalogManager::getInstance()->find(params.id);
	//if (!ctg)
	//{
	//	Gateway::OpenStreamException e;
	//	e.reason = "camara does not exist!";
	//	excb(std::make_exception_ptr(e));
	//	return;
	//}
	//int port = atoi(ctg->GetPort().c_str());
	//dt::OpenRealStream streamParam;
	//streamParam.id = params.id;
	//streamParam.ip = ctg->GetIp();
	//streamParam.port = port;
	//streamParam.name = ctg->GetName();
	//streamParam.pwd = ctg->GetPassword();
	//streamParam.destip = params.destip;
	//streamParam.destport = params.destport;
	//streamParam.ssrc = params.ssrc;

	mediaClient_->openRealStream(params, cb, excb);
	//mediaClient_->openRealStream(params.id, ctg->GetIp(), port,ctg->GetName(),ctg->GetPassword(), params.destip, params.destport, params.ssrc, cb, ecb);
}

void ControllerManager::closeStream(std::string callid, string id)
{
	mediaClient_->closeStream(callid, id);
}

typedef CamaraController* (*CREATE_PTR)();

void ControllerManager::ptzControl(const std::string & id, const string & cmd, std::function<void()> cb, std::function<void(::std::exception_ptr)> excb)
{
	std::shared_ptr<CCatalog> ctg = CatalogManager::getInstance()->find(id);
	if (!ctg)
	{
		Gateway::DeviceControlException ex;
		ex.reason = "camara doesn't exist";
		excb(make_exception_ptr(ex));
		return;
	}
	auto search = controllers_.find("hkdevice");
	std::shared_ptr<CamaraController> controller;

	if (search == controllers_.end())
	{
		controller = loadPlugin("hkdevice");
		if (!controller)
		{
			LOG(ERROR) << "load plugin failed";
			Gateway::DeviceControlException ex;
			ex.reason = "load plugin failed";
			excb(make_exception_ptr(ex));
			return;		
		}
	}
	else
	{
		controller = search->second;
	}

	msgThread_.submit([=]() {controller->ptzControl(ctg, cmd); });
	//服务端是异步调用，必须调用回调函数
	cb();
}

void ControllerManager::getDeviceStatusAsync(std::string id, ::std::function<void(const::Gateway::DeviceStatus&)> cb, ::std::function<void(::std::exception_ptr)> excb)
{
	std::shared_ptr<CCatalog> ctg = CatalogManager::getInstance()->find(id);
	if (!ctg)
	{
		Gateway::DeviceControlException ex;
		ex.reason = "camara doesn't exist";
		excb(make_exception_ptr(ex));
		return;
	}
	std::shared_ptr<CamaraController> controller = getController("hkdevice");
	if (!controller)
	{
		Gateway::DeviceControlException ex;
		ex.reason = "load plugin failed";
		excb(make_exception_ptr(ex));
		return;
	}

/*	controller->Login(ctg, [=](bool login) {
		Gateway::DeviceStatus status;
		status.id = ctg->GetID();
		if (login)
		{
			status.status = 0;
			
		}
		else
		{
			status.status = 1;
		}
		cb(status);
	})*/;

	msgThread_.submit([=]() { 
		dt::DeviceStatus st;
		controller->getDeviceStatus(ctg, st);
		Gateway::DeviceStatus s;
		s.id = id;
		s.status = st.status;
		cb(s);
	});
}

void ControllerManager::getDeviceStatusAsync(QueryStatusReq req, std::function<void(const QueryStatusResp&)> cb)
{
	std::shared_ptr<CCatalog> ctg = CatalogManager::getInstance()->find(req.id_);
	if (!ctg)
	{
		msgThread_.submit([=]() {
			QueryStatusResp resp;
			resp.id_ = req.id_;
			resp.sn_ = req.sn_;
			resp.manufacturer_ = "";
			resp.status_ = false;
			//其他参数
			cb(resp);
		});
		return;
	}

	std::shared_ptr<CamaraController> controller = getController(ctg->GetSdkName());
	if (!controller)
	{
		msgThread_.submit([=]() {
			QueryStatusResp resp;
			resp.id_ = req.id_;
			resp.sn_ = req.sn_;
			resp.manufacturer_ = ctg->GetManufacturer();
			resp.status_ = false;
			//其他参数
			cb(resp);
		});
		return;
	}

	msgThread_.submit([=]() {
		dt::DeviceStatus st;
		controller->getDeviceStatus(ctg, st);
		QueryStatusResp resp;
		resp.id_ = req.id_;
		resp.sn_ = req.sn_;
		resp.manufacturer_ = ctg->GetManufacturer();
		resp.status_ = !!st.status;
		//其他参数
		
		cb(resp);
	});
}

std::shared_ptr<CamaraController> ControllerManager::loadPlugin(const std::string& name)
{
	if (!plugins_->Load("./", name.c_str()))
	{
		LOG(ERROR) << "Load "<< name <<".dll failed!";
		return std::shared_ptr<CamaraController>();
	}

	CREATE_PTR func = (CREATE_PTR)plugins_->GetFuncAddr("GetController");
	if (func == nullptr)
	{
		LOG(ERROR) << "GetFuncAddr failed!";
		return std::shared_ptr<CamaraController>();
	}

	//std::shared_ptr<CamaraController> Controller(func());
	std::shared_ptr<CamaraController> controller = std::shared_ptr<CamaraController>(func());
	if (controller == nullptr)
	{
		LOG(ERROR) << "CamaraController is null!";
		return std::shared_ptr<CamaraController>();
	}

	

	controllers_.emplace(std::make_pair(name, controller));
	LOG(INFO) << "load plugin : "<< name<<".dll";
	//add("hik", controller);

	return controller;
}

std::shared_ptr<CamaraController> ControllerManager::getController(const std::string & name)
{
	auto search = controllers_.find(name);
	std::shared_ptr<CamaraController> controller;

	if (search == controllers_.end())
	{
		controller = loadPlugin("hkdevice");
		if (!controller)
		{
			LOG(ERROR) << "load plugin failed";
			//Gateway::DeviceControlException ex;
			//ex.reason = "load plugin failed";
			//excb(make_exception_ptr(ex));
			return std::shared_ptr<CamaraController>();;
		}
	}
	else
	{
		controller = search->second;
	}

	return controller;
}
