/**
* @file FkKey.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 분산처리를 위한 key 
*/
#include"FkKey.h"
FkKey::FkKey(){
	pthread_mutex_init(&mutex, NULL);
}
FkKey::~FkKey(){
	pthread_mutex_destroy(&mutex);
}

void FkKey::lock(){
	pthread_mutex_lock(&mutex);
}
void FkKey::unlock(){
	pthread_mutex_unlock(&mutex);
}
FkCondition* FkKey::newCondition(){
	return new FkCondition(&mutex);
}
