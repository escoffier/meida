// c++11.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <atomic>
#include <thread>
#include <future>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include<list>
#include<map>
#include<utility>
#include "ThreadGuard.h"
#include "interruptibleThread.h"
using  std::string;
using namespace std::chrono_literals;

struct C : std::atomic<int> {
	C() : std::atomic<int>(0) {}
	void increase_member(int n) { for (int i = 0; i<n; ++i) fetch_add(1); }
};


class Person
{

public:
	Person() {};
	Person(const std::string str):name(str) {};
	~Person() {};

	std::string GetName() { std::cout<<"GetName thread id: "<<std::this_thread::get_id()<<"\n"; return name; };
private:
	std::string name;

};

template <typename RAIter>
int parallel_sum(RAIter beg, RAIter end)
{
	auto len = end - beg;
	if (len < 1000)
		return std::accumulate(beg, end, 0);

	RAIter mid = beg + len / 2;
	auto handle = std::async(std::launch::async,
		parallel_sum<RAIter>, mid, end);
	int sum = parallel_sum(beg, mid);
	return sum + handle.get();
}

void accumulate(std::vector<int>::iterator first,
	std::vector<int>::iterator last,
	std::promise<int> accumulate_promise )
{
	std::cout << "accumulate thread id: " << std::this_thread::get_id() << "\n";
	int sum = std::accumulate(first, last, 0);
	accumulate_promise.set_value(sum);  // Notify future
}

//void accumulate(std::vector<int>::iterator first,
//	std::vector<int>::iterator last,
//	std::promise<int> accumulate_promise)
//{
//	int sum = std::accumulate(first, last, 0);
//	accumulate_promise.set_value(sum);  // Notify future
//}

class  Object
{
public:
	Object();
	Object(int p1, int p2);
	~Object();
	bool operator==(const Object& obj) const;
	bool operator<(const Object& obj) const;
	int Geta() const { return a; }
	int Getb() const { return b; }
private:
	int a;
	int b;
	int c;
	int d;
};

 Object:: Object()
{
}

 Object::Object(int p1, int p2):
	 c(0), d(0)
 {
	 a = p1;
	 b = p2;
 }

 Object::~ Object()
{
}

 bool Object::operator<(const Object & obj) const
 {
	  return a < obj.a;;
 }

 bool Object::operator==(const Object& obj) const
 {
	 return (obj.a == a) && (obj.b == b);
 }



 //constexpr bool std::less<Object>::operator()(const Object &lhs, const Object &rhs) const
 //{
	// return lhs.Geta() < rhs.Getb();
 //}



 class ObjectContainer
 {
 public:
	 ObjectContainer();
	 ~ObjectContainer();
	 void Insert(const Object & obj);
 private:
	 std::list<Object> li;
	 std::map<Object, std::list<Object>::iterator, std::less<Object>> ObjMap;
 };

 //bool operator==<Object, std::list<Object>::iterator, std::less<Object>>(const Object & obj1, const Object & obj2)
 //{
	//return (obj1.Geta() == obj2.Geta()) && (obj1.Getb() == obj2.Getb());
 //}

 ObjectContainer::ObjectContainer()
 {
 }

 ObjectContainer::~ObjectContainer()
 {
 }
 void ObjectContainer::Insert(const Object & obj)
 {
	 if (ObjMap.find(obj) != ObjMap.end())
	 {
		 li.remove(obj);
		// ObjMap[obj] = li.insert(li.end(), obj);
	 }
	 //else
	 //{
		// li.remove(obj);
		// ObjMap[obj] = li.insert(li.end(), obj);
	 //}
	 ObjMap[obj] = li.insert(li.end(), obj);
 }

 using constptr = const char*;

 void  foo(constptr & p)
 {
	 std::cout << p << std::endl;
 }

 const int getValue()
 {
	 return 1;
 }

 void UpdateData(std::string & str)
 {
	 str.append("robbie");
	 //std::cout << "UpdateData: " << str << std::endl;
 }



 class TestObj
 {
 public:
	 TestObj();
	 ~TestObj();
	 TestObj(const TestObj & other)
	 {
		 std::cout << "Copy Construct TestObj\n";
		 data_ = other.data_;
	 }
	 TestObj& operator=(const TestObj & other) 
	 { 
		 std::cout << "assign Construct TestObj\n";
		 data_ = other.data_;
		 return *this;
	 }

	 TestObj(TestObj && other) noexcept
		 :data_(std::move(other.data_))
	 {
		 std::cout << "Move Construct TestObj\n";
	 }

	 TestObj& operator=( TestObj && other) noexcept
		// : data_(std::move(other.data_))
	 {
		 data_ = std::move(other.data_);
		 return *this;
	 }
 private:
	 int data_;
 };

 TestObj::TestObj() :
	 data_(0)
 {
	 std::cout << "Construct TestObj\n";
 }

 TestObj::~TestObj()
 {
	 std::cout << "Destruct TestObj\n";
 }

 TestObj test()
 {
	 TestObj obj1, obj2;
	 if (true)
	 {
		 return obj1;
	 }
	 else
	 {
		 return obj2;
	 }
 }

 TestObj testRVO()
 {
	 TestObj obj;
	 return obj;
     //return std::move(obj);

 }

 struct Foo {
	 void show(int i)
	 {
		// data_ = i;
		 std::cout << "show Foo " << i << "\n";
	 }
	 int data_;
 };
	void needptr(Foo* fn, int i)
	{
	if (!fn)
		std::cout << "fn == NULL" << '\n';
	fn->show(i);
};

void foo1()
{
	
	while (true)
	{
		std::this_thread::sleep_for(3s);
		interruption_point();
	}
	
}

void quickSort(int *array, unsigned int left, unsigned int right)
{
	int flag;
	flag = (right - left ) / 2;
	while ()
	{

	}
}




#include "Handler.h"
int main()
{
	C bar;
	//std::thread th(&C::increase_member, &bar, 1000 );
	//th.join();

	std::vector<int> vec(10000, 1);
	std::cout << "The sum is " << parallel_sum(vec.begin(), vec.end()) << "\n";

	Person Tom("Tom");

	std::cout << "Main thread id: " << std::this_thread::get_id() << "\n";
	auto name = std::async(std::launch::deferred, &Person::GetName, &Tom);
	std::string Name = name.get();
	std::cout << "Name is "<<Name<< "\n";

	std::vector<int> nums = { 1,2,3,4,5,6 };
	std::promise<int> promise;
	std::future<int> accumulateFuture = promise.get_future();
	std::async(std::launch::async, accumulate, nums.begin(), nums.end(), std::move(promise));

	accumulateFuture.wait();
	std::cout << "accumulate is " << accumulateFuture.get() << "\n";

	ObjectContainer objs;
	Object obj1(1, 2);
	Object obj2(3, 4);
	Object obj3(1, 2);
	objs.Insert(obj1);
	objs.Insert(obj2);
	objs.Insert(obj3);
	////////////////////////////////////////////////////

	/*std::vector<int> vec1{ 1, 2, 3, 3, 4, 5, 6, 7, 8 };

	for (auto it = vec1.begin(); it != vec1.end(); ++it)
	{
		if (*it > 2)
			it = vec1.erase(it);
		else
		{
			it++;
		}
	}

	for (const auto& val : vec1)
	{
		std::cout << val << ' ';
	}
	std::cout << std:: endl;*/

	//char * &str= "abcd";
	using contptr = const char*;

	const  char  *r = "hell0";
	int iv = 12;
	const int &&rrv = 12;
	const int &rv = getValue();

	
	{
		std::thread th1(&C::increase_member, &bar, 1000);
		//std::this_thread::sleep_for(3s);
		ThreadGuard thGuard(std::move(th1));
	}

	
	{
		std::string name("abcd");
		std::thread th(&UpdateData, std::ref(name));
		ThreadGuard thGuard(std::move(th));
		std::cout << "new name: " << name << std::endl;
	}


	{
		TestObj obj = testRVO();
		int a = 2;
	}

	{
		std::shared_ptr<Foo> sh1;
		needptr(sh1.get(), 1);
		Foo *ptr = nullptr;
		ptr->show(2);
	}

	{
		std::function<void()> f = std::bind(foo1);
		interruptible_thread th(f);
		interruptible_thread thb(f);
		th.interrupt();
		thb.interrupt();
		//th.join();
	}

	std::shared_ptr<ConcreteHandler2> handler2 = std::make_shared<ConcreteHandler2>(nullptr);
	std::shared_ptr<Handler> h = handler2;
	//如下的handler2类型为什么能顺利的转换为ConcreteHandler1？这点运用的是哪条规则？ 
	std::shared_ptr<ConcreteHandler1> handler1 = std::make_shared<ConcreteHandler1>(handler2);
	//foo("122222");
    return 0;
}

