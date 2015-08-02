#include"FkMessageQueue.h"
FkMessageQueue::FkMessageQueue(){
	this->msgIn = key.newCondition();
	this->msgOut = key.newCondition();
}
void FkMessageQueue::enqueue(FkEventMessage msg){



}
FkEventMessage FkMessageQueue::dequeue(){
	FkEventMessage msg;

	return msg;
}

