// client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <Ice/Ice.h>
#include "Hello.h"
#include <thread>
#include <cstdlib>

using namespace std;
using namespace Demo;

class ConnCallback :public Ice::ConnectionCallback
{
	virtual void heartbeat(const ::Ice::ConnectionPtr&);

	virtual void closed(const ::Ice::ConnectionPtr&);
};


class Callback : public IceUtil::Shared
{
public:

	void response()
	{
	}

	void exception(const Ice::Exception& ex)
	{
		cerr << "sayHello AMI call failed:\n" << ex << endl;
	}
};
typedef IceUtil::Handle<Callback> CallbackPtr;


class GetNameCallback : public IceUtil::Shared
{
public:

	void response(const string & str)
	{
		cout << str << std::endl;
	}

	void exception(const Ice::Exception& ex)
	{
		cerr << "sayHello AMI call failed:\n" << ex << endl;
	}
};
typedef IceUtil::Handle<GetNameCallback> GetNameCallbackPtr;


class GetDeviceInfollback : public IceUtil::Shared
{
public:

	void response(const Demo::DeviceInfo & info)
	{
		cout << info.id << std::endl;
		cout << info.name << std::endl;
		cout << info.type << std::endl;
	}

	void exception(const Ice::Exception& ex)
	{
		cerr << "GetDeviceInfo AMI call failed:\n" << ex << endl;
	}
};
typedef IceUtil::Handle<GetDeviceInfollback> GetDeviceInfoCallbackPtr;


class AsyncClient : public Ice::Application
{
public:

	AsyncClient();

	virtual int run(int, char*[]);

private:

	void exception(const Ice::Exception&);
	void menu();
};

AsyncClient::AsyncClient() :
	//
	// Since this is an interactive demo we don't want any signal
	// handling.
	//
	Ice::Application(Ice::NoSignalHandling)
{
}

int
main(int argc, char* argv[])
{
	AsyncClient app;
	return app.main(argc, argv, "config.client");
}

int
AsyncClient::run(int argc, char* argv[])
{
	if (argc > 1)
	{
		cerr << appName() << ": too many arguments" << endl;
		return EXIT_FAILURE;
	}

	HelloPrx hello = HelloPrx::checkedCast(communicator()->propertyToProxy("Hello.Proxy"));
	if (!hello)
	{
		cerr << argv[0] << ": invalid proxy" << endl;
		return EXIT_FAILURE;
	}

	try
	{
		Ice::ConnectionPtr conn = hello->ice_getConnection();
		if (conn)
		{
			Ice::ConnectionCallbackPtr concallback = new ConnCallback();
			cout << "Connection type: "<<conn->type() << endl;
			conn->setCallback(concallback);
		}
		else
		{
			cout << "collocated" << endl;
		}
	}
	catch (const Ice::LocalException& ex)
	{
		cout << ex << endl;
	}

	hello->login("robbie", "12345678");
	menu();

	CallbackPtr cb = new Callback();
	GetNameCallbackPtr getNamecb = new GetNameCallback();
	GetDeviceInfoCallbackPtr getDeviceInfocb = new GetDeviceInfollback();
	std::system("pause");
	return EXIT_SUCCESS;
	char c = 'x';
	do
	{
		try
		{
			cout << "==> ";
			cin >> c;
			if (c == 'i')
			{
				hello->sayHello(0);
			}
			else if (c == 'd')
			{
				hello->begin_sayHello(5000, newCallback_Hello_sayHello(cb, &Callback::response, &Callback::exception));
			}
			else if (c == 's')
			{
				hello->shutdown();
			}
			else if (c == 'n')
			{
				hello->begin_getName(123, newCallback_Hello_getName(getNamecb, &GetNameCallback::response, &GetNameCallback::exception));
			}
			else if (c == 'o')
			{
				hello->begin_getDeviceInfo(123, newCallback_Hello_getDeviceInfo(getDeviceInfocb, &GetDeviceInfollback::response, &GetDeviceInfollback::exception));
			}
			else if (c == 'x')
			{
				// Nothing to do
			}
			else if (c == '?')
			{
				menu();
			}
			else
			{
				cout << "unknown command `" << c << "'" << endl;
				menu();
			}
		}
		catch (const Ice::Exception& ex)
		{
			cerr << ex << endl;
		}
	} while (cin.good() && c != 'x');

	return EXIT_SUCCESS;
}

void
AsyncClient::menu()
{
	cout <<
		"usage:\n"
		"i: send immediate greeting\n"
		"d: send delayed greeting\n"
		"n: get name\n"
		"s: shutdown server\n"
		"x: exit\n"
		"?: help\n";
}

void ConnCallback::heartbeat(const::Ice::ConnectionPtr & conn)
{
	std::cout << "rev heart beat " << conn->getEndpoint()->toString() << "\n";
}

void ConnCallback::closed(const::Ice::ConnectionPtr & conn)
{
	std::cout << "close " << conn->getEndpoint()->toString() << "\n";
}
