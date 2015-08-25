#include"FkCondition.h"
#include"FkMessage.h"
#include<iostream>
FkCondition::FkCondition(pthread_mutex_t *mutex){
	pthread_cond_init(&condition, NULL);
	this->mutex = mutex;
}
void FkCondition::await(){
	pthread_cond_wait(&condition,mutex);
}
void FkCondition::timeWait(){
	struct timespec time;
	FkWindowsMessage msg;
	time.tv_sec =40;
	time.tv_nsec = 4*1000;
	pthread_cond_timedwait(&condition, mutex, &time);

}
void FkCondition::signal(){
	pthread_cond_signal(&condition);
}
void FkCondition::signalAll(){
	pthread_cond_broadcast(&condition);
}
FkCondition::~FkCondition(){
	pthread_cond_destroy(&condition);
}