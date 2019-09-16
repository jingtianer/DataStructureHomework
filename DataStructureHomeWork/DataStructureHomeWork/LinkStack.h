#ifndef MY_LINK_STACK_H
#define MY_LINK_STACK_H
#include "Stack.h"
#include "SNode.h"
template<class T>
class LinkStack : public Stack<T>
{
public:
	LinkStack() : Stack<T>()
	{
		LinkStack<T>::InitStack();
	}
	~LinkStack()
	{
		LinkStack<T>::DestoryStack();
	}
	void InitStack()
	{
		base = new SNode<T>(nullptr);
		top = base;
		Length = 0;
	}
	void DestoryStack()
	{
		SNode<T> * move = base;
		while (move)
		{
			SNode<T> * p = move->next;
			delete move;
			move = p;
		}
		base = top = nullptr;
		Length = 0;
	}
	void ClearStack()
	{
		SNode<T> * move = base->next;
		while (move)
		{
			SNode<T> * p = move->next;
			delete move;
			move = p;
		}
		top = base;
		base->next = nullptr;
		Length = 0;
	}
	bool StackEmpty()
	{
		return Length == 0;
	}
	int StackLength()
	{
		return Length;
	}
	T GetTop()
	{
		return top->data;
	}
	void Push(T e)
	{
		SNode<T> * temp = new SNode<T>(e, top);
		top->next = temp;
		top = temp;
		Length++;
	}
	T Pop()
	{
		T e = top->data;
		SNode<T> * temp = top->prior;
		delete top;
		top = temp;
		top->next = nullptr;
		Length--;
		return e;
	}
	void StackTraverse(std::function<void(T)> visit)
	{
		std::cout << "bottom->top :";
		for (SNode<T> * move = base->next; move; move = move->next)
		{
			visit(move->data);
		}
		std::cout << "\ntop->bottom :";
		for (SNode<T> * move = top; move != base; move = move->prior)
		{
			visit(move->data);
		}
	}

private:
	SNode<T> * base;
	SNode<T> * top;
	int Length;
};

#endif
