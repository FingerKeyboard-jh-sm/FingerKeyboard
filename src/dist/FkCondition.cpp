#include"FkCondition.h"
FkCondition::FkCondition(pthread_mutex_t *mutex){
	pthread_cond_init(&condition, NULL);
	this->mutex = mutex;
}
void FkCondition::await(){
	pthread_cond_wait(&condition,mutex);
}
void FkCondition::signal(){
	pthread_cond_signal(&condition);
}
void FkCondition::signalAll(){
	pthread_cond_broadcast(&condition);
}
