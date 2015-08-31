#ifndef Fk_TIME_
#define FK_TIME_
#include"FkThread.h"
#include"FkKey.h"
#include"FkCondition.h"
#include<time.h>
#include<iostream>
class FkTimeScheduler : public FkThread{
	FkCondition* timer;
	FkCondition* startCondition;
	FkKey* key;
	double startTime, endTime, runningTime;
	int frameCount;
public:
	FkTimeScheduler();
	void setTimer(FkCondition* timer);
	void setkey(FkKey* key);
	void setStartCondition(FkCondition* startCondition);
	void run();
	int calcWaitTime();

};
#endif