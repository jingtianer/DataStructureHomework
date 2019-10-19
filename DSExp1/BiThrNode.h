#ifndef MY_BI_THR_NODT
#define MY_BI_THR_NODT
#include"ADTTreeNode.h"
template<class T>
class BiThrTreeNode : public ADTTreeNode<T, BiThrTreeNode<T>> {
private:
	typedef BiThrTreeNode<T> N;
public:
	BiThrTreeNode() {
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		LTag = Child;
		RTag = Child;
	}
	BiThrTreeNode(N* parent) {
		left = nullptr;
		right = nullptr;
		LTag = Child;
		RTag = Child;
		this->parent = parent;
	}
	T Value(){
		return data;
	}
	void Assign(T e){
		data = e;
	}
	N*& Child(int degree){
		switch (degree)
		{
		case LEFT:
			if(LTag == Child)
				return left;
			break;
		case RIGHT:
			if(RTag == Child)
				return right;
			break;
		default:
			throw "Error";
			break;
		}
		throw "NotChild";
	}
	N*& Parent(){
		return parent;
	}
	void DeleteChild(int degree){}
	void InsertChild(N* node, int degree){}
private:
	T data;
	bool LTag;
	bool RTag;
	N* left;
	N* right;
	N* parent;
private:
	static const int LEFT = 0;
	static const int RIGHT = 1;
	static const bool Thread = false;
	static const bool Child = true;
};
#endif // !MY_BI_THR_NODT
