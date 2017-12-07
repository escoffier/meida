#pragma once
//#include <memory>
#include<string>
namespace dt
{
	struct DeviceStatus
	{
		std::string id;
		int status;
	};

	struct OpenRealStream
	{
		std::string id;
		std::string callid;
		std::string destip;
		int destport;
		std::string ip;
		int port;
		std::string name;
		std::string pwd;
		int pt;
		int ssrc;
	};
};

