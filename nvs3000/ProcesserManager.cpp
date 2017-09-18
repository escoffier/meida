#include "ProcesserManager.h"
#include "DeviceProcesser.h"
#include <Operation.h>
#include "ControlParam.h"
#include "Device.h"
ProcesserManager* ProcesserManager::instance_ = nullptr;

ProcesserManager::ProcesserManager():
	processers_(), msgThread_(), mediaClient_(new MediaClient)
{
	mediaClient_->init();
}

ProcesserManager * ProcesserManager::getInstance()
{
	if (instance_ == nullptr)
	{
		return new ProcesserManager;
	}
	return instance_;
}

ProcesserManager::~ProcesserManager()
{
}

DeviceProcesser * ProcesserManager::get(const std::string & name)
{
	std::map<std::string, DeviceProcesser* >::iterator it = processers_.find(name);
	if (it != processers_.end())
		return it->second;
	return nullptr;
}

void ProcesserManager::add(const std::string & name, DeviceProcesser * p)
{
	processers_.emplace(std::make_pair(name, p));
}

void ProcesserManager::openRealStream(const Datang::RealStreamReqParam & params, std::function<void(const::Datang::RealStreamRespParam&)> cb)
{
	std::shared_ptr<CCatalog> ctg = CatalogManager::getInstance()->find(params.id);
	int port = atoi(ctg->GetPort().c_str());

	mediaClient_->openRealStream(params.id, ctg->GetIp(), port,ctg->GetName(),ctg->GetPassword(), params.destip, params.destport, params.ssrc, cb);



	//std::shared_ptr<CCatalog> ctg = CatalogManager::getInstance()->find(params.id);
	//
	//std::map<std::string, DeviceProcesser* >::iterator it = processers_.find("hik");
	//it->second->addStreamOperation(params);

}
