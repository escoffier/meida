#pragma once
#include <functional>
#include "WorkorQueue.h"
#include <future>

class function_wrapper
{
public:
	template<typename F>
	function_wrapper(F&& f) :
		impl(new impl_type<F>(std::move(f)))
	{}
	void operator()() { impl->call(); }
	function_wrapper() = default;
	function_wrapper(function_wrapper&& other) :
		impl(std::move(other.impl))
	{}
	function_wrapper& operator=(function_wrapper&& other)
	{
		impl = std::move(other.impl);
		return *this;
	}
	function_wrapper(const function_wrapper&) = delete;
	//function_wrapper(function_wrapper&) = delete;
	function_wrapper& operator=(const function_wrapper&) = delete;

private:
	struct impl_base {
		virtual void call() = 0;
		virtual ~impl_base() {}
	};

	template<typename F>
	struct impl_type : impl_base
	{
		F f;
		impl_type(F&& f_) : f(std::move(f_)) {}
		void call() { f(); }
	};

	std::unique_ptr<impl_base> impl;
};

class MessageThread
{
public:
	MessageThread()
	{
		std::thread(&MessageThread::worker_thread, this);
	};
	~MessageThread()
	{

	}

	//void start()
	//{
	//	std::thread(&MessageThread::worker_thread, this);
	//}
	void worker_thread()
	{
		while (!done)
		{
			function_wrapper task;
			if (queue_.try_pop(task))
			{
				task();
			}
			else
			{
				std::this_thread::yield();
			}
		}
	}

	template<typename FunctionType>
	std::future<typename std::result_of<FunctionType()>::type>
		submit(FunctionType f)
	{
		typedef typename std::result_of<FunctionType()>::type
			result_type;
		std::packaged_task<result_type()> task(std::move(f));
		std::future<result_type> res(task.get_future());
		queue_.push(std::move(task));
		return res;
	}
private:
	//WorkorQueue<function_wrapper> queue_;
	threadsafe_queue<function_wrapper> queue_;
	std::atomic_bool done;
};