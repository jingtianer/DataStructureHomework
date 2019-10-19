#ifndef MY_TEST_SETTINGS_H
#define MY_TEST_SETTINGS_H
#include <iostream>
#include <fstream>
#include "SqList.h"
#include "LinkList.h"
#include "CycleLinkList.h"
#include "DuLinkList.h"
#include "StaticLinkList.h"
#include "SqStack.h"
#include<sstream>
#include<functional>
#include"printable.h"
#include"queue.h"
#include"SqQueue.h"
#include"LinkQueue.h"
#include"TriMatrix.h"
#include"String.h"

using namespace std;
streambuf* coutBuf = nullptr;
ofstream* of = nullptr;
const int TEST_SIZE = 500;
#define NOT_TEST_LIST
#define NOT_TEST_STACK
#define NOT_TEST_HOMEWORK_2_37
//#define NOT_TEST_QUEUE
void WriteToFile()
{
	coutBuf = cout.rdbuf();
	of = new ofstream("out.txt");
	// 获取文件out.txt流缓冲区指针
	streambuf* fileBuf = of->rdbuf();
	// 设置cout流缓冲区指针为out.txt的流缓冲区指针
	cout.rdbuf(fileBuf);
}
void RecoverCOUT()
{
	of->flush();
	of->close();
	cout.flush();
	cout.rdbuf(coutBuf);
	system("out.txt");
}

template<class T>
void print(Printable<T>* l) {
	cout << "begin :{\n";
	l->printAll();
	cout << "\n}\n";
}
#endif
