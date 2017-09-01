#pragma once
#include <thread>
class ThreadGuard
{
public:
	ThreadGuard(std::thread && t);
	~ThreadGuard();

private:
	std::thread t_;
};
