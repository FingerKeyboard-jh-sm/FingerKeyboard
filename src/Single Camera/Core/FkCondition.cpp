/**
* @file FkCondition.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 조건 변수 
*/
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
FkCondition::~FkCondition(){
	pthread_cond_destroy(&condition);
}