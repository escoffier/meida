
#pragma once

module Media
{

exception RequestCanceledException
{
};

struct StreamInfo
{
    string ip;
	string port;
	int pt;
	string callid;
};
struct RealStream
{
    string id;
	string ip;
	int port;
	string name;
	string pwd;
	string destip;
	int destport;
	string sdk;
	//DEVICETYPE type = HAIKANG;
};

interface Stream
{
	["amd"] void openRealStream(RealStream ctg, out StreamInfo stm)
	throws RequestCanceledException;
};

};
