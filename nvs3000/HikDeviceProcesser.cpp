#include "HikDeviceProcesser.h"
#include <Windows.h>
#include <BaseTsd.h>
#include <WinNT.h>
#include "HCNetSDK.h"

#include "glog\logging.h"
//#include <thread>
HikDeviceProcesser::HikDeviceProcesser()
{
	LOG(INFO) << "costr HikDeviceProcesser";
	//std::thread th(&HikDeviceProcesser::run,this);
}

HikDeviceProcesser::~HikDeviceProcesser()
{
}

bool HikDeviceProcesser::Login(std::shared_ptr<Device> device)
{
#if 0



	//调用海康sdk登录
	//LOG_TRACE(g_nLogID, "Enter");
	//BaseModel Model;
	//if (m_pHikDevice->GetModel(request.stDeviceID, Model))//检测当前设备是否已经连接成功
	//{
	//	request.outputparam.pthis = m_pHikDevice->m_pRecvResponseThis;
	//	request.outputparam.nErrorID = G_ERROR_ALREADY_LOGIN;
	//	m_pHikDevice->m_pRecvResponse(request);
	//	LOG_WARN(g_nLogID, "该设备没有登录,SIPID:" << request.stDeviceID.a << request.stDeviceID.b);
	//	LOG_TRACE(g_nLogID, "Exit");
	//	return false;
	//}

	NET_DVR_USER_LOGIN_INFO struLoginInfo;
	struLoginInfo.bUseAsynLogin = false;
	memcpy(struLoginInfo.sDeviceAddress, device->userIp_.c_str(), NET_DVR_DEV_ADDRESS_MAX_LEN);
	memcpy(struLoginInfo.sUserName, device->userName_.c_str(), NAME_LEN);
	memcpy(struLoginInfo.sPassword, device->userPassword_.c_str(), PASSWD_LEN);
	struLoginInfo.wPort = atoi(device->userPort_.c_str());

	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40;

	LONG lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
	if (lUserID < 0)
	{
		LOG(ERROR) << "注册设备失败:\r\n"
			<< "设备IP:[" << device->userIp_ << "]\r\n"
			<< "设备端口:[" << device->userPort_ << "]\r\n"
			<< "用户名:[" << device->userName_ << "]\r\n"
			<< "密码:[" << device->userPassword_ << "]\r\n";
			//<< "SIPID:[" << request.stDeviceID.a << request.stDeviceID.b << "]";
		//m_pHikDevice->InsertModel(request.stDeviceID, sDeviceAddress, wPort, sUserName, sPassword, lUserID);
		//request.outputparam.pthis = m_pHikDevice->m_pRecvResponseThis;
		//request.outputparam.nErrorID = NET_DVR_GetLastError();
		//m_pHikDevice->m_pRecvResponse(request);
		return false;
	}
	NET_DVR_DEVICECFG_V40 devConfig;
	memset(&devConfig, 0, sizeof(LPNET_DVR_DEVICECFG_V40));
	DWORD  dwBytesReturned = 0;
	BOOL ret = NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_DEVICECFG_V40, 0, &devConfig, sizeof(devConfig), &dwBytesReturned);
	LOG(INFO) <<"device type : " <<devConfig.wDevType;
	//if (ret)
	//{
	//	m_pHikDevice->InsertModel(request.stDeviceID, sDeviceAddress, wPort, sUserName, sPassword, lUserID, devConfig);
	//}
	//else
	//{
	//	m_pHikDevice->InsertModel(request.stDeviceID, sDeviceAddress, wPort, sUserName, sPassword, lUserID);
	//}
	//LOG_TRACE(g_nLogID, "Exit");
#endif // 0
	return true;
}

void HikDeviceProcesser::run()
{
	while (true)
	{
		//std::cout << "Processing Message\n";
		LOG(INFO) << "HikDeviceProcesser";
		auto op = queue_.Pop();
		op->Process();
	}
}
