#include"FkThread.h"
FkKey FkThread::cleanUpKey;
FkThread::FkThread(){

}
FkThread::~FkThread(){
	//pthread_detach(this->thread);
}
void* FkThread::run_(void* thread){
	FkThread* pThread = (FkThread*)thread;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	//cleanUpKey.lock();
	pthread_cleanup_push(&FkThread::cleanUp_, thread);
	//cleanUpKey.unlock();
	pThread->run();
	pthread_cleanup_pop(0);
	return 0;
}
void FkThread::cleanUp_(void* thread){
	FkThread* pThread = (FkThread*)thread;
	pThread->cleanUp();
}
void FkThread::start(){
	pthread_create(&thread, NULL, &FkThread::run_, (void*)this);
}

void FkThread::cancel(){
	cleanUpKey.unlock();
	pthread_cancel(this->thread);
}
void FkThread::join(){
	pthread_join(thread, NULL);
}
pthread_t FkThread::getId(){
	return pthread_self();
}