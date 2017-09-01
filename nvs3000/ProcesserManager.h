#pragma once
#include <map>

class DeviceProcesser;

class ProcesserManager
{

	ProcesserManager();
public:
	static ProcesserManager * getInstance();
	~ProcesserManager();

	DeviceProcesser* get(const std::string & name);
	void add(const std::string & name, DeviceProcesser* p);

private:
	std::map<std::string, DeviceProcesser* > processers_;

	static ProcesserManager* instance_;
};


