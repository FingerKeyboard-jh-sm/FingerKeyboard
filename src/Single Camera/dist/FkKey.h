#include<pthread.h>
#ifndef FK_KEY_
#define FK_KEY_
#include"FkCondition.h"
class FkCondition;
class FkKey{
	pthread_mutex_t mutex;
public:
	FkKey();
	void lock();
	void unlock();
	FkCondition* newCondition();
};
#endif