/**
* @file FkMessageQueue.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 이벤트 메시지가 전달되는 공유 저장소. 
*/
#include"FkMessageQueue.h"
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

