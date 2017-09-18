// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

module Datang
{

exception RequestCanceledException
{
};

enum DEVICETYPE { HAIKANG, DAHUA, YUSHI };

struct DeviceInfo
{
    string id;
	string name;
	string sdk;
	DEVICETYPE type = HAIKANG;
};


struct Catalog
{
    string id;
	string name;
	string sdk;
	DEVICETYPE type = HAIKANG;
};

struct RealStreamReqParam
{
    string id;
    string destip;
	int destport;
	int pt;
	int ssrc;
};

struct RealStreamRespParam
{
    string id;
	string sourceip;
	string sourceport;
};

sequence<Catalog> CatalogList;

interface Operation
{
    ["amd"] void requsetCatalog(string id, out CatalogList catalogs)
	throws RequestCanceledException;

	["amd"] void openRealStream(RealStreamReqParam req, out RealStreamRespParam resp)
	throws RequestCanceledException;

    ["amd"] void ptzControl(string id, string cmd)
	throws RequestCanceledException;

	["amd"] void getDeviceInfo(int id, out DeviceInfo info)
	throws RequestCanceledException;

	bool login(string user, string password);
	//void register(string user, string password);

    void shutdown();
};


};
