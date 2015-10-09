/**
* @file FkKey.cpp
* @author �Ѽ����б� ��ǻ�Ͱ��а� ������(jinhuk1313@gmail.com)	
* @brief �л�ó���� ���� key 
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
