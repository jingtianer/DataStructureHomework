#ifndef MY_STATIC_LNODE_H
#define MY_STATIC_LNODE_H

template<class T>
struct StaticLNode
{
public:
	T data;
	int cur;
	StaticLNode()
	{
		cur = -1;
	}
};
#endif
