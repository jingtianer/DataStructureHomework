#ifndef MY_LNODE_H
#define MY_LNODE_H
template <class U>
class LNode
{
public:
	U data;
	LNode<U>* next;

	LNode()
	{
		next = nullptr;
	}
};
#endif
