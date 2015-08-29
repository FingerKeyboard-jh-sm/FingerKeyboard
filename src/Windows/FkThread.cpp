#include"FkThread.h"
FkThread::FkThread(){

}
FkThread::~FkThread(){
	pthread_detach(this->thread);
}
void* FkThread::run_(void* thread){
	FkThread* pThread = (FkThread*)thread;
	pThread->run();
	return 0;
}
void FkThread::start(){
	pthread_create(&thread, NULL, &FkThread::run_, (void*)this);
}

void FkThread::exit(){
	pthread_cancel(this->thread);
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
}
void FkThread::join(){
	pthread_join(thread, NULL);
}
pthread_t FkThread::getId(){
	return pthread_self();
}