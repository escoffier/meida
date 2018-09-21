#pragma once
#include <map>
#include "threadsafequeue.h"
#include <Gateway.h>
#include "mediaclient.h"
#include "DeviceProcesser.h"
#include "Plugins.h"
#include "GBMessage.h"

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

class MessageThreadPool
{
public:
	MessageThreadPool() :
		done(false)
		//thread_(std::thread(&MessageThread::worker_thread, this))
	{
		unsigned int n = std::thread::hardware_concurrency();
		for (size_t i = 0; i < (n - 2); i++)
		{
			threads_.push_back( std::thread(&MessageThreadPool::worker_thread, this) );
		}
		//done = false;
		//std::thread(&MessageThread::worker_thread, this);
		//std::async(std::launch::async, &MessageThread::worker_thread, this);
	};
	~MessageThreadPool()
	{
		done = true;
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
			queue_.wait_and_pop(task);
			task();
			//if (queue_.try_pop(task))
			//{
			//	std::cout << "worker_thread run task" << std::endl;
			//	task();
			//}
			//else
			//{
			//	//std::cout << "worker_thread yield" << std::endl;
			//	std::this_thread::yield();
			//}
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
	std::vector<std::thread> threads_;
};

class ControllerManager
{

	ControllerManager();
public:
	static ControllerManager * getInstance();
	~ControllerManager();

	std::shared_ptr<CamaraController> get(const std::string & name);
	void add(const std::string & name, std::shared_ptr<CamaraController> p);
	//for ICE call, ice请求使用异步调用
	void openRealStream(const dt::OpenRealStream & params, std::function<void(const::Media::RealStreamRespParam&)> cb, std::function<void(::std::exception_ptr)> e);
	void openRealStream(const dt::OpenRealStream & params);
	void closeStream(std::string callid, string id);
	void ptzControl(const std::string &id, const string &cmd, std::function<void()> cb, std::function<void(::std::exception_ptr)> excb);

	/// \brief RPC获取camara状态  
	/// \param req 参数1说明  
	/// \param cb 参数2说明  
	/// \param excb 参数2说明  
	/// \return void  
	void getDeviceStatusAsync(std::string id, ::std::function<void(const ::Gateway::DeviceStatus&)> cb, ::std::function<void(::std::exception_ptr)> excb);

	//for GB28181 call 
	void openRealStream(const RealStreamReqParam & params);

	/// \brief 国标协议获取camara状态  
	/// \param req 参数1说明  
	/// \param cb 参数2说明  
	/// \return void  
	void getDeviceStatusAsync(QueryStatusReq req, std::function<void(const QueryStatusResp&)> cb);

private:
	std::shared_ptr<CamaraController> loadPlugin(const std::string& name);
	//
	std::shared_ptr<CamaraController> getController(const std::string& name);
	void logincb(bool login);
private:
	std::map<std::string, std::shared_ptr<CamaraController> > controllers_;
	MessageThreadPool msgThread_;
	std::unique_ptr<MediaClient> mediaClient_;
	std::unique_ptr<SDKPlugins> plugins_;
	static ControllerManager* instance_;
};


