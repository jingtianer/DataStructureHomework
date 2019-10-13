#ifndef MY_CYCLE_LINKLIST_H
#define MY_CYCLE_LINKLIST_H
#include "List.h"
#include "LNode.h"
template<class T>
class CycleList :public list<T>
{
private:
	LNode<T> * tail;
	int size;
public:
	CycleList() : list<T>()
	{
		CycleList<T>::InitList();
	}
	LNode<T> * head()
	{
		return tail->next;
	}
	void InitList()
	{
		tail = new LNode<T>();
		size = 0;
		tail->next = tail;
	}
	void DestroyList()
	{
		LNode<T> * p = tail->next;
		while (p)
		{
			LNode<T> * temp = p->next;
			delete p;
			p = temp;
		}
		size = 0;
	}
	void ClearList()
	{
		LNode<T> * head = tail->next;
		LNode<T> * p = head->next;
		while (p != head)
		{
			LNode<T> * temp = p->next;
			delete p;
			p = temp;
		}
		tail = head;
		tail->next = head;
		size = 0;
	}
	bool ListEmpty()
	{
		return size == 0 && tail == head();//双重验证
	}
	int ListLength()
	{
		return  size;
	}
	T GetElement(int i)
	{
		LNode<T>* temp = head()->next;//得到头节点
		int j = 1;
		for(; j < i && temp != tail; j++, temp = temp->next);
		if (temp != tail && j <= i)
		{
			return temp->data;
		}
		throw "IndexOutOfBoundsException";
	}
	int LocateElement(T e, std::function<bool(T, T)> cmp)
	{
		int i = 0;
		LNode<T>* move = this->head()->next;
		for (i = 0;move != head() ;i++, move = move->next)
		{
			if (cmp(move->data, e))
			{
				return i + 1;
			}
		}
		throw "ElementDoesNotExistException";
	}
	T PriorElement(T e, std::function<bool(T, T)> cmp)
	{
		if (cmp(head()->next->data, e) && head() != tail)
		{
			throw "PriorDoesNotExistException";
		}
		LNode<T> *move = head()->next;
		for (; move != head(); move = move->next)
		{
			if (move->next != head() && cmp(move->next->data, e))
			{
				return move->data;
			}
		}
		throw "ElementNotFoundException";
	}
	void printAll() {
        ListTraverse(print_all<T>);
    }
	T NextElement(T e, std::function<bool(T, T)> cmp)
	{
		LNode<T> *move = head()->next;
		for (; move != head(); move = move->next)
		{
			if (cmp(move->data, e) && move->next != head())
			{
				return move->next->data;
			}
			if (cmp(move->data, e) && move->next == head())
			{
				return head()->next->data;
			}
		}
		throw "ElementDoesNotExistException";
	}
	void ListInsert(int i, T e)
	{
		LNode<T> * move= head()->next;
		int j = 1;
		for (j = 1; j < i-1 && move != head(); j++, move = move->next);
		if (tail != head() && (move == head() || j > i))
		{
			throw "IndexOutOfBoundsException";
		}
		if (i == 1)
		{
			move = head();
		}
		LNode<T> * temp = new LNode<T>();
		temp->data = e;
		temp->next = move->next;
		move->next = temp;
		if (move == tail)
		{
			tail = temp;
		}
		size++;

	}
	T ListDelete(int i)
	{
		LNode<T>* temp = head()->next;
		int j = 1;
		for (j = 1; j < i-1 && temp != tail; j++, temp = temp->next);
		if (j > i || temp == tail)
            throw "IndexOutOfBoundsException";
		if (i == 1) temp = head();
		LNode<T> * p = temp->next;
		temp->next  =temp->next->next;
		T data = p->data;
		if (p == tail) tail= temp;
		delete p;
		size--;
		return data;
	}
	void ListTraverse(std::function<void(T)> visit)
	{
		LNode<T> * move = head()->next;
		for (; move != head(); move = move->next)
		{
			visit(move->data);
		}
	}


};


#endif
