#ifndef MY_SQ_STACK_H
#define MY_SQ_STACK_H
#include "Stack.h"
template<class T>
class SqStack : public Stack<T>
{
public:
	SqStack() : Stack<T>()
	{
		SqStack<T>::InitStack();
	}
	~SqStack()
	{
		SqStack<T>::DestoryStack();
	}
	void InitStack()
	{
		base = (T*)malloc(sizeof(T) * StackInitSize);
		top = base;
		StackSize = StackInitSize;
	}
	void DestoryStack()
	{
		free(base);
		base = nullptr;
		top = nullptr;
		StackSize = 0;
	}
	void ClearStack()
	{
		top = base;
	}
	bool StackEmpty()
	{
		return (top - base) ? false : true;
	}
	int StackLength()
	{

		return top - base;
	}
	T GetTop()
	{
		return *(top - 1);
	}
	void Push(T e)
	{
		if (StackLength() >= StackSize)
		{
			int len = StackLength();
			T * temp = (T *) realloc(base, sizeof(T) * (StackSize + StackIncreasement));
			if (!temp)
			{
				throw "MemeoryAllocFail";
			}
			base = temp;
			top = base + len;
			StackSize += StackIncreasement;
		}

		*top = e;
		++top;
	}
	T Pop()
	{
		T e = *(top - 1);
		--top;
		return e;
	}
	void printAll() {
        StackTraverse(print_all<T>);
    }
	void StackTraverse(std::function<void(T)> visit)
	{
		for (T * move = top - 1; move >= base; --move)
		{
			visit(*move);
		}
	}
private:
	T * base;
	T * top;
	int StackSize;
};

#endif
