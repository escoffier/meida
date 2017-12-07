#pragma once
//#include <memory>
//
//class function_wrapper
//{
//public:
//	template<typename F>
//	function_wrapper(F&& f) :
//		impl(new impl_type<F>(std::move(f)))
//	{}
//	void operator()() { impl->call(); }
//	function_wrapper() = default;
//	function_wrapper(function_wrapper&& other) :
//		impl(std::move(other.impl))
//	{}
//	function_wrapper& operator=(function_wrapper&& other)
//	{
//		impl = std::move(other.impl);
//		return *this;
//	}
//	function_wrapper(const function_wrapper&) = delete;
//	//function_wrapper(function_wrapper&) = delete;
//	function_wrapper& operator=(const function_wrapper&) = delete;
//
//private:
//	struct impl_base {
//		virtual void call() = 0;
//		virtual ~impl_base() {}
//	};
//
//	template<typename F>
//	struct impl_type : impl_base
//	{
//		F f;
//		impl_type(F&& f_) : f(std::move(f_)) {}
//		void call() { f(); }
//	};
//
//	std::unique_ptr<impl_base> impl;
//};
namespace dt
{
	struct DeviceStatus
	{
		std::string id;
		int status;
	};

	struct OpenRealStream
	{
		std::string id;
		std::string callid;
		std::string destip;
		int destport;
		std::string ip;
		int port;
		std::string name;
		std::string pwd;
		int pt;
		int ssrc;
	};
};

