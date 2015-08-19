#include"FkThread.h"
#include<iostream>
FkThread::FkThread(){
	alive = false;
}
FkThread::~FkThread(){
	pthread_detach(this->thread);
}
bool FkThread::isAlive(){
	return this->alive;
}
void* FkThread::run_(void* thread){
	FkThread* pThread = (FkThread*)thread;
	if(pThread->isAlive())
		pThread->run();

	return 0;
}
void FkThread::start(){
	alive = true;
	pthread_create(&thread, NULL, &FkThread::run_, (void*)this);
}
void FkThread::join(){
	pthread_join(thread, NULL);
}
pthread_t FkThread::getId(){
	return pthread_self();
}