#include "ThreadGuard.h"
#include <iostream>
ThreadGuard::ThreadGuard(std::thread && t) :
	t_(std::move(t) )
{

}

ThreadGuard::~ThreadGuard()
{
	std::cout << "dcot\n";
	if (t_.joinable())
	{
		std::cout << "joinable\n";
		t_.join();
	}
}
