#ifndef FK_THREAD_
#define FK_THREAD_
#include<pthread.h>
class FkThread{
protected:
	pthread_t thread;
public:
	FkThread();
	virtual ~FkThread();
	virtual void run() = 0;
	static void* run_(void*);
	static void cleanUp_(void*);
	virtual void cleanUp() = 0;
	void start();
	void join();
	void exit();
	pthread_t getId();
};
#endif