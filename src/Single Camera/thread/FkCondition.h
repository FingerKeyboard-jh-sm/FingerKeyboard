#include<pthread.h>
#include"FkKey.h"
#ifndef FK_CONDI_
#define FK_CONDI_
class FkCondition{
	pthread_cond_t condition;
	pthread_mutex_t* mutex;
public:
	FkCondition(pthread_mutex_t* mutex);
	void await();
	void signal();
	void signalAll();

};
#endif