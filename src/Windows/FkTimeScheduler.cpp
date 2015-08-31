#include"FkTimeScheduler.h"
#define TIMEQUANTUM 0.033
#ifdef WIN32
#include<Windows.h>
#else
#include<unistd.h>
#endif
FkTimeScheduler::FkTimeScheduler(){
	
}
void FkTimeScheduler::setTimer(FkCondition* timer){
	this->timer = timer;
}
void FkTimeScheduler::setkey(FkKey* key){
	this->key = key;
}

void FkTimeScheduler::setStartCondition(FkCondition* startCondition){
	this->startCondition = startCondition;
}
int FkTimeScheduler::calcWaitTime(){
	runningTime = endTime - startTime;
	if(runningTime < TIMEQUANTUM)
		return (int)((TIMEQUANTUM - runningTime)*1000);
	return 0;
}
void FkTimeScheduler::run(){
	double endd;
	int fps;
	while(1){
		timer->signal();
		startTime = (double)clock()/CLOCKS_PER_SEC;
		key->lock();
		startCondition->await();
		key->unlock();
		endTime = (double)clock()/CLOCKS_PER_SEC;
#ifdef WIN32
		Sleep(calcWaitTime());
#else
		sleep(calcWaitTime());
#endif
		endd = (double)clock()/CLOCKS_PER_SEC;
		fps = 1/(endd-startTime);
		//std::cout<<"fps : "<<fps<<std::endl;
	}
}
