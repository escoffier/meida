#pragma once
#include <string>
#include <map>

class CallInfo
{
public:
	CallInfo();
	~CallInfo();

private:
	std::string peerIp_;
	std::string peerPort_;
};

//CallInfo::CallInfo()
//{
//}
//
//CallInfo::~CallInfo()
//{
//}

class CallInfos
{
public:
	CallInfos();
	~CallInfos();

	void Insert(std::string, std::string peerIp, std::string peerPort);
private:
	//std::string callId;

	std::multimap<std::string, CallInfo> callinfos_;
};