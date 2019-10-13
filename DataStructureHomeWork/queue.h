#ifndef MY_QUEUE_H
#define MY_QUEUE_H
#include<functional>
#include"printable.h"

static const int QueueInitSize = 100;
static const int QueueIncreasement = 10;
template<class T>
class queue : public Printable<T> {
public:
	queue(){}
	~queue(){}
	virtual void InitQueue() = 0;
	virtual void DestoryQueue() = 0;
	virtual void ClearQueue() = 0;
	virtual bool QueueEmpty() = 0;
	virtual int QueueLength() = 0;
	virtual T GetHead() = 0;
	virtual void EnQueue(T e) = 0;
	virtual T DeQueue() = 0;
	virtual void QueueTraverse(std::function<void(T& e)> visit) = 0;
};
#endif // !MY_QUEUE_H
