#ifndef MY_TEST_SETTINGS_H
#define MY_TEST_SETTINGS_H
#include <iostream>
#include <fstream>
using namespace std;
/**
 * \brief 测试章节大类，注释掉想测试的章节，只能注释一个
 */
//#define NOT_TEST_LIST
#define NOT_TEST_STACK
/**
 * \brief 测试数据是否写入文件
 */
//#define WRITE_TO_FILE
/**
 * \brief 测试数据量（150较合理）
 */
const int TEST_SIZE = 150;

streambuf* coutBuf = nullptr;
ofstream * of = nullptr;
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
#endif
