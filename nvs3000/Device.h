#pragma once
#include <string>
#include <map>

class Device
{
public:
	Device() :needInitSdk(true) {}
	Device(const Device &other);
	Device & operator=(const Device &other);
	Device(Device &&other);
	Device & operator=( Device &&other);
	~Device();

public:
	virtual bool Login() ;
	std::string userId_;
	std::string userName_;
	std::string userIp_;
	std::string userPort_;
	std::string loginName_;
	std::string loginPassword_;
	bool needInitSdk;
};


class CatalogManager
{
	CatalogManager();
public:
	~CatalogManager();
	static CatalogManager * getInstance();

private:
	static CatalogManager *instance_;

	//std::map
};