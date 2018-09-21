#pragma once
#include <string>

struct QueryStatusReq
{
	std::string id_;
	std::string sn_;
	std::string callid_;
};

struct QueryStatusResp
{
	std::string id_;
	std::string sn_;
	std::string callid_;
	bool result_;
	bool online_;
	std::string manufacturer_;
	bool status_;
	bool encode_;
	bool record_;
	std::string deviceTime_;
};