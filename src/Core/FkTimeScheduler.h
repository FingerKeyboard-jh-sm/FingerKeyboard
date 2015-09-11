#ifndef Fk_TIME_
#define FK_TIME_
#include"FkThread.h"
#include"FkKey.h"
#include"FkCondition.h"
#include"FkMessage.h"
#include<time.h>
#include<iostream>
#ifndef WIN32
#include<unistd.h>
#endif
class FkTimeScheduler : public FkThread{
	FkCondition* timer;
	FkKey* key;
	double startTime, endTime, runningTime;
	int frameCount;
public:
	FkTimeScheduler();
	void setTimer(FkCondition* timer);
	void setkey(FkKey* key);
	void run();
	void cleanUp();
	int calcWaitTime();

};
#endif