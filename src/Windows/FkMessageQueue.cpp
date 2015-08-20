#include"FkMessageQueue.h"
#include<iostream>
FkMessageQueue::FkMessageQueue(){
	this->msgIn = key.newCondition();
	this->msgOut = key.newCondition();
}
void FkMessageQueue::enqueue(FkEventMessage msg){
	key.lock();
	queue.push_back(msg);
	msgIn->signal();
	key.unlock();
}
FkEventMessage FkMessageQueue::dequeue(){
	FkEventMessage msg;
	key.lock();
	if(queue.empty())
		msgIn->await();
	iterator = queue.begin();
	msg = *iterator;
	iterator = queue.erase(iterator);
	msgOut->signal();
	key.unlock();
	return msg;
}

