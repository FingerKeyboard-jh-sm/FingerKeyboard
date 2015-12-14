/**
* @file FkThread.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 분산 처리를 위한 FkThread 정의
*/
#ifndef FK_THREAD_
#define FK_THREAD_
#include<pthread.h>
class FkThread{
private:
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
	void cancel();
};
#endif