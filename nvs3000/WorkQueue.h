// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#ifndef WORK_QUEUE_H
#define WORK_QUEUE_H

#include <Gateway.h>
#include <IceUtil/IceUtil.h>

#include <list>

struct CallbackEntry
{
	//Datang::AMD_Operation_sayHelloPtr cb;
	int delay;
};

struct RequestCatalogCB
{

};
class WorkQueue : public IceUtil::Thread
{
public:

    WorkQueue();

    virtual void run();

    //void add(const Datang::AMD_Operation_sayHelloPtr&, int);
	//void add(const Datang::AMD_Operation_getNamePtr&, int);
    void destroy();

private:

    struct CallbackEntry
    {
		//Datang::AMD_Operation_sayHelloPtr cb;
        int delay;
    };

    IceUtil::Monitor<IceUtil::Mutex> _monitor;
    std::list<CallbackEntry> _callbacks;
    bool _done;
};

typedef IceUtil::Handle<WorkQueue> WorkQueuePtr;

#endif
