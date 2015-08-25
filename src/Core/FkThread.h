#ifndef FK_THREAD_
#define FK_THREAD_
#include<pthread.h>
class FkThread{
protected:
	//bool alive;
	pthread_t thread;
public:
	FkThread();
	virtual ~FkThread();
	virtual void run() = 0;
	static void* run_(void*);
	void start();
	void join();
	void exit();
	pthread_t getId();
};
#endif