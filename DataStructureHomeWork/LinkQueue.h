#ifndef MY_LINK_QUEUE
#define MY_LINK_QUEUE
#include"queue.h"
#include"LNode.h"
template<class T>
class LinkQueue : public queue<T>
{
	typedef LNode<T> QNode;
public:
	LinkQueue() {
		InitQueue();
	}
	~LinkQueue() {
		DestoryQueue();
	}
	void InitQueue() {
		head = new QNode();
		tail = head;
		if (!head)
		{
			throw "Init Fail";
		}
		length = 0;
	}
	void DestoryQueue() {
		QNode* temp = head->next;
		while (temp)
		{
			QNode* del = temp;
			temp = temp->next;
			delete temp;
		}
		delete head;
		head = nullptr;
		tail = nullptr;
		length = 0;
	}
	void ClearQueue() {
		QNode* temp = head->next;
		while (temp)
		{
			QNode* del = temp;
			temp = temp->next;
			delete del;
		}
		tail = head;
		length = 0;
		head->next = nullptr;
	}
	bool QueueEmpty() {
		return tail == head;
	}
	int QueueLength() {
		return length;
	}
	T GetHead() {
		return head->next->data;
	}
	void EnQueue(T e) {
		QNode* temp = new QNode();
		temp->data = e;
		tail->next = temp;
		tail = temp;//每次通过tail指针入队
		length++;
	}
	T DeQueue() {
		if (head->next == nullptr)
		{
			throw "empty queue";
		}
		T temp = head->next->data;
		QNode* del = head->next;
		head->next = del->next;
		//如果删除队尾的话，tail要指回head
		if (tail == del)
		{
			tail = head;
		}
		delete del;
		length--;
		return temp;
	}
	void QueueTraverse(std::function<void(T& e)> visit) {
		QNode* temp = head->next;
		while (temp)
		{
			visit(temp->data);
			temp = temp->next;
		}
	}
	void printAll() {
		QueueTraverse(print_all<T>);
	}
private:
	QNode* head;//队头,链表头，是头节点
	QNode* tail;//队尾
	int length;
};

#endif // !MY_LINK_QUEUE
