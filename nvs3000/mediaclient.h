#pragma once
//#include "stream.h"
#include "Gateway.h"
#include "utility.h"
#include"glog/logging.h"
using namespace std;

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
		                std::function<void(const::Media::RealStreamRespParam&)> cb,
		                std::function<void(::std::exception_ptr)> ecb);

	void openRealStream(
		dt::OpenRealStream param,
		std::function<void(const::Media::RealStreamRespParam&)> cb,
		std::function<void(::std::exception_ptr)> ecb);

	void openRealStream(dt::OpenRealStream param);
	 
	void closeStream(std::string callid, string id);

	template<typename FunctionType> void emplacecb(FunctionType f)
	{
		std::packaged_task<void()> task(std::move(f));
	}
	
	void response(Media::RealStreamRespParam resp)
	{
		LOG(INFO) << "Open stream: " << resp.id <<"-----"<< resp.callid << "successfully from media";
		Media::RealStreamRespParam param;
		param.id = resp.id;
		param.callid = resp.callid;
		param.sourceip = resp.sourceip;
		param.sourceport = resp.sourceport;
		auto  search = realcallbacks_.find(resp.callid);
		if (search != realcallbacks_.end())
		{
			search->second.respcb_(param);
		}
	}

	void emplacecallback(std::function<void(const::Media::RealStreamRespParam&)>  respcb, std::function<void(::std::exception_ptr)> excb);
	void exception(string callid,std::exception_ptr ex)
	{
		auto  search = realcallbacks_.find(callid);
		if (search != realcallbacks_.end())
		{
			try
			{
				rethrow_exception(ex);
			}
			catch (const Media::OpenStreamException & me)
			{
				Media::OpenStreamException dte;
				dte.reason = me.reason;
				search->second.excb_(make_exception_ptr(dte));
			}
	
		}
		//cerr << "sayHello AMI call failed:\n" << ex << endl;
	}

	struct callback
	{
		std::function<void(const::Media::RealStreamRespParam&)>  respcb_;
		std::function<void(::std::exception_ptr)> excb_;
    };
private:
	bool initiated_;
	std::shared_ptr< Media::StreamPrx> stream_;
	
	//std::map<string, function_wrapper> cbmaps;
	//��¼��е��첽�ص�����<call id, callback>
	std::map<string, std::function<void(const::Media::RealStreamRespParam&)> > realcbmaps;

	std::map<string, callback > realcallbacks_;
};


