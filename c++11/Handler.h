#pragma once
#include <memory>
#include <iostream>
class Handler
{
protected:
	std::shared_ptr<Handler> m_next;
public:
	Handler(std::shared_ptr<Handler> next) : m_next(next) { std::cout << "Handler ctor\n"; }
};

class ConcreteHandler1 : public Handler
{
public:
	ConcreteHandler1(std::shared_ptr<Handler> next) : Handler(next) { std::cout << "ConcreteHandler1 ctor\n"; }
};
class ConcreteHandler2 : public Handler
{
public:
	ConcreteHandler2(std::shared_ptr<Handler> next) : Handler(next) { std::cout << "ConcreteHandler2 ctor\n"; }
};
