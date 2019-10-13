#ifndef MY_SQ_QUEUE_H
#define MY_SQ_QUEUE_H
#include"queue.h"
template<class T>
class SqQueue : public queue<T> {
private:
	T* base;
	int front;
	int rear;
	int QueueSize;
public:
	SqQueue() {
		InitQueue();
	}
	~SqQueue() {
		DestoryQueue();
	}
	void InitQueue() {
		base = new T[QueueInitSize];
		if (!base) throw "init fail";
		front = rear = 0;
		QueueSize = QueueInitSize;
	}
	void DestoryQueue() {
		delete[] base;
		front = rear = 0;
		QueueSize = 0;
		base = nullptr;
	}
	void ClearQueue() {
		front = rear = 0;
	}
	bool QueueEmpty() {
		return front == rear;
	}
	int QueueLength() {
		return (front - rear + QueueSize) % QueueSize;
	}
	T GetHead() {
		return base[front];
	}
	void ReAlloc() {
		T* temp = new T[QueueSize + QueueIncreasement];
		if (!temp)
		{
			throw "realloc fail";
		}
		int i = front > rear ? 0 : front;
		while (i < rear)
		{
			temp[i] = base[i];
			i++;
		}
		if (front > rear)
		{
			i = QueueSize - 1;
			while (i >= front)
			{
				temp[i + QueueIncreasement] = base[i];
				i--;
			}
		}
		delete[] base;
		base = temp;
		QueueSize += QueueIncreasement;
	}
	void EnQueue(T e) {
		if ((rear + 1) % QueueSize == front) {
			ReAlloc();
		}
		base[rear] = e;
		rear = (rear + 1) % QueueSize;
	}
	T DeQueue() {
		if (front == rear) throw "empty queue";
		T e = base[front];
		front = (front + 1) % QueueSize;
		return e;
	}
	void printAll() {
		QueueTraverse(print_all<T>);
	}
	void QueueTraverse(std::function<void(T& e)> visit) {
		int i = 0;
		if (front > rear)
		{
			i = front;
			while (i <= QueueSize - 1)
			{
				visit(base[i]);
				i++;
			}
		}
		i = front > rear ? 0 : front;
		while (i < rear)
		{
			visit(base[i]);
			i++;
		}
	}
};
#endif // !MY_SQ_QUEUE_H
