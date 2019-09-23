#ifndef MY_STACK_H
#define MY_STACK_H
#include <functional>
#include <iostream>

static const int StackInitSize = 100;
static const int StackIncreasement = 10;

const auto print_all = [](int x) { std::cout << x << " "; };
const auto equals = [](int i, int j)-> bool { return i == j; };
const auto Greater = [](int i, int j) -> bool { return i > j; };
const auto Smaller = [](int i, int j) -> bool { return i < j; };

template<class T>
class Stack
{
public:
	virtual void InitStack() = 0;
	virtual void DestoryStack() = 0;
	virtual void ClearStack() = 0;
	virtual bool StackEmpty() = 0;
	virtual int StackLength() = 0;
	virtual T GetTop() = 0;
	virtual void Push(T e) = 0;
	virtual T Pop() = 0;
	virtual void StackTraverse(std::function<void(T e)> visit) = 0;
	virtual ~Stack(){}
};
#endif
