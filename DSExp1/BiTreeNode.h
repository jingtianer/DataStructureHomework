#ifndef MY_BI_TREE_NODE_H
#define MY_BI_TREE_NODE_H
#include "ADTTreeNode.h"
template<class T>
class BiTreeNode : public ADTTreeNode<T, BiTreeNode<T>> {
public:
	BiTreeNode() {
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	BiTreeNode(BiTreeNode<T>* parent, T e) {
		this->parent = parent;
		left = nullptr;
		right = nullptr;
		data = e;
	}
	T Value(){
		return data;
	}
	void Assign(const T& e) {
		data = e;
	}
	BiTreeNode<T>*& Left() {
		return Child(LEFT);
	}
	BiTreeNode<T>*& Right() {
		return Child(RIGHT);
	}
	BiTreeNode<T>*& Child(int degree){
		switch (degree) {
		case LEFT:
			return left;
			break;
		case RIGHT:
			return right;
			break;
		default:
			throw "InValid Degree";
			break;
		}
	}
	BiTreeNode<T>*& Parent() {
		return parent;
	}

	void DeleteChild(int degree) {
	}
	void InsertChild(BiTreeNode<T>* node, int degree) {
	}

public:
	BiTreeNode<T>* left;
	BiTreeNode<T>* right;
	BiTreeNode<T>* parent;
	T data;
public:
	static const int LEFT = 0;
	static const int RIGHT = 1;
};
#endif // !MY_BI_TREE_NODE_H
