#include<pthread.h>
#ifndef FK_THREAD_
#define FK_THREAD_
class FkThread{
protected:
	bool alive;
	pthread_t thread;
public:
	FkThread();
	virtual ~FkThread();
	virtual void run() = 0;
	static void* run_(void*);
	void start();
	void join();

	pthread_t getId();
	bool isAlive();
};
#endif