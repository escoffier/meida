#include "mediastream.h"
#include "zmd5.h"
#include <functional>
#include "HCNetSDK.h"

static void __stdcall RealDataCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void* pUser)
{
	// qDebug()<<tr(u8"receive data");
	//std::cout<<"receive data";
	if (pUser == nullptr)
	{
		return;
	}
	//Widget * w = (Widget *) pUser;
	//StreamPlayer *player = (StreamPlayer *)pUser;
	//w->hkstream_->write((const char *)pBuffer, dwBufSize);
	//player->getStreamBuf()->write((const char *)pBuffer, dwBufSize);
	// qDebug()<<"buf size: "<<w->hkstream_->buffer().size()<<" : " <<dwBufSize;
	// w->startPlay();

}

MediaStream::MediaStream(const std::string & id, const std::string & name, const std::string & pwd, 
	                     const std::string & ip, int port, const std::string & destIp, int destPort, 
	                     const Media::AMD_Stream_openRealStreamPtr & iceCB):
	id_(id),name_(name), pwd_(pwd),ip_(ip),port_(port),destIp_(destIp), 
	destPort_(destPort), iceCB_(iceCB), isOpen_(true), isLogin_(false)
{
}

MediaStream::MediaStream(const std::string & id)
{
}

void MediaStream::addDestHost(const std::string & destIp, int destPort)
{


}

std::string MediaStream::addsubStream(const std::string & destIp, int destPort)
{
	
	unsigned char buff[128] = { 0 };
	md5_state_t mdctx;
	md5_byte_t md_value[16];

	snprintf((char*)buff, 127, "%s%d", destIp.c_str(), destPort);
	md5_init(&mdctx);
	md5_append(&mdctx, (const unsigned char*)(buff), strlen((const char*)buff));
	md5_finish(&mdctx, md_value);

	char md5sum[33];
	int i;
	int h, l;
	for (i = 0; i<16; ++i)
	{
		h = md_value[i] & 0xf0;
		h >>= 4;
		l = md_value[i] & 0x0f;
		md5sum[i * 2] = (char)((h >= 0x0 && h <= 0x9) ? (h + 0x30) : (h + 0x57));
		md5sum[i * 2 + 1] = (char)((l >= 0x0 && l <= 0x9) ? (l + 0x30) : (l + 0x57));
	}
	md5sum[32] = '\0';

	std::string md5str(md5sum);
	auto search = subStreams_.find(md5str);
	if (search == subStreams_.end())
	{
		//subStreams_.emplace(std::pair<std::string, subStream>(md5str, ss));
		subStream ss(destIp, destPort);
		subStreams_.emplace(md5str, std::move(ss));
	}
	return md5str;
}

RealSteam::RealSteam(const std::string & id, const std::string & name, const std::string & pwd, const std::string & ip, int port, const std::string & destIp, int destPort, const Media::AMD_Stream_openRealStreamPtr & iceCB):
	MediaStream(id, name, pwd, ip, port, destIp, destPort, iceCB)
{
}

RealSteam::~RealSteam()
{
}

bool RealSteam::openStream()
{
	
	return false;
}

bool RealSteam::openStream(const std::string & callid)
{
	NET_DVR_USER_LOGIN_INFO struLoginInfo = { 0 };
	struLoginInfo.bUseAsynLogin = false;
	//    memcpy(struLoginInfo.sDeviceAddress, "192.168.254.106", NET_DVR_DEV_ADDRESS_MAX_LEN);
	//    memcpy(struLoginInfo.sUserName, "admin", NAME_LEN);
	//    memcpy(struLoginInfo.sPassword, "dtnvs3000", PASSWD_LEN);
	//    struLoginInfo.wPort = 8000;

	memcpy(struLoginInfo.sDeviceAddress, ip_.c_str(), NET_DVR_DEV_ADDRESS_MAX_LEN);
	memcpy(struLoginInfo.sUserName, name_.c_str(), NAME_LEN);
	memcpy(struLoginInfo.sPassword, pwd_.c_str(), PASSWD_LEN);
	struLoginInfo.wPort = port_;


	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = { 0 };

	//LONG lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
	long userID_ = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
	if (userID_ < 0)
	{
		//qDebug() << tr(u8"注册设备失败");
		return false;
	}
	else
	{

		//qDebug() << tr(u8"注册设备向成功");

	}

	HWND hWnd = NULL;
	//= GetConsoleWindow();
	NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
	struPlayInfo.hPlayWnd = hWnd;
	struPlayInfo.lChannel = 1;//request.ulChannelID;//iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
	struPlayInfo.dwLinkMode = 0;//Tcp
	struPlayInfo.dwStreamType = 0;//主码流
								  //	struPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;
	struPlayInfo.byPreviewMode = 0;//正常预览
	struPlayInfo.bBlocked = 1;//阻塞取流
	struPlayInfo.bPassbackRecord = 0;//不启用录像回传;
	struPlayInfo.byProtoType = 0;//私有协议
								 //LONG lPlayHandle = 0;
	//lPlayHandle = NET_DVR_RealPlay_V40( lUserID, &struPlayInfo, RealDataCallBack, (void *)w);
	long playHandle_ = NET_DVR_RealPlay_V40(userID_, &struPlayInfo, RealDataCallBack, (void *)this);
	return true;
}



void RealSteam::closeStream(const std::string & callid)
{
}

VodSteam::VodSteam(const std::string & id, const std::string & name, const std::string & pwd, const std::string & ip, int port, const std::string & destIp, int destPort, const Media::AMD_Stream_openRealStreamPtr & iceCB, const std::string & startTime, const std::string & endTime):
	MediaStream(id, name, pwd, ip, port, destIp, destPort, iceCB), startTime_(startTime), endTime_(endTime)
{
}

VodSteam::~VodSteam()
{
}

bool VodSteam::openStream()
{
	return false;
}

std::shared_ptr<MediaStream> StreamManager::getStream(const std::string & id)
{
	auto search  = streams_.find(id);
	if (search != streams_.end())
	{
		return search->second;
	}
	return nullptr;
}

void StreamManager::addStream(const std::string & id, const std::string & name, const std::string & pwd, 
	                          const std::string & ip, int port, const std::string & destIp, int destPort, 
	                          const Media::AMD_Stream_openRealStreamPtr & iceCB)
{
	//std::shared_ptr<MediaStream> stream = getStream(id);
	auto search = streams_.find(id);
	if (search == streams_.end())
	{
		std::shared_ptr<MediaStream> ms = std::make_shared<RealSteam>(id, name, pwd, ip, port, destIp, destPort, iceCB);
		//streams_.emplace(std::pair<std::string, std::shared_ptr<MediaStream>>(id, ms));
		std::string callid = ms->addsubStream(destIp, destPort);
		streams_.emplace(id, ms);
		auto f = std::bind( &StreamManager::openStream, this, std::cref(id),std::cref(callid) );
		msgthread_.submit(std::move(f));
		//queue_.Push(std::move(f));
	}
	else
	{
		//search->second->addDestHost(destIp, destPort);
		search->second->addsubStream(destIp, destPort);
	}

	
}

bool StreamManager::openStream(const std::string &id, const std::string & callid)
{
	auto search = streams_.find(id);
	search->second->openStream(callid);
	return false;
}
