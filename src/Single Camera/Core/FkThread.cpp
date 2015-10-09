/**
* @file FkThread.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 분산처리를 위한 쓰레드
*/
#include"FkThread.h"
FkThread::FkThread(){

}
FkThread::~FkThread(){
	//pthread_detach(this->thread);
}
void* FkThread::run_(void* thread){
	FkThread* pThread = (FkThread*)thread;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_cleanup_push(&FkThread::cleanUp_, thread);
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
	pthread_cancel(this->thread);
}
void FkThread::join(){
	pthread_join(thread, NULL);
}