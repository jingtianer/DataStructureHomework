#ifndef MY_BI_TREE_HELPER_H
#define MY_BI_TREE_HELPER_H
#include"Tree.h"
#include"BiTreeNode.h"
#include<stack>
#include<sstream>
template<class T> 
class BiTreeHelper : public Tree<T, BiTreeNode<T>> {
private:
	typedef BiTreeNode<T> Node;
	typedef BiTreeNode<T> N;
public :
	BiTreeHelper() {
		InitTree();
	}
	BiTreeHelper(N* root) {
		InitTree();
		this.root->Left() = root;
	}
	~BiTreeHelper() {
		DestoryTree();
	}
	void InitTree() {
		root = new Node(nullptr, 0);
	}
	void DestoryTree() {
		ClearTree();
		DeleteNode(root);
	}
	void CreateTree(std::string definition){
	}
	void ClearTree() { 
		PostOrderTraverse(DeleteNode);
		this->root->Child(BiTreeNode<T>::LEFT) = nullptr;
		this->root->Child(BiTreeNode<T>::RIGHT) = nullptr;
	}
	bool TreeEmpty(){
		return root->Left() == nullptr;
	}
	int TreeDepth(){
		throw "notImplement";
	}

	Node*& LeftSibling(Node* node){
		return node->Parent()->Child(BiTreeNode<T>::LEFT);
	}
	Node*& RightSibling(Node* node){
		return node->Parent()->Child(BiTreeNode<T>::RIGHT);
	}
	

	void PreOrderTraverse(std::function<void(N* e)> visit){
		PreOrderTraverse(root->Left(), visit);
	}
	void InOrderTraverse(std::function<void(N* e)> visit){
		InOrderTraverse(root->Left(), visit);
	}
	void PostOrderTraverse(std::function<void(N* e)> visit){
		PostOrderTraverse(root->Left(), visit);
	}
	void LevelOrderTraverse(std::function<void(N* e)> visit) {}//四个遍历是广义的

	void PreOrderTraverse(N* root, std::function<void(N* e)> visit) {
		if (root == nullptr) {
			return;
		}
		stack<N*> sta;
		sta.push(root);
		while (!sta.empty()) {
			N* node = sta.top();
			sta.pop();
			visit(node);
			if (node->Right() != nullptr) {
				sta.push(node->Right());
			}
			if (node->Left() != nullptr) {
				sta.push(node->Left());
			}
		}
	}
	void InOrderTraverse(N* root, std::function<void(N* e)> visit) {
		stack<N*> sta;
		N* p = root;
		while (p || !sta.empty()) {
			if (p) {
				sta.push(p);
				p = p->Left();
			}
			else {
				p = sta.top();
				sta.pop();
				visit(p);
				p = p->Right();
			}
		}
	}
	void PostOrderTraverse(N* root, std::function<void(N* e)> visit) {
		if (root == nullptr) return;
		stack<N*> sta;
		N* cur = root;
		N* last = nullptr;

		while (cur != nullptr || !sta.empty()) {
			while (cur != nullptr) {
				sta.push(cur);
				cur = cur->Left();
			}
			cur = sta.top();
			if (cur->Right() == nullptr || cur->Right() == last) {
				visit(cur);
				sta.pop();
				last = cur;
				cur = nullptr;
			}
			else {
				cur = cur->Right();
			}
		}
	}
	void LevelOrderTraverse(N* root, std::function<void(N* e)> visit) {
		throw "notImplement";
	}//四个遍历是广义的
	//printAll实现画出一棵树
	void printAll() {
		throw "notImplement";
	}
	N*& Root() {
		if (root->Left() == nullptr) {
			root->Left() = new BiTreeNode<T>(root, 0);
		}
		return root->Left();
	}

	static void print_all(N* e) {
		cout << e->Value() << " ";
	}
	static void DeleteNode(N* node) {
		delete node;
	}
private:
	BiTreeNode<T>* root;
	
};
#endif // !MY_BI_TREE_H
