
#pragma once

module Media
{

exception OpenStreamException
{
	string callid;
	string reason;
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
	//string ip;  //camara ip
	//int port;    //camara control port number
	//string name;  //camara login username
	//string pwd;
	string destip;  // ip
	int destport;    //port number
	int ssrc;
	int pt;
	//string sdk;
	//DEVICETYPE type = HAIKANG;
};

struct StreamStatic
{
    int busynode;
	int freenode;
};

interface Stream
{
	["amd"] bool openRealStream(RealStreamReqParam ctg, out RealStreamRespParam stm);
	["amd"] void closeStream(string id, string callid);
	 void getStreamStatic(string id, out StreamStatic statics);
	 void getRecordFiles(string start, string end, out string files);
	 void openVodStream(RealStreamReqParam ctg, out RealStreamRespParam stm);
	void closeVodStream(string id, string callid);
	 void controlVodStream(string id, string callid, string cmd);
};

};
