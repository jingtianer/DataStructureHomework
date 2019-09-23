#ifndef MY_SNODE_H
#define MY_SNODE_H
template<class T>
class  SNode
{
public:
	T data;
	SNode<T> * next;
	SNode<T> * prior;
	SNode(SNode<T> * prior)
	{
		this->prior = prior;
		next = nullptr;
	}
	SNode(T e,SNode<T> * prior)
	{
		this->data = e;
		this->prior = prior;
		next = nullptr;
	}
};
#endif
