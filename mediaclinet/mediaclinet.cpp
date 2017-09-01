// mediaclinet.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Ice/Ice.h>
#include <IceGrid/IceGrid.h>
#include "stream.h"


class MeidaClient : public Ice::Application
{
public:

	virtual int run(int, char*[]);
};

int main(int argc, char *argv[])
{
	MeidaClient app;
	return app.main(argc, argv, "config.mediaclient");
}

int MeidaClient::run(int argc, char *argv[] )
{
	if (argc > 1)
	{
		std::cerr << appName() << ": too many arguments" << std::endl;
		return EXIT_FAILURE;
	}

	//
	// Create a proxy to the well-known object with the `pricing'
	// identity.
	//
	Media::StreamPrx stream = Media::StreamPrx::uncheckedCast(communicator()->stringToProxy("stream"));
	if (!stream)
	{
		std::cerr << argv[0] << ": couldn't find a `::Demo::PricingEngine' object." << std::endl;
		return EXIT_FAILURE;
	}

	//
	// If no context is set on the default locator (with the
	// Ice.Default.Locator.Context property, see the comments from the
	// `config.client' file in this directory), ask for the preferred
	// currency.
	//
	//Ice::Context ctx = communicator()->getDefaultLocator()->ice_getContext();
	//if (ctx["currency"].empty())
	//{
	//	cout << "enter your preferred currency (USD, EUR, GBP, INR, AUD, JPY): ";
	//	string currency;
	//	cin >> currency;

	//	//
	//	// Setup a locator proxy with a currency context.
	//	//
	//	Ice::LocatorPrx locator = communicator()->getDefaultLocator();
	//	ctx["currency"] = currency;
	//	pricing = pricing->ice_locator(locator->ice_context(ctx));
	//}
	//else
	//{
	//	cout << "Preferred currency configured for the client: " << ctx["currency"] << endl;
	//}

	//
	// Get the preferred currencies of the server
	//
	Media::Catalog ctg;
	Media::StreamInfo stminfo;
	stream->openRealStream(ctg, stminfo);
	//Ice::StringSeq currencies = pricing->getPreferredCurrencies();
	std::cout << "StreamInfo of the server: "<< stminfo.ip<<std::endl;
	//for (Ice::StringSeq::const_iterator p = currencies.begin(); p != currencies.end(); ++p)
	//{
	//	cout << *p;
	//	if (p + 1 != currencies.end())
	//	{
	//		cout << ", ";
	//	}
	//}
	//cout << endl;
	return EXIT_SUCCESS;
}
