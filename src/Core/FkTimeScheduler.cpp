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
	std::cout<<"Time Scheduler's mutex key : "<<this->key<<std::endl;
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
		fps = 1/(endd-startTime);
		std::cout<<"fps : "<<fps<<std::endl;
	}
}
