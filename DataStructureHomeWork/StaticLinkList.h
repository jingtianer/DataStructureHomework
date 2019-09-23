#ifndef MY_SATAIC_LINK_LIST_H
#define MY_SATAIC_LINK_LIST_H
#include "List.h"
#include "StaticLNode.h"

template<class T>
class StaticLinkList : public list<T>
{
public:
	StaticLinkList()
	{
		StaticLinkList<T>::InitList();
	}
	void InitList()
	{
		elem = new StaticLNode<T>[ListInitSize];
		if (!elem)
		{
			throw "Memory alloc Fail";
		}
		length = 0;
		//不能用head充当space，因为其cur永远指向第一个可用节点
		Space = 1;
		ListSize = ListInitSize;
		for (int i = 1; i < ListSize - 1; i++)
		{
			elem[i].cur = i + 1;
		}
	}
	void DestroyList()
	{
		free(elem);
	}
	void ClearList()
	{
		elem[0].cur = -1;
		Space = 1;
		length = 0;
	}
	bool ListEmpty()
	{
		return length == 0;
	}
	int ListLength()
	{
		return length;
	}
	int head()
	{
		return 0;
		
	}
	int next(int i)
	{
		return elem[i].cur;
	}
	bool isNull(int i)
	{
		return i == -1;
	}
	T GetElement(int i)
	{
		int move = next(head());
		int j;
		for (j = 1; j < i && !isNull(move); j++, move = next(move));
		if (!isNull(move) && j <= i) { return elem[move].data; }
		throw "IndexOutOfBoundsException";
	}
	int LocateElement(T e, std::function<bool(T, T)> cmp)
	{
		int i = 0;
		int move = next(head());
		while (!isNull(move))
		{
			if (cmp(e, elem[move].data))
			{
				return i + 1;
			}
			move = next(move);
			i++;
		}
		throw "ElementNotFoundException";
	}
	T PriorElement(T e, std::function<bool(T, T)> cmp)
	{
		int move = next(head());
		if (!isNull(next(head())) && cmp(e, elem[next(head())].data))
		{
			throw "PriorDoesNotExistException";
		}
		while (!isNull(next(move)))
		{
			if (cmp(e, elem[next(move)].data))
			{
				return elem[move].data;
			}
			move = next(move);
		}
		throw "ElementNotFoundException";
	}
	T NextElement(T e, std::function<bool(T, T)> cmp)
	{
		auto move = next(head());
		while (!isNull(move))
		{
			if (cmp(e, elem[move].data))
			{
				if (!isNull(next(move)))
				{
					return elem[next(move)].data;
				}
				throw "NextDoesNotExistException";
			}
			move = next(move);
		}
		throw "ElementNotFoundException";
	}
	void ListInsert(int i, T e)
	{
		/*if (i <= 0)
		{
			throw "IndexOutOfBoundsException";
		}*/
		int move = head();
		int j;
		for (j = 0; j < i - 1 && !isNull(move); j++, move = next(move))
		{
			;
		}
		if (!isNull(move) && j <= i-1)
		{
			if (length + 2>= ListSize)
			{
				StaticLNode<T> * temp = new StaticLNode<T>[ListSize + ListIncreasement];
				if (!temp)
				{
					throw "Memory Alloc Fail";
				}
				
				for (int j = 0; j <= length; j++)
				{
					temp[j] = elem[j];
				}
				for (int j = length+1; j < ListSize + ListIncreasement -1; j++)
				{
					temp[j].cur = j + 1;
				}
				temp[ ListSize + ListIncreasement -1].cur = -1;
				ListSize += ListIncreasement;
				delete []elem;
				elem = temp;
				
			}
			
			int temp = Space;
			Space = elem[Space].cur;
			elem[temp].data = e;
			elem[temp].cur = elem[move].cur;
			elem[move].cur = temp;
			length++;
			
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
		int move = head();
		for (int j = 0; j < i - 1 && !isNull(move); j++, move = next(move));
		if (!isNull(next(move)))
		{
			int index = elem[move].cur;
			int temp = next(move);
			T e = elem[temp].data;
			elem[move].cur = elem[next(move)].cur;
			//free
			elem[temp].cur = Space;
			Space = temp;
			
			length--;
			return e;
		}
		throw "IndexOutOfBoundsException";
	}
	void ListTraverse(std::function<void(T)> visit)
	{
		for (int move = next(head()); !isNull(move); move = next(move))
		{
			visit(elem[move].data);
		}
	}
private:
	StaticLNode<T> * elem;
	int Space;
	int length;
	int ListSize;
};
#endif

