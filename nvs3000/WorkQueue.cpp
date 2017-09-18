// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>
#include "WorkQueue.h"

using namespace std;

WorkQueue::WorkQueue() :
    _done(false)
{
}

void
WorkQueue::run()
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);

    while(!_done)
    {
        if(_callbacks.size() == 0)
        {
            _monitor.wait();
        }

        if(_callbacks.size() != 0)
        {
            //
            // Get next work item.
            //
            CallbackEntry entry = _callbacks.front();

            //
            // Wait for the amount of time indicated in delay to 
            // emulate a process that takes a significant period of
            // time to complete.
            //
            _monitor.timedWait(IceUtil::Time::milliSeconds(entry.delay));

            if(!_done)
            {
                //
                // Print greeting and send response.
                //
                _callbacks.pop_front();
                cout << "Belated Hello World!" << endl;
                //entry.cb->ice_response();
            }
        }
    }

    //
    // Throw exception for any outstanding requests.
    //
    list<CallbackEntry>::const_iterator p;
    for(p = _callbacks.begin(); p != _callbacks.end(); ++p)
    {
        //(*p).cb->ice_exception(Datang::RequestCanceledException());
    }
}
#if 0



void 
WorkQueue::add(const Datang::AMD_Operation_sayHelloPtr& cb, int delay)
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);

    if(!_done)
    {
        //
        // Add work item.
        //
        CallbackEntry entry;
        entry.cb = cb;
        entry.delay = delay;

        if(_callbacks.size() == 0)
        {
            _monitor.notify();
        }
        _callbacks.push_back(entry);
    }
    else
    {
        //
        // Destroyed, throw exception.
        //
        cb->ice_exception(Datang::RequestCanceledException());
    }
}

void WorkQueue::add(const Datang::AMD_Operation_getNamePtr& cb, int)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);

	//if (!_done)
	//{
	//	//
	//	// Add work item.
	//	//
	//	CallbackEntry entry;
	//	entry.cb = cb;
	//	entry.delay = delay;

	//	if (_callbacks.size() == 0)
	//	{
	//		_monitor.notify();
	//	}
	//	_callbacks.push_back(entry);
	//}
	//else
	//{
	//	//
	//	// Destroyed, throw exception.
	//	//
	//	cb->ice_exception(Demo::RequestCanceledException());
	//}
}

#endif // 0
void
WorkQueue::destroy()
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);

    //
    // Set done flag and notify.
    //
    _done = true;
    _monitor.notify();
}
