/**
* @file FkTimeScheduler.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 일정한 FPS 관리
*/
#include"FkTimeScheduler.h"
FkTimeScheduler::FkTimeScheduler(){
	this->timeQuantum = 0.033;
}
void FkTimeScheduler::setTimer(FkCondition* timer){
	this->timer = timer;
}
void FkTimeScheduler::setkey(FkKey* key){
	this->key = key;
}
int FkTimeScheduler::calcWaitTime(){
	runningTime = endTime - startTime;
	if(runningTime < timeQuantum)
		return (int)((timeQuantum - runningTime)*1000);
	return 0;
}
void FkTimeScheduler::run(){
	double endd;
	while(1){
		key->lock();
		timer->signal();
		startTime = (double)clock()/CLOCKS_PER_SEC;
		timer->await();
		key->unlock();
		endTime = (double)clock()/CLOCKS_PER_SEC;
#ifdef WIN32
		Sleep(calcWaitTime());
#else
		sleep(calcWaitTime());
#endif
		endd = (double)clock()/CLOCKS_PER_SEC;
		fps = 1.0/(endd-startTime);
	}
}
void FkTimeScheduler::cleanUp(){
	key->unlock(); 
	key->lock();
	timer->signal();
	key->unlock();
}
