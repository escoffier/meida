#include "Device.h"
#include <Windows.h>
#include <BaseTsd.h>
#include <WinNT.h>
#include "HCNetSDK.h"
#include "glog\logging.h"

Device::Device(const Device & other)
{
}

Device & Device::operator=(const Device & other)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

Device::Device(Device && other)
{
}

Device & Device::operator=(Device && other)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

Device::~Device()
{
}

bool Device::Login()
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
	if (needInitSdk)
	{
		LOG(INFO) << "Initialize Hik SDK";
		NET_DVR_Init();
		needInitSdk = false;
	}
	NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
	struLoginInfo.bUseAsynLogin = false;
	memcpy(struLoginInfo.sDeviceAddress, this->userIp_.c_str(), NET_DVR_DEV_ADDRESS_MAX_LEN);
	memcpy(struLoginInfo.sUserName, this->userName_.c_str(), NAME_LEN);
	memcpy(struLoginInfo.sPassword, this->userPassword_.c_str(), PASSWD_LEN);
	struLoginInfo.wPort = atoi(this->userPort_.c_str());

	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};

	LONG lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
	if (lUserID < 0)
	{
		LOG(ERROR) << "注册设备失败:\r\n"
			<< "设备IP:[" << this->userIp_ << "]\r\n"
			<< "设备端口:[" << this->userPort_ << "]\r\n"
			<< "用户名:[" << this->userName_ << "]\r\n"
			<< "密码:[" << this->userPassword_ << "]\r\n"
			<< "错误码: " << NET_DVR_GetLastError();
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
	LOG(INFO) << "device type : " << devConfig.byDevTypeName;
	//if (ret)
	//{
	//	m_pHikDevice->InsertModel(request.stDeviceID, sDeviceAddress, wPort, sUserName, sPassword, lUserID, devConfig);
	//}
	//else
	//{
	//	m_pHikDevice->InsertModel(request.stDeviceID, sDeviceAddress, wPort, sUserName, sPassword, lUserID);
	//}
#endif // 0
	return true;
}

CatalogManager* CatalogManager::instance_ = nullptr;

CatalogManager::CatalogManager()
{

}

CatalogManager::~CatalogManager()
{
}

CatalogManager * CatalogManager::getInstance()
{
	if (instance_ == nullptr)
	{
		return new CatalogManager;
	}
	return instance_;
}
