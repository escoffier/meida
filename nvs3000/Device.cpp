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

CCatalog::CCatalog() : m_config(true)
{
}

CCatalog::~CCatalog()
{
}

bool CCatalog::operator!=(const CCatalog &catalog) const
{
	return(m_id != catalog.m_id ||
		m_name != catalog.m_name ||
		m_manufacturer != catalog.m_manufacturer ||
		m_model != catalog.m_model ||
		m_owner != catalog.m_owner ||
		m_civil != catalog.m_civil ||
		m_block != catalog.m_block ||
		m_address != catalog.m_address ||
		m_safetyway != catalog.m_safetyway ||
		m_registerway != catalog.m_registerway ||
		m_certnum != catalog.m_certnum ||
		m_certifiable != catalog.m_certifiable ||
		m_errcode != catalog.m_errcode ||
		m_secrecy != catalog.m_secrecy ||
		m_parental != catalog.m_parental ||
		m_parentid != catalog.m_parentid ||
		m_endtime != catalog.m_endtime ||
		m_ip != catalog.m_ip ||
		m_port != catalog.m_port ||
		m_password != catalog.m_password ||
		m_status != catalog.m_status ||
		m_longitude != catalog.m_longitude ||
		m_latitude != catalog.m_latitude ||
		m_ptz != catalog.m_ptz ||
		m_position != catalog.m_position ||
		m_room != catalog.m_room ||
		m_use != catalog.m_use ||
		m_supplylight != catalog.m_supplylight ||
		m_direction != catalog.m_direction ||
		m_resolution != catalog.m_resolution ||
		m_businessgroup != catalog.m_businessgroup);
}

bool CCatalog::operator==(const CCatalog &catalog) const
{
	return(m_id == catalog.m_id &&
		m_name == catalog.m_name &&
		m_manufacturer == catalog.m_manufacturer &&
		m_model == catalog.m_model &&
		m_owner == catalog.m_owner &&
		m_civil == catalog.m_civil &&
		m_block == catalog.m_block &&
		m_address == catalog.m_address &&
		m_safetyway == catalog.m_safetyway &&
		m_registerway == catalog.m_registerway &&
		m_certnum == catalog.m_certnum &&
		m_certifiable == catalog.m_certifiable &&
		m_errcode == catalog.m_errcode &&
		m_secrecy == catalog.m_secrecy &&
		m_parental == catalog.m_parental &&
		m_parentid == catalog.m_parentid &&
		m_endtime == catalog.m_endtime &&
		m_ip == catalog.m_ip &&
		m_port == catalog.m_port &&
		m_password == catalog.m_password &&
		m_status == catalog.m_status &&
		m_longitude == catalog.m_longitude &&
		m_latitude == catalog.m_latitude &&
		m_ptz == catalog.m_ptz &&
		m_position == catalog.m_position &&
		m_room == catalog.m_room &&
		m_use == catalog.m_use &&
		m_supplylight == catalog.m_supplylight &&
		m_direction == catalog.m_direction &&
		m_resolution == catalog.m_resolution &&
		m_businessgroup == catalog.m_businessgroup);
}

const std::string& CCatalog::GetID() const
{
	return m_id;
}

void CCatalog::SetID(const std::string &id)
{
	m_id = id;
}

const std::string& CCatalog::GetChannel() const
{
	return m_channel;
}

void CCatalog::SetChannel(const std::string& channel)
{
	m_channel = channel;
}

const std::string& CCatalog::GetName() const
{
	return m_name;
}

void CCatalog::SetName(const std::string &name)
{
	m_name = name;
}

const std::string& CCatalog::GetManufacturer() const
{
	return m_manufacturer;
}

void CCatalog::SetManufacturer(const std::string &manufacturer)
{
	m_manufacturer = manufacturer;
}

const std::string& CCatalog::GetModel() const
{
	return m_model;
}

void CCatalog::SetModel(const std::string &model)
{
	m_model = model;
}

const std::string& CCatalog::GetOwner() const
{
	return m_owner;
}

void CCatalog::SetOwner(const std::string &owner)
{
	m_owner = owner;
}

const std::string& CCatalog::GetCivil() const
{
	return m_civil;
}

void CCatalog::SetCivil(const std::string &civil)
{
	m_civil = civil;
}

const std::string& CCatalog::GetBlock() const
{
	return m_block;
}

void CCatalog::SetBlock(const std::string &block)
{
	m_block = block;
}

const std::string& CCatalog::GetAddress() const
{
	return m_address;
}

void CCatalog::SetAddress(const std::string &address)
{
	m_address = address;
}

const std::string& CCatalog::GetSafetyway() const
{
	return m_safetyway;
}

void CCatalog::SetSafetyway(const std::string &safetyway)
{
	m_safetyway = safetyway;
}

const std::string& CCatalog::GetRegisterway() const
{
	return m_registerway;
}

void CCatalog::SetRegisterway(const std::string &registerway)
{
	m_registerway = registerway;
}

const std::string& CCatalog::GetCertnum() const
{
	return m_certnum;
}

void CCatalog::SetCertnum(const std::string &certnum)
{
	m_certnum = certnum;
}

const std::string& CCatalog::GetCertifiable() const
{
	return m_certifiable;
}

void CCatalog::SetCertifiable(const std::string &certifiable)
{
	m_certifiable = certifiable;
}

const std::string& CCatalog::GetErrcode() const
{
	return m_errcode;
}

void CCatalog::SetErrcode(const std::string &errcode)
{
	m_errcode = errcode;
}

const std::string& CCatalog::GetSecrecy() const
{
	return m_secrecy;
}

void CCatalog::SetSecrecy(const std::string &secrecy)
{
	m_secrecy = secrecy;
}

const std::string& CCatalog::GetParental() const
{
	return m_parental;
}

void CCatalog::SetParental(const std::string &parental)
{
	m_parental = parental;
}

const std::string& CCatalog::GetParentID() const
{
	return m_parentid;
}

void CCatalog::SetParentID(const std::string &parentid)
{
	m_parentid = parentid;
}

const std::string& CCatalog::GetEndtime() const
{
	return m_endtime;
}

void CCatalog::SetEndtime(const std::string &endtime)
{
	m_endtime = endtime;
}

const std::string& CCatalog::GetIp() const
{
	return m_ip;
}

void CCatalog::SetIp(const std::string &ip)
{
	m_ip = ip;
}

const std::string& CCatalog::GetPort() const
{
	return m_port;
}

void CCatalog::Setport(const std::string &port)
{
	m_port = port;
}

const std::string& CCatalog::GetPassword() const
{
	return m_password;
}

void CCatalog::SetPassword(const std::string &password)
{
	m_password = password;
}

const std::string& CCatalog::GetStatus() const
{
	return m_status;
}

void CCatalog::SetStatus(const std::string &status)
{
	m_status = status;
}

void CCatalog::SetOnStatus()
{
	m_status = "ON";
}

void CCatalog::SetOffStatus()
{
	m_status = "OFF";
}

void CCatalog::SetVlostStatus()
{
	m_status = "VLOST";
}

void CCatalog::SetDefectStatus()
{
	m_status = "DEFECT";
}

const std::string& CCatalog::GetLongitude() const
{
	return m_longitude;
}

void CCatalog::SetLongitude(const std::string &longitude)
{
	m_longitude = longitude;
}

const std::string& CCatalog::GetLatitude() const
{
	return m_latitude;
}

void CCatalog::SetLatitude(const std::string &latitude)
{
	m_latitude = latitude;
}

const std::string& CCatalog::GetPtz() const
{
	return m_ptz;
}

void CCatalog::SetPtz(const std::string &ptz)
{
	m_ptz = ptz;
}

const std::string& CCatalog::GetPosition() const
{
	return m_position;
}

void CCatalog::SetPosition(const std::string &position)
{
	m_position = position;
}

const std::string& CCatalog::GetRoom() const
{
	return m_room;
}

void CCatalog::SetRoom(const std::string &room)
{
	m_room = room;
}

const std::string& CCatalog::GetUse() const
{
	return m_use;
}

void CCatalog::SetUse(const std::string &use)
{
	m_use = use;
}

const std::string& CCatalog::GetSupplylight() const
{
	return m_supplylight;
}

void CCatalog::SetSupplylight(const std::string &supplylight)
{
	m_supplylight = supplylight;
}

const std::string& CCatalog::GetDirection() const
{
	return m_direction;
}

void CCatalog::SetDirection(const std::string &direction)
{
	m_direction = direction;
}

const std::string& CCatalog::GetResolution() const
{
	return m_resolution;
}

void CCatalog::SetResolution(const std::string &resolution)
{
	m_resolution = resolution;
}

const std::string& CCatalog::GetBusinessgroup() const
{
	return m_businessgroup;
}

void CCatalog::SetBusinessgroup(const std::string &businessgroup)
{
	m_businessgroup = businessgroup;
}

const std::string& CCatalog::GetPlatformID() const
{
	return m_platfromid;
}

void CCatalog::SetPlatformID(const std::string &platformid)
{
	m_platfromid = platformid;
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

void CatalogManager::insert(std::shared_ptr<CCatalog> ctg)
{
}

std::shared_ptr<CCatalog> CatalogManager::find(std::string id)
{
	return std::shared_ptr<CCatalog>();
}
