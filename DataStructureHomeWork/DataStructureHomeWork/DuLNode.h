#ifndef MY_DULNODE_H
#define MY_DULNODE_H
template<class U>
struct DuLNode
{
public:
	U data;
	DuLNode<U> * next;
	DuLNode<U> * prior;
	DuLNode(DuLNode<U> * prior)
	{
		next = nullptr;
		this->prior = prior;
	}
};
#endif
