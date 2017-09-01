#include "ProcesserManager.h"
#include "DeviceProcesser.h"

ProcesserManager* ProcesserManager::instance_ = nullptr;

ProcesserManager::ProcesserManager()
{
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
