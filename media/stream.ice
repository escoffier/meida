
#pragma once

module Media
{

exception RequestCanceledException
{
};

struct RealStreamRespParam
{
    string id;
	string callid;
	string sourceip;
	string sourceport;
};
struct RealStreamReqParam
{
    string id;
	string callid;
	string ip;  //camara ip
	int port;    //camara control port number
	string name;  //camara login username
	string pwd;
	string destip;  // ip
	int destport;    //port number
	int ssrc;
	string sdk;
	//DEVICETYPE type = HAIKANG;
};

interface Stream
{
	["amd"] void openRealStream(RealStreamReqParam ctg, out RealStreamRespParam stm)
	throws RequestCanceledException;
};

};
