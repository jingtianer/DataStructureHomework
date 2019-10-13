#ifndef MY_DULINKLIST_H
#define MY_DULINKLIST_H
#include "DuLNode.h"
#include "List.h"
using namespace std;
template<class T>
class DuLinkList :public list<T>
{
public:
	DuLinkList()
	{
		DuLinkList<T>::InitList();
	}
	void printAll() {
        ListTraverse(print_all<T>);
    }
	void InitList()
	{
		head = new DuLNode<T>(nullptr);
		last = new DuLNode<T>(head);
		head->next = last;
		size = 0;
	}
	void DestroyList()
	{
		ClearList();
		delete head;
		delete last;
	}
	void ClearList()
	{
		DuLNode<T>* move = head->next;
		while (move != last)
		{
			DuLNode<T>* p = move;
			move = move->next;
			delete p;
		}
		head->next = last;
		last->prior = head;
		size = 0;
	}
	bool ListEmpty()
	{
		return  size == 0;
	}
	int ListLength()
	{
		return size;
	}
	T GetElement(int i)
	{
		int j = 1;
		DuLNode<T>* move = head->next;
		for (; j < i && move != last; j++, move = move->next);
		if (move != last && j <= i)
		{
			return move->data;
		}
		throw "IndexOutOfBoundsException";
	}
	int LocateElement(T e, std::function<bool(T, T)> cmp)
	{
		int i = 1;
		for (DuLNode<T>* move = head->next; move != last; move = move->next, i++)
		{
			if (cmp(move->data, e))
			{
				return i;
			}
		}
		throw "ElementDoesNotExistException";
	}
	T PriorElement(T e, std::function<bool(T, T)> cmp)
	{
		if (head->next != last && cmp(head->next->data, e))
		{
			throw "PriorDoesNotExistException";
		}
		for (DuLNode<T>* move = head->next; move->next != last; move = move->next)
		{
			if (cmp(move->next->data, e))
			{
				return move->data;
			}
		}
		throw "ElementDoesNotExistException";
	}
	T NextElement(T e, std::function<bool(T, T)> cmp)
	{
		for (DuLNode<T>* move = head->next; move->next != last; move = move->next)
		{
			if (cmp(move->data, e))
			{
				return move->next->data;
			}
		}
		if (cmp(last->prior->data, e) && last->prior != head)
		{
			throw "NextDoesNotExistException";
		}
		throw "ElementDoesNotExistException";
	}
	void ListInsert(int i, T e)
	{
		DuLNode<T>* move = head;
		int j;
		for (j = 0; j < i - 1 && move != last; j++, move = move->next);
		if (move != last && j == i - 1)
		{
			DuLNode<T>* temp = new DuLNode<T>(move);
			temp->data = e;
			temp->next = move->next;
			move->next = temp;
			temp->next->prior = temp;
			size++;
			return;
		}
		throw "IndexOutOfBoundsException";
	}
	T ListDelete(int i)
	{
		DuLNode<T>* move = head;
		int j = 0;
		for (j = 0; j < i - 1 && move != last; j++, move = move->next);
		if (move->next != last && j == i - 1)//j == i - 1是为了防止输入i<=0
			//应该判断move.next，不能删去尾节点
		{
			DuLNode<T>* p = move->next;
			move->next = p->next;
			p->next->prior = move;
			T data = p->data;
			delete p;
			size--;
			return data;
		}
		throw "IndexOutOfBoundsException";
	}
	void ListTraverse(std::function<void(T)> visit)
	{
		cout << "head->last :";
		for (DuLNode<T>* move = head->next; move != last; move = move->next)
		{
			visit(move->data);
		}
		cout << "\nlast->head :";
		for (DuLNode<T>* move = last->prior; move != head; move = move->prior)
		{
			visit(move->data);
		}
	}
	void homework_2_37()
	{
		DuLNode<T>* insert = last;
		DuLNode<T>* end = last->prior;
		for (DuLNode<T>* move = head->next; move != end; move = move->next)
		{
			DuLNode<T>* temp = move->next;
			move->next = move->next->next;
			move->next->prior = move;
			temp->prior = insert->prior;
			temp->prior->next = temp;
			temp->next = insert;
			insert->prior = temp;
			insert = temp;
			//cout << "begin :{\n";
			//ListTraverse(print_all<T>);
			//cout << "\n}" << endl;
		}
	}

private:
	DuLNode<T>* head;
	DuLNode<T>* last;
	int size;
};
#endif
