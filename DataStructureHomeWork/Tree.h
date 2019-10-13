#ifndef MY_TREE_H
#define MY_TREE_H
#include"printable.h"
#include<string>
template<class T, class N>//T���������ͣ�N�ǽڵ�����
class Tree : public Printable<T> {//��ֻ�Ƕ�����,˳��洢���ڶ���������дint���൱��index
public:
	virtual void InitTree() = 0;
	virtual void DestoryTree() = 0;
	virtual void CreateTree(std::string definition) = 0;
	virtual void ClearTree() = 0;
	virtual bool TreeEmpty() = 0;
	virtual int TreeDepth() = 0;
	virtual N*& Root() = 0;//������ȡֵ����ȡ��/˫�׽ڵ㣬��ֵ��ȡֵ���ɽڵ�����ʵ��

	virtual N*& LeftSibling(N* node) = 0;
	virtual N*& RightSibling(N* node) = 0;//���ֻ�������������ڵ�����������Ϊ�ڵ㲻֪��˭������


	virtual void PreOrderTraverse(N* root, std::function<void(N* e)> visit) = 0;
	virtual void InOrderTraverse(N* root, std::function<void(N* e)> visit) = 0;
	virtual void PostOrderTraverse(N* root, std::function<void(N* e)> visit) = 0;
	virtual void LevelOrderTraverse(N* root, std::function<void(N* e)> visit) = 0;//�ĸ������ǹ����
};
#endif // !MY_TREE_H
