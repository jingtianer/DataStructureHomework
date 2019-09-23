#ifndef MY_SQ_LIST_H
#define MY_SQ_LIST_H
#include "List.h"

template <class T>
class SqList :public list<T>
{
private:
	T* elem;
	int Length;
	int ListSize;
public:
	SqList()
	{
		SqList<T>::InitList();
	}

	SqList(SqList* L)
	{
		this->elem = L->elem;
		this->Length = L->Length;
		this->ListSize = L->ListSize;
	}

	void InitList()
	{
		//elem = static_cast<T *>(malloc(ListInitSize * sizeof(T)));
		elem = new T[ListInitSize];
		if (!elem)
		{
			throw "Memory alloc fail";
		}
		Length = 0;
		ListSize = ListInitSize;
	}

	void DestroyList()
	{
		delete []elem;
		elem = nullptr;
		Length = 0;
		ListSize = 0;
	}

	void ClearList()
	{
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
		i--;
		if (isOutOfBounds(i))
		{
			throw "ArrayIndexOutOfBoundsException";
		}
		return elem[i];
	}

	int LocateElement(T e, std::function<bool(T a, T b)> cmp)
	{
		for (int i = 0; i < Length; i++)
		{
			if (cmp(e, elem[i]))
			{
				return i + 1;
			}
		}
		throw "ElementNotFoundException";
	}

	T PriorElement(T e, std::function<bool(T a, T b)> cmp)
	{
		if (cmp(e, elem[0]))
		{
			throw "PriorDoesNotExistException";
		}
		for (int i = 0; i < Length - 1; i++)
		{
			if (cmp(e, elem[i + 1]))
			{
				return elem[i];
			}
		}
		throw "ElementDoesNotExistException";
	}

	T NextElement(T e, std::function<bool(T a, T b)> cmp)
	{
		for (int i = 1; i < Length; i++)
		{
			if (cmp(e, elem[i - 1]))
			{
				return elem[i];
			}
		}
		if (cmp(e, elem[Length - 1]))
		{
			throw "NextDoesNotExistException";
		}
		throw "ElementDoesNotExistException";
	}

	void ListInsert(int i, T e)
	{
		if (i > Length + 1 || i <= 0)
		{
			throw "ArrayIndexOutOfBoundsException";
		}
		T* temp;
		if (Length >= ListSize)
		{ 
			temp = static_cast<T*>(realloc(elem, sizeof(T) * (ListSize + ListIncreasement)));
			if (!temp)
			{
				throw "ReallocFailException";
			}
			elem = temp;
			ListSize += ListIncreasement;
		}
		T* q = elem + i - 1;
		T* p = elem + Length - 1;
		while (p >= q)
		{
			*(p + 1) = *p;
			--p;
		}
		*q = e;
		Length++;
	}

	T ListDelete(int i)
	{
		if (isOutOfBounds(i-1))
		{
			throw "ArrayIndexOutOfBoundsException";
		}
		T e = elem[i - 1];
		T* p = elem + i - 1;
		T* q = elem + Length - 1;
		while (p <= q)
		{
			*p = *(p + 1);
			++p;
		}
		Length--;
		return e;
	}

	SqList<T>& MergeList_Sq(SqList<T>* L, std::function<bool(T a, T b)> greater, std::function<bool(T a, T b)> equal)
	{
		auto* list = new SqList<T>();
		delete []list->elem;
		list->Length = this->Length + L->Length;
		list->ListSize = this->ListSize + L->ListSize;
		list->elem = new T[list->ListSize];

		T* la = this->elem;
		T* lb = L->elem;
		T* lc = list->elem;

		T* la_last = la + this->Length - 1;
		T* lb_last = lb + L->Length - 1;

		if (!la || !lb || !lc)
		{
			throw "UnExpectedNullPointerException";
		}
		while (la <= la_last && lb <= lb_last)
		{
			if (greater(*la, *lb) || equal(*la, *lb))
			{
				*lc = *lb;
				++lb;
			}
			else
			{
				*lc = *la;
				++la;
			}
			++lc;
		}
		while (la <= la_last)
		{
			*lc = *la;
			++la;
			++lc;
		}
		while (lb <= lb_last)
		{
			*lc = *lb;
			++lc;
			++lb;
		}
		return *list;
	}

	void ListTraverse(std::function<void(T x)> visit)
	{
		for (int i = 0; i < Length; i++)
		{
			visit(elem[i]);
		}
	}

	virtual ~SqList() { SqList<T>::DestroyList(); }

	int getLength() const
	{
		return this->Length;
	}

	int getListSize() const
	{
		return this->ListSize;
	}

	SqList<T>& operator<<(SqList& L)
	{
		return MergeList_Sq(&L, Greater<T>, equals<T>);
	}

	SqList<T>& operator>>(SqList& L)
	{
		return MergeList_Sq(&L, Smaller<T>, equals<T>);
	}

	SqList<T>& operator+(SqList<T>& L)
	{
		return CatList_Sq(&L);
	}

	SqList<T>& CatList_Sq(SqList<T>* L)
	{
		auto* list = new SqList<T>();
		delete []list->elem;
		list->Length = this->Length + L->Length;
		list->ListSize = this->ListSize + L->ListSize;
		list->elem = new T[list->ListSize];

		T* la = this->elem;
		T* lb = L->elem;
		T* lc = list->elem;

		T* la_last = la + this->Length - 1;
		T* lb_last = lb + L->Length - 1;
		while (la <= la_last)
		{
			*lc++ = *la++;
		}
		while (lb <= lb_last)
		{
			*lc++ = *lb++;
		}
		return *list;
	}
	void Delete(std::function<bool(T x)> condition)
	{
		T * temp = new T[ListSize];
		T* move = temp;
		for (int i = 0; i < Length; i++)
		{
			if (!condition(elem[i]))
			{
				*move = elem[i];
				++move;
			}
		}
		Length = move - temp;
		delete elem;
		elem = temp;
	}

private:
	bool isOutOfBounds(int index) const
	{
		return !(index >= 0 && index < Length);
	}
};
#endif
