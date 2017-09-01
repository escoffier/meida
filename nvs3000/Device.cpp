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
	// TODO: �ڴ˴����� return ���
	return *this;
}

Device::Device(Device && other)
{
}

Device & Device::operator=(Device && other)
{
	// TODO: �ڴ˴����� return ���
	return *this;
}

Device::~Device()
{
}

bool Device::Login()
{

#if 0
	//���ú���sdk��¼
	//LOG_TRACE(g_nLogID, "Enter");
	//BaseModel Model;
	//if (m_pHikDevice->GetModel(request.stDeviceID, Model))//��⵱ǰ�豸�Ƿ��Ѿ����ӳɹ�
	//{
	//	request.outputparam.pthis = m_pHikDevice->m_pRecvResponseThis;
	//	request.outputparam.nErrorID = G_ERROR_ALREADY_LOGIN;
	//	m_pHikDevice->m_pRecvResponse(request);
	//	LOG_WARN(g_nLogID, "���豸û�е�¼,SIPID:" << request.stDeviceID.a << request.stDeviceID.b);
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
		LOG(ERROR) << "ע���豸ʧ��:\r\n"
			<< "�豸IP:[" << this->userIp_ << "]\r\n"
			<< "�豸�˿�:[" << this->userPort_ << "]\r\n"
			<< "�û���:[" << this->userName_ << "]\r\n"
			<< "����:[" << this->userPassword_ << "]\r\n"
			<< "������: " << NET_DVR_GetLastError();
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
