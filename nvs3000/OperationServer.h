#pragma once
#include <Ice/Ice.h>

class NvsServer : public Ice::Application
{
public:
	virtual int run(int, char*[]);
	virtual void interruptCallback(int);
};
