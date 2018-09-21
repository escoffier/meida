// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

module Demo
{

exception RequestCanceledException
{
};

enum DEVICETYPE { HAIKANG, DAHUA, YUSHI };

struct DeviceInfo
{
    string id;
	string name;
	DEVICETYPE type = HAIKANG;
};

interface Hello
{
    ["amd"] idempotent void sayHello(int delay)
        throws RequestCanceledException;

    ["amd"] void getName(int id, out string name)
	    throws RequestCanceledException;

    ["amd"] void getDeviceInfo(int id, out DeviceInfo info)
	throws RequestCanceledException;

	bool login(string user, string password);
	//void register(string user, string password);

    void shutdown();
};


};
