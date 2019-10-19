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
	printList<int>(&la);
	printList<int>(&lb);
	printList<int>(&lc);
	printList<int>(&ld);
	printList<int>(&le);
	printList<int>(&lf);
	printList<int>(&lg);
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

	printList<int>(&a);
	printList<int>(&b);
	LinkList<int> c = a.CatList_Link(&b);
	printList<int>(&c);
	printList<int>(&a);
	printList<int>(&b);
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
	printList<int>(&d);
	printList<int>(&g);
	printList<int>(&a);
	printList<int>(&b);
	printList<int>(&e);
	printList<int>(&f);
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
	printList<int>(l);
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
	printList<int>(l);
	try
	{
		cout << "insert to 0\n";
		l->ListInsert(0, 888);
	}
	catch (char const* s)
	{
		cout << s << endl;
	}
	printList<int>(l);
	try
	{
		cout << "insert to l.ListLength() + 2 = " << l->ListLength() + 2 << endl;
		l->ListInsert(l->ListLength() + 2, 888);
		printList<int>(l);
	}
	catch (char const* s)
	{
		cout << s << endl;
	}
	printList<int>(l);
	cout << "delete test" << endl;
	for (int i = 1; i < 10; i++)
	{
		cout << "----------" << "delete item in " << GIDTEST / i << "----------" << endl;
		try
		{
			int t = l->ListDelete(GIDTEST / i);
			cout << t << " deleted" << endl;
			printList<int>(l);
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
			printList<int>(l);
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
	printList<int>(l);
	cout << "isListEmpty ? : " << (l->ListEmpty() ? "true" : "false") << endl;

	cout << "insert back" << endl;

	for (int i = 0; i < GIDTEST; i++)
	{
		l->ListInsert(1, i);
	}
	printList<int>(l);
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
	printList<int>(l);
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

void GeneralTest(Stack<int>* s, std::function<void()> other)
{
	printStack<int>(s);
	for (int  i = 0; i < TEST_SIZE; i++)
	{
		s->Push(i);
		printStack(s);
		cout << "length = " << s->StackLength() << endl
		<< "isEmpty = " << (s->StackEmpty() ? "true" : "false") << endl;
	}
	s->ClearStack();
	printStack(s);
	for (int  i = 0; i < TEST_SIZE; i++)
	{
		s->Push(i);
	}
	printStack<int>(s);
	std::cout << "----------" << "push clear test" << "----------OK" <<endl;
	system("pause");
	while (!s->StackEmpty())
	{
		cout << "top == " << s->GetTop();
		int temp = s->Pop();
		cout << "\npop the top : " << temp << endl;
		printStack<int>(s);
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

#ifndef NOT_TEST_HOMEWORK_2_37
#include "DuLinkList.h"
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
	l.ClearList();
	for (int i = 0; i < 101; i++)
	{
		l.ListInsert(l.ListLength() + 1, i + 1);
	}
	print<int>(&l);
	l.homework_2_37();
	print<int>(&l);
	cin.get();
}
#endif // !NOT_TEST_HOMEWORK_2_3

#ifndef NOT_TEST_QUEUE
#include"LinkQueue.h"
#include"queue.h"
#include"SqQueue.h"
#include <time.h>
#define LINK_QUEUE
#define SQ_QUEUE_TEST
void GeneralEn_DeQueue(queue<int>* q) {
	for (int i = 0; i < TEST_SIZE; i++)
	{
		q->EnQueue(i);
	}
	print<int>(q);
	cout << "the top is " << q->GetHead() << endl;
	while (!q->QueueEmpty())
	{
		cout << "delete : " << q->DeQueue() << endl;
	}

	print<int>(q);
	for (int i = 0; i < TEST_SIZE; i++)
	{
		q->EnQueue(i);
	}
	print<int>(q);
	q->ClearQueue();
	print<int>(q);
}
void RandomEnDeQueue(queue<int>* q) 
{
	srand((int)time(NULL));
	int e;
	for (int i = 0; i < TEST_SIZE; i++) {
		switch ((int)rand() % 3)
		{
		case 0://控制dequeue的概率小一点
			try
			{
				
				cout << "DeQueue " << q->DeQueue() << endl;
			}
			catch (const char * e)
			{
				cout << e << endl;
			}
			break;
		default:
			e = (int)rand()%501 - 250;
			q->EnQueue(e);
			cout << "EnQueue " << e << endl;
			break;
		}
		print<int>(q);
	}
}
void GeneralTest(queue<int>* q, std::function<void()> others) {
	GeneralEn_DeQueue(q);
	RandomEnDeQueue(q);
	RandomEnDeQueue(q);
	if (others)
	{
		others();
	}
}
int main() {

#ifdef LINK_QUEUE
	LinkQueue<int> linkq;
	GeneralTest(&linkq, nullptr);
#endif // LINK_QUEUE
#ifdef SQ_QUEUE_TEST
	SqQueue<int> Sqq;
	GeneralTest(&Sqq, nullptr);
#endif // SqQueue
	return 0;
}
#endif // !NOT_TEST_QUEUE

#ifndef NOT_TEST_ARRAY
int main() {
	Array<int> arr(3, 5, 5, 5);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++) 
		{
			for (int k = 0; k < 5; k++)
			{
				arr.Assign(i + j + k, i, j, k);
			}	
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++) 
		{
			for (int k = 0; k < 5; k++)
			{
				int n=0;
				arr.Value(&n, i, j, k);
				cout << n << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
	return 0;
}
#endif // !NOT_TEST_ARRAY

#ifndef NOT_TEST_TREE

int main() {
	BiTreeHelper<int> tree;
	BiTreeNode<int> * root = tree.Root();
	BiTreeNode<int>* temp = root;
	root->Assign(-1);
	temp->Left() = new BiTreeNode<int>(temp, 1);
	temp->Right() = new BiTreeNode<int>(temp, 2);
	temp = temp->Left();
	temp->Left() = new BiTreeNode<int>(temp, 3);
	temp->Right() = new BiTreeNode<int>(temp, 4);
	temp = tree.Root()->Right();
	temp->Left() = new BiTreeNode<int>(temp, 5);
	temp->Right() = new BiTreeNode<int>(temp, 6);
	tree.PreOrderTraverse(BiTreeHelper<int>::print_all);
	cout << endl;
	tree.InOrderTraverse(BiTreeHelper<int>::print_all);
	cout << endl;
	tree.PostOrderTraverse(BiTreeHelper<int>::print_all);
	cout << "\nleft  " << tree.LeftSibling(root->Left())->Value();
	cout << "\nright " << tree.RightSibling(root->Left())->Value() << endl;

	cout << "clear all\n";
	tree.ClearTree();
	cout << "----------------------\n";

	root = tree.Root();
	temp = root;
	root->Assign(-1);
	temp->Left() = new BiTreeNode<int>(temp, 1);
	temp->Right() = new BiTreeNode<int>(temp, 2);
	temp = temp->Left();
	temp->Left() = new BiTreeNode<int>(temp, 3);
	temp->Right() = new BiTreeNode<int>(temp, 4);

	temp = tree.Root()->Right();
	temp->Left() = new BiTreeNode<int>(temp, 5);
	temp->Right() = new BiTreeNode<int>(temp, 6);
	tree.PreOrderTraverse(BiTreeHelper<int>::print_all);
	cout << endl;
	tree.InOrderTraverse(BiTreeHelper<int>::print_all);
	cout << endl;
	tree.PostOrderTraverse(BiTreeHelper<int>::print_all);
	cout << "\nleft  " << tree.LeftSibling(root->Left())->Value();
	cout << "\nright " << tree.RightSibling(root->Left())->Value() << endl;
	return 0;
}
#endif // !NOT_TEST_TREE

#ifndef NOT_TEST_STRING
void String_Test(const string& d, const string& s, const string& t) {
	cout << "在字符串 (" << d << ")\n"
		<< "把所有   (" << s << ")\n"
		<< "替换为   (" << t << ")" << endl;
	String myStr(d);
	myStr.Replace(s, t);
	cout << "result : " << myStr.StrCopy() << endl;
}
void String_Test() {
	string a = "abcdefghijkabcdefghijkabcdefghijkabcdefghijk", b = "def", c = "^_^";
	String_Test(a, b, c);
	a = "****^_^****"; b = "*"; c = "O_o";
	String_Test(a, b, c);
}
int main() {
	String_Test();
	return 0;
}
#endif // !NOT_TEST_STRING

