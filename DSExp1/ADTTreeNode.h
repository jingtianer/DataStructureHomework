#ifndef MY_ADT_TREE_NODE_H
#define MY_ADT_TREE_NODE_H
template<class T, class N>
class ADTTreeNode{
public:
	virtual T Value() = 0;
	virtual void Assign(const T& e) = 0;
	virtual N*& Child(int degree) = 0;
	virtual N*& Parent() = 0;
	virtual void DeleteChild(int degree) = 0;
	virtual void InsertChild(N* node, int degree) = 0;
public:
	int Weight;
};
#endif // !MY_ADT_TREE_NODE_H
