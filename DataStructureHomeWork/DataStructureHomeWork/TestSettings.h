#ifndef MY_TEST_SETTINGS_H
#define MY_TEST_SETTINGS_H
#include <iostream>
#include <fstream>
using namespace std;
/**
 * \brief �����½ڴ��࣬ע�͵�����Ե��½ڣ�ֻ��ע��һ��
 */
//#define NOT_TEST_LIST
#define NOT_TEST_STACK
/**
 * \brief ���������Ƿ�д���ļ�
 */
//#define WRITE_TO_FILE
/**
 * \brief ������������150�Ϻ���
 */
const int TEST_SIZE = 150;

streambuf* coutBuf = nullptr;
ofstream * of = nullptr;
void WriteToFile()
{
	coutBuf = cout.rdbuf();
	of = new ofstream("out.txt");
	// ��ȡ�ļ�out.txt��������ָ��
	streambuf* fileBuf = of->rdbuf();
	// ����cout��������ָ��Ϊout.txt����������ָ��
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
