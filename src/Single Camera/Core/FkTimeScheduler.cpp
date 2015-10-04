#include"FkTimeScheduler.h"
//#define TIMEQUANTUM 0.033
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
		std::cout<<"fps : "<<fps<<std::endl;
	}
}
void FkTimeScheduler::cleanUp(){
	key->unlock(); 
	key->lock();
	timer->signal();
	key->unlock();
}
