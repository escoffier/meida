
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
struct Catalog
{
    string id;
	string ip;
	int port;
	string name;
	string pwd;
	string sdk;
	//DEVICETYPE type = HAIKANG;
};

interface Stream
{
	["amd"] void openRealStream(Catalog ctg, out StreamInfo stm)
	throws RequestCanceledException;
};

};
