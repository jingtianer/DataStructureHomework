#ifndef MY_LIST_H
#define MY_LIST_H
#include <cstdlib>
#include <functional>
#include <iostream>
#include "printable.h"
static const int ListInitSize = 100;
static const int ListIncreasement = 10;
template <class T>
class list: public Printable<T>
{
public:
	virtual ~list()
	{
	}

	virtual void InitList() = 0;
	virtual void DestroyList() = 0;
	virtual void ClearList() = 0;
	virtual bool ListEmpty() = 0;
	virtual int ListLength() = 0;
	virtual T GetElement(int i) = 0;
	virtual int LocateElement(T e, std::function<bool(T a, T b)> cmp) = 0;
	virtual T PriorElement(T e, std::function<bool(T a, T b)> cmp) = 0;
	virtual T NextElement(T e, std::function<bool(T a, T b)> cmp) = 0;
	virtual void ListInsert(int i, T e) = 0;
	virtual T ListDelete(int i) = 0;
	virtual void ListTraverse(std::function<void(T x)> visit) = 0;
};

#endif
