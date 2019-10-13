#ifndef MY_TREE_H
#define MY_TREE_H
#include"printable.h"
#include<string>
template<class T, class N>//T是数据类型，N是节点类型
class Tree : public Printable<T> {//不只是二叉树,顺序存储，第二个参数就写int，相当于index
public:
	virtual void InitTree() = 0;
	virtual void DestoryTree() = 0;
	virtual void CreateTree(std::string definition) = 0;
	virtual void ClearTree() = 0;
	virtual bool TreeEmpty() = 0;
	virtual int TreeDepth() = 0;
	virtual N*& Root() = 0;//其他获取值，获取子/双亲节点，赋值，取值都由节点类型实现

	virtual N*& LeftSibling(N* node) = 0;
	virtual N*& RightSibling(N* node) = 0;//这个只能由树做到，节点做不到，因为节点不知道谁是树根


	virtual void PreOrderTraverse(N* root, std::function<void(N* e)> visit) = 0;
	virtual void InOrderTraverse(N* root, std::function<void(N* e)> visit) = 0;
	virtual void PostOrderTraverse(N* root, std::function<void(N* e)> visit) = 0;
	virtual void LevelOrderTraverse(N* root, std::function<void(N* e)> visit) = 0;//四个遍历是广义的
};
#endif // !MY_TREE_H
