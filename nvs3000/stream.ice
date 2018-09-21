
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
};
struct Catalog
{
    string id;
	string name;
	string sdk;
	//DEVICETYPE type = HAIKANG;
};

interface Stream
{
	["amd"] void openRealStream(Catalog ctg, out Stream stm)
	throws RequestCanceledException;
};

};
