#include"FkCondition.h"
#include<iostream>
FkCondition::FkCondition(pthread_mutex_t *mutex){
	pthread_cond_init(&condition, NULL);
	this->mutex = mutex;
}
void FkCondition::await(){
	pthread_cond_wait(&condition,mutex);
}
int FkCondition::timeWait(){
	struct timespec time;
	time.tv_sec = 9999;
	return pthread_cond_timedwait(&condition, mutex, &time); 
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