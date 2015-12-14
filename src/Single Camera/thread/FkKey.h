/**
* @file FkKey.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 분산처리를 위한 Key Class 정의 
*/
#include<pthread.h>
#ifndef FK_KEY_
#define FK_KEY_
#include"FkCondition.h"
class FkCondition;
class FkKey{
	pthread_mutex_t mutex;
public:
	FkKey();
	~FkKey();
	void lock();
	void unlock();
	FkCondition* newCondition();
};
#endif