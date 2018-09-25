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

	struct OpenRealStreamParam
	{
		std::string id;
		std::string callid;
		std::string destip;
		int destport;
		int pt;
		int ssrc;
	};
};

