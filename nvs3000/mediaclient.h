#pragma once
#include "stream.h"
#include "Operation.h"
#include "utility.h"

using namespace std;

//class Callback : public IceUtil::Shared
//{
//public:
//	Callback(const Datang::AMD_Operation_openRealStreamPtr& ptr):
//		openRealStreamPtr_(ptr)
//	{}
//	void response(const Media::RealStreamRespParam& info)
//	{
//		Datang::RealStreamRespParam param;
//		param.sourceip = info.sourceip;
//		param.sourceport = info.sourceport;
//		openRealStreamPtr_->ice_response(param);
//	}
//
//	void exception(const Ice::Exception& ex)
//	{
//		cerr << "sayHello AMI call failed:\n" << ex << endl;
//	}
//	Datang::AMD_Operation_openRealStreamPtr openRealStreamPtr_;
//};
//typedef IceUtil::Handle<Callback> CallbackPtr;


class MediaClient
{
public:
	MediaClient();
	~MediaClient();

	bool init();
	void openRealStream(string id,
		                string ip,
						int port,
						string name,
						string pwd,
						string destip,
						int destport,
						int ssrc,
		                std::function<void(const::Datang::RealStreamRespParam&)> cb);

	template<typename FunctionType> void emplacecb(FunctionType f)
	{
		std::packaged_task<void()> task(std::move(f));
		//std::future<result_type> res(task.get_future());
		//cbmaps.push(std::move(task));
	}
	void response(Media::RealStreamRespParam resp)
	{
		Datang::RealStreamRespParam param;
		param.sourceip = resp.sourceip;
		param.sourceport = resp.sourceport;
		auto  search = realcbmaps.find(resp.callid);
		if (search != realcbmaps.end())
		{
			search->second(param);
		}
		
		//cb(param);
	}

	void exception(const Ice::Exception& ex)
	{
		cerr << "sayHello AMI call failed:\n" << ex << endl;
	}


private:
	std::shared_ptr< Media::StreamPrx> stream_;
	bool initiated_;
	//std::map<string, function_wrapper> cbmaps;
	//记录呼叫的异步回调函数<call id, callback>
	std::map<string, std::function<void(const::Datang::RealStreamRespParam&)> > realcbmaps;
};


