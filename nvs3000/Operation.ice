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
struct Stream
{
    string ip;
	string port;
	int pt;
};

sequence<Catalog> CatalogList;

interface Operation
{
    ["amd"] idempotent void sayHello(int delay)
        throws RequestCanceledException;

    ["amd"] void getName(int id, out string name)
	    throws RequestCanceledException;

    ["amd"] void requsetCatalog(string id, out CatalogList catalogs)
	throws RequestCanceledException;

	["amd"] void openRealStream(Catalog ctg, out Stream stm)
	throws RequestCanceledException;

    ["amd"] void ptzControl(Catalog ctg, string cmd)
	throws RequestCanceledException;

	["amd"] void getDeviceInfo(int id, out DeviceInfo info)
	throws RequestCanceledException;

	bool login(string user, string password);
	//void register(string user, string password);

    void shutdown();
};


};
