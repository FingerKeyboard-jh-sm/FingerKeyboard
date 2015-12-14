/**
* @file FkCondition.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 조건 변수 정의
*/
#include<pthread.h>
#ifndef FK_CONDI_
#define FK_CONDI_
#include"FkKey.h"
class FkCondition{
	pthread_cond_t condition;
	pthread_mutex_t* mutex;
public:
	FkCondition(pthread_mutex_t* mutex);
	void await();
	void signal();
	void signalAll();
	~FkCondition();
};
#endif