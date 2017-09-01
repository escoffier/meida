#pragma once
#include <thread>
#include <stdexcept>
#include <string>
#include <atomic>

class Interrupted :public std::runtime_error
{
public:
	Interrupted(const std::string & s) : runtime_error(s)
	{};
	~Interrupted() {};

private:

};

class interrupt_flag
{
public:
	void set() { flag.store(true, std::memory_order_relaxed); };
	bool is_set() const { return flag.load(std::memory_order_relaxed); };
	std::atomic<bool> flag;

};

thread_local interrupt_flag this_thread_interrupt_flag;
class interruptible_thread
{
	std::thread internal_thread;
	interrupt_flag* flag;
public:
	void join() { internal_thread.join(); };
	~interruptible_thread()
	{
		if (internal_thread.joinable())
		{
			internal_thread.join();
		}
	}
	template<typename FunctionType>
	interruptible_thread(FunctionType f)
	{
		std::promise<interrupt_flag*> p;
		internal_thread = std::thread([f, &p] {
			p.set_value(&this_thread_interrupt_flag);
			std::cout << "this_thread_interrupt_flag: " << &this_thread_interrupt_flag << std::endl;

			try
			{
				f();
			}
			catch (const Interrupted& e)
			{
				std::cout << e.what()<<std::endl;
			}
			
		});
		flag = p.get_future().get();
	}
	void interrupt()
	{
		if (flag)
		{
			flag->set();
		}
	}
};

inline void interruption_point()
{
	if (this_thread_interrupt_flag.is_set())
	{
		throw Interrupted("Interrupted!");
	}
}