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
	void timeWait();
	void signal();
	void signalAll();
	~FkCondition();
};
#endif