/**
 * \brief 有关测试的全局设置
 */
#include "TestSettings.h"
/**
 * \brief 线性表
 */

#ifndef NOT_TEST_LIST
#include "SqList.h"
#include "LinkList.h"
#include "CycleLinkList.h"
#include "DuLinkList.h"
#include "StaticLinkList.h"

/**
 * \brief 测试具体的数据结构，不想测试的可以注释，可以同时测试多个
 */
#define TEST_SQ_LIST
#define TEST_LINK_LIST
#define TEST_CYCLE_LINK_LIST
#define TEST_DU_LINK_LIST
#define TEST_STATIC_LINK_LIST
/**
 * \brief 是否想在测试模块之间暂停
 */
#define PAUSE

/**
 * \brief 测试数据量
 */
const int GIDTEST = TEST_SIZE;
const int TESTSIZE1 = GIDTEST;


void print(list<int>* l)
{
	cout << "begin :{\n";
	l->ListTraverse(print_all<int>);
	cout << "\n}" << endl;
}
void SqMergemain()
{
	SqList<int> la, lb, lc, ld;
	const int testSize = TESTSIZE1 / 10;
	for (int i = 0; i < testSize; i++)
	{
		la.ListInsert(la.getLength() + 1, i);
		lb.ListInsert(lb.ListLength() + 1, 6 * i - 60);
		lc.ListInsert(lc.getLength() + 1, testSize - i);
		ld.ListInsert(ld.getLength() + 1, testSize - 2 * i);
	}
	SqList<int> le = la << lb;
	SqList<int> lf = lc >> ld;

	SqList<int> lg = la + lb + lc + ld + le + lf;
	print(&la);
	print(&lb);
	print(&lc);
	print(&ld);
	print(&le);
	print(&lf);
	print(&lg);
#ifdef PAUSE
	system("pause");
#endif
}


void LinkMergemain()
{
	LinkList<int> a, b;
	for (int i = 0; i < TESTSIZE1; i++)
	{
		a.ListInsert(a.ListLength() + 1, i);
		b.ListInsert(b.ListLength() + 1, i * i);
	}

	print(&a);
	print(&b);
	LinkList<int> c = a.CatList_Link(&b);
	print(&c);
	print(&a);
	print(&b);
	LinkList<int> e, f;
	for (int i = 0; i < TESTSIZE1; i++)
	{
		a.ListInsert(a.ListLength() + 1, i);
		b.ListInsert(b.ListLength() + 1, i * i);
		e.ListInsert(e.ListLength() + 1, 100 - i);
		f.ListInsert(f.ListLength() + 1, 100 - 2 * i);
	}
	LinkList<int> d = a << b;
	LinkList<int> g = e >> f;
	print(&d);
	print(&g);
	print(&a);
	print(&b);
	print(&e);
	print(&f);
#ifdef PAUSE
	system("pause");
#endif
}



void GeneralInsertDelete(list<int>* l)
{
	cout << "insert to tail" << endl;
	for (int i = 0; i < GIDTEST; i++)
	{
		l->ListInsert(l->ListLength() + 1, i);
		cout << "Length :" << l->ListLength();
	}
	cout << "\n";
	print(l);
	cout << "insert to incorrect position\n";

	try
	{
		cout << "insert to -1\n";
		l->ListInsert(-1, 888);
	}
	catch (char const const* s)
	{
		cout << s << endl;
	}
	print(l);
	try
	{
		cout << "insert to 0\n";
		l->ListInsert(0, 888);
	}
	catch (char const* s)
	{
		cout << s << endl;
	}
	print(l);
	try
	{
		cout << "insert to l.ListLength() + 2 = " << l->ListLength() + 2 << endl;
		l->ListInsert(l->ListLength() + 2, 888);
		print(l);
	}
	catch (char const* s)
	{
		cout << s << endl;
	}
	print(l);
	cout << "delete test" << endl;
	for (int i = 1; i < 10; i++)
	{
		cout << "----------" << "delete item in " << GIDTEST / i << "----------" << endl;
		try
		{
			int t = l->ListDelete(GIDTEST / i);
			cout << t << " deleted" << endl;
			print(l);
			l->ListInsert(GIDTEST / i, t);
			cout << "----------" << t << " insert back"<< "----------\n"  << endl;
		}
		catch (char const* s)
		{
			cout << s << endl;
		}
	}
	int temp[3] = {-1,0,l->ListLength() + 1};
	for (int i = 0; i < 3; i++)
	{
		cout << "----------" << "delete item in " << temp[i] << "----------" << endl;
		try
		{
			int t = l->ListDelete(temp[i]);
			cout << t << " deleted" << endl;
			print(l);
			l->ListInsert(temp[i], t);
			cout << "----------" << t << " insert back"<< "----------"  << endl;
		}
		catch (char const* s)
		{
			cout << s << endl;
		}
	}

	cout << "clear all item" << endl;
	l->ClearList();
	print(l);
	cout << "isListEmpty ? : " << (l->ListEmpty() ? "true" : "false") << endl;

	cout << "insert back" << endl;

	for (int i = 0; i < GIDTEST; i++)
	{
		l->ListInsert(1, i);
	}
	print(l);
}

void GeneralFindTest(list<int>* l)
{
	for (int i = -1; i < l->ListLength() + 2; i++)
	{
		
		cout << "pos = " << i + 1 << "\telem = ";
		try
		{
			cout << l->GetElement(i + 1) << endl;
		}
		catch (char const* s)
		{
			cout << s;
		}
		try
		{
			cout << "\tprior elem = ";
			cout << l->PriorElement(l->GetElement(i + 1), equals<int>);
		}
		catch (char const* s)
		{
			cout << s;
		}
		try
		{
			cout << "\tnext elem = ";
			cout << l->NextElement(l->GetElement(i + 1), equals<int>) << endl;
		}
		catch (char const* s)
		{
			cout << s << endl;
		}
	}
	print(l);
}

void GeneralTest(list<int>* l, std::function<void()> other)
{
	GeneralInsertDelete(l);
	cout << "----------" << "setp 1 " << "insert delete test" << "----------OK" << endl;
#ifdef PAUSE
	system("pause");
#endif
	GeneralFindTest(l);
	cout << "----------" << "setp 2 " << "GeneralFindTest" << "----------OK" << endl;
#ifdef PAUSE
	system("pause");
#endif
	if (other)
	{
		
		other();
		cout << "----------" << "step 3 " << "OtherFunctionText" << "----------OK" << endl;
#ifdef PAUSE
	system("pause");
#endif
	}
}

int main(int argc, char const* argv[])
{
#ifdef WRITE_TO_FILE
	WriteToFile();
#endif
#ifdef TEST_SQ_LIST
	cout << "SqList" << endl;
	list<int> * sqList = new SqList<int>();
	GeneralTest(sqList, SqMergemain);
	system("cls");
#endif

#ifdef TEST_LINK_LIST
	cout << "LinkList" << endl;
	list<int>* linkList = new LinkList<int>();
	GeneralTest(linkList, LinkMergemain);
	system("cls");
#endif

#ifdef TEST_CYCLE_LINK_LIST
	cout << "CycleList" << endl;
	list<int>* cycleList = new CycleList<int>();
	GeneralTest(cycleList, nullptr);
	system("cls");
#endif
#ifdef TEST_DU_LINK_LIST
	cout << "DuLinkList" << endl;
	list<int>* duList = new DuLinkList<int>();
	GeneralTest(duList, nullptr);
	system("cls");
#endif

	#ifdef TEST_STATIC_LINK_LIST
	
	cout << "StaticLinkList" << endl;
	list<int>* staticList = new StaticLinkList<int>();
	GeneralTest(staticList, nullptr);
	system("cls");
#endif
	
#ifdef WRITE_TO_FILE
	RecoverCOUT();
#endif
	return 0;
}

#endif
/**
 * \brief 栈
 */
#ifndef NOT_TEST_STACK
#include "Stack.h"
#include "SqStack.h"
#include "LinkStack.h"
/**
 * \brief 测试具体的数据结构，不想测试的可以注释，可以同时测试多个
 */
#define TEST_SQ_STACK
#define TEST_Link_STACK

void print(Stack<int>* s)
{
	cout << "begin : {\n";
	s->StackTraverse(print_all);
	cout << "\n}\n";
}
void GeneralTest(Stack<int>* s, std::function<void()> other)
{
	print(s);
	for (int  i = 0; i < TEST_SIZE; i++)
	{
		s->Push(i);
		print(s);
		cout << "length = " << s->StackLength() << endl
		<< "isEmpty = " << (s->StackEmpty() ? "true" : "false") << endl;
	}
	s->ClearStack();
	print(s);
	for (int  i = 0; i < TEST_SIZE; i++)
	{
		s->Push(i);
	}
	print(s);
	std::cout << "----------" << "push clear test" << "----------OK" <<endl;
	system("pause");
	while (!s->StackEmpty())
	{
		cout << "top == " << s->GetTop();
		int temp = s->Pop();
		cout << "\npop the top : " << temp << endl;
		print(s);
		cout << "length = " << s->StackLength() << endl
		<< "isEmpty = " << (s->StackEmpty() ? "true" : "false") << endl;
	}
	std::cout << "----------" << "pop test" << "----------OK" <<endl;
	system("pause");
	
	if (other)
	{
		other();
		std::cout << "----------" << "other test" << "----------OK" <<endl;
		system("pause");
	}
}
int main(int argc, char const* argv[])
{
#ifdef WRITE_TO_FILE
	WriteToFile();
#endif
#ifdef TEST_SQ_STACK
	Stack<int> * sqStack = new SqStack<int>();
	GeneralTest(sqStack, nullptr);
#endif

#ifdef TEST_Link_STACK
	Stack<int> *linkStack = new LinkStack<int>();
	GeneralTest(linkStack, nullptr);
#endif

#ifdef WRITE_TO_FILE
	RecoverCOUT();
#endif
	return 0;
}

#endif
/*
#include "DuLinkList.h"
template<class T>
void print(list<T> * l)
{
	cout << "begin :{\n";
	l->ListTraverse(print_all<T>);
	cout << "\n}" << endl;
}
int main(int argc, char const* argv[])
{
	DuLinkList<int> l;
	for (int i = 0; i < 100; i++)
	{
		l.ListInsert(l.ListLength() + 1, i + 1);
	}
	print<int>(&l);
	l.homework_2_37();
	print<int>(&l);
	cin.get();
}
*/