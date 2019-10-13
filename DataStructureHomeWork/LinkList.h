#ifndef MY_LINKLIST_H
#define MY_LINKLIST_H
#include "List.h"
#include "LNode.h"
#include <vector>
template <class T>
class LinkList :public list<T>
{
private:
	LNode<T>* head;
	int Length;
public:
	LinkList(): list<T>()
	{
		LinkList<T>::InitList();
	}
	void InsertToHead(std::vector<T>& arr)//对应CreateList_L，头插法
	{
		int size = arr.size();
		for (int i = 0; i < size; i++)
		{
			LNode<T> * temp = new LNode<T>();
			temp->data = arr[i];
			temp->next = head->next;
			head->next = temp;
		}
		Length += size;
	}

	void InitList()
	{
		head = new LNode<T>;
		Length = 0;
	}

	void DestroyList()
	{
		ClearList();
		delete head;
	}

	void ClearList()
	{
		LNode<T>* move = head->next;
		while (move)
		{
			LNode<T>* cur = move;
			move = move->next;
			delete cur;
		}
		head->next = nullptr;
		Length = 0;
	}

	bool ListEmpty()
	{
		return Length == 0;
	}

	int ListLength()
	{
		return Length;
	}

	T GetElement(int i)
	{

		LNode<T>* move = head->next;
		int j;
		for (j = 1; j < i && move; j++, move = move->next);
		if (move && j <= i) { return move->data; }
		throw "IndexOutOfBoundsException";
	}

	int LocateElement(T e, std::function<bool(T, T)> cmp)
	{
		int i = 0;
		auto move = head->next;
		while (move)
		{
			if (cmp(e, move->data))
			{
				return i + 1;
			}
			move = move->next;
			i++;
		}
		throw "ElementNotFoundException";
	}

	T PriorElement(T e, std::function<bool(T, T)> cmp)
	{
		auto move = head->next;
		if (head->next && cmp(e, head->next->data))
		{
			throw "PriorDoesNotExistException";
		}
		while (move->next)
		{
			if (cmp(e, move->next->data))
			{
				return move->data;
			}
			move = move->next;
		}
		throw "ElementNotFoundException";
	}

	T NextElement(T e, std::function<bool(T, T)> cmp)
	{
		auto move = head->next;
		while (move)
		{
			if (cmp(e, move->data))
			{
				if (move->next)
				{
					return move->next->data;
				}
				throw "NextDoesNotExistException";
			}
			move = move->next;
		}
		throw "ElementNotFoundException";
	}

	void ListInsert(int i, T e)
	{
		/*if (i <= 0)
		{
			throw "IndexOutOfBoundsException";
		}*/
		LNode<T>* move = head;
		int j;
		for (j = 0; j < i - 1 && move; j++, move = move->next);
		if (move && j <= i-1)
		{
			LNode<T>* temp = new LNode<T>();
			temp->data = e;
			temp->next = move->next;
			move->next = temp;
			Length++;

			return;
		}
		throw "IndexOutOfBoundsException";
	}

	T ListDelete(int i)
	{
		if (i <= 0)
		{
			throw "IndexOutOfBoundsException";
		}
		LNode<T>* move = head;
		for (int j = 0; j < i - 1 && move; j++, move = move->next);
		if (move->next)
		{
			LNode<T>* temp = move->next;
			T e = temp->data;
			move->next = move->next->next;
			delete temp;
			Length--;
			return e;
		}
		throw "IndexOutOfBoundsException";
	}
    void printAll() {
        ListTraverse(print_all<T>);
    }
	void ListTraverse(std::function<void(T)> visit)
	{
		LNode<T>* move = head->next;
		while (move)
		{
			visit(move->data);
			move = move->next;
		}
	}
	LinkList<T>& operator+(LinkList<T>& L)
	{
		return CatList_Link(&L);
	}
	LinkList<T>& CatList_Link(LinkList<T>* L)
	{
		LinkList<T> * list = new LinkList<T>();
		list->Length = this->Length + L->Length;
		LNode<T> * move = this->head;
		while (move->next)
		{
			move = move->next;
		}
		move->next = L->head->next;
		list->head->next = this->head->next;
		this->Length = 0;
		L->Length = 0;
		this->head->next = nullptr;
		L->head->next = nullptr;
		return *list;
	}
	LinkList<T>& operator<<(LinkList<T>& L)
	{
		return MergeList_Link(&L, Greater<T>, equals<T>);
	}
	LinkList<T>& operator>>(LinkList<T>& L)
	{
		return  MergeList_Link(&L, Smaller<T>, equals<T>);
	}
	LinkList<T>& MergeList_Link(LinkList<T>* L, std::function<bool(T a, T b)> greater, std::function<bool(T a, T b)> equal)
	{
		LinkList<T> * list = new LinkList<T>();
		LNode<T> * p = this->head->next;
		LNode<T> * q = L->head->next;
		LNode<T> * move = list->head;//与书上不同，不破坏各个结构的头结点
		list->Length = this->Length + L->Length;
		while (p && q)
		{
			if (greater(p->data, q->data) || equal(p->data, q->data))
			{
				move->next = q;
				q = q->next;
			} else
			{
				move->next = p;
				p = p->next;
			}
			move = move->next;//与书上不同，move后移更简明
		}
		move->next = p ? p : q;

		this->head->next = nullptr;
		L->head->next = nullptr;
		this->Length = 0;
		L->Length = 0;//两个表的结构被破坏，恢复成空表
		return *list;
	}


};

#endif MY_LINKLIST_H
