#pragma once
#include <map>
#include "threadsafequeue.h"
#include <Operation.h>
#include "mediaclient.h"

class DeviceProcesser;
class RealStreamReqParam;

#include <functional>
#include "WorkorQueue.h"
#include <future>
#include <memory>

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
	MessageThread() :
		done(false),
		thread_(std::thread(&MessageThread::worker_thread, this))
	{
		//done = false;
		//std::thread(&MessageThread::worker_thread, this);
		//std::async(std::launch::async, &MessageThread::worker_thread, this);
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
				std::cout << "worker_thread run task" << std::endl;
				task();
			}
			else
			{
				//std::cout << "worker_thread yield" << std::endl;
				std::this_thread::yield();
			}
		}
	}

	template<typename FunctionType>
	std::future<typename std::result_of<FunctionType()>::type>
		submit(FunctionType f)
	{
		std::cout << "submit task" << std::endl;
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
	std::thread thread_;
};

class ProcesserManager
{

	ProcesserManager();
public:
	static ProcesserManager * getInstance();
	~ProcesserManager();

	DeviceProcesser* get(const std::string & name);
	void add(const std::string & name, DeviceProcesser* p);
	//for ICE call, ice请求使用异步调用
	void openRealStream(const Datang::RealStreamReqParam & params, std::function<void(const::Datang::RealStreamRespParam&)> cb);

	//for GB28181 call 
	void openRealStream(const RealStreamReqParam & params);

private:
	std::map<std::string, DeviceProcesser* > processers_;
	MessageThread msgThread_;
	std::unique_ptr<MediaClient> mediaClient_;
	static ProcesserManager* instance_;
};


