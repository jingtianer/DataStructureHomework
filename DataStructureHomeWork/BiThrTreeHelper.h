#ifndef MY_BI_THR_TREE_HELPER
#define MY_BI_THR_TREE_HELPER
#include"Tree.h"
#include"BiThrNode.h"
template<class T>
class BiTheTreeHelper : Tree<T, BiThrTreeNode<T>> {
private:
	typedef BiThrTreeNode<T> N;
public:
	BiTheTreeHelper() {
		InitTree();
	}
	~BiTheTreeHelper{
		DestoryTree();
	}
	void InitTree(){
		root = new N;
		if (!root)
		{
			throw "alloc fail";
		}
	}
	void DestoryTree() {
		ClearTree();
		DeleteNode(root);
	}
	void CreateTree(std::string definition) {
	}
	void ClearTree() {
		PostOrderTraverse(DeleteNode);
		this->root->Child(BiThrTreeNode<T>::LEFT) = nullptr;
		this->root->Child(BiThrTreeNode<T>::RIGHT) = nullptr;
	}
	bool TreeEmpty() {
		return root->Left() == nullptr;
	}
	int TreeDepth() {
		throw "notImplement";
	}
	N*& Root(){
		if (root->Left() == nullptr) {
			root->Left() = new BiTreeNode<T>(root, 0);
		}
		return root->Left();
	}

	Node*& LeftSibling(Node* node) {
		return node->Parent()->Child(BiTreeNode<T>::LEFT);
	}
	Node*& RightSibling(Node* node) {
		return node->Parent()->Child(BiTreeNode<T>::RIGHT);
	}


	void PreOrderTraverse(std::function<void(N* e)> visit) {
		PreOrderTraverse(root->Left(), visit);
	}
	void InOrderTraverse(std::function<void(N* e)> visit) {
		InOrderTraverse(root->Left(), visit);
	}
	void PostOrderTraverse(std::function<void(N* e)> visit) {
		PostOrderTraverse(root->Left(), visit);
	}
	void LevelOrderTraverse(std::function<void(N* e)> visit) {}//四个遍历是广义的

	void PreOrderTraverse(N* root, std::function<void(N* e)> visit){}
	void InOrderTraverse(N* root, std::function<void(N* e)> visit){}
	void PostOrderTraverse(N* root, std::function<void(N* e)> visit){}
	void LevelOrderTraverse(N* root, std::function<void(N* e)> visit){}//四个遍历是广义的
private:
	N* root;
};
#endif // !MY_BI_THR_TREE_HELPER
