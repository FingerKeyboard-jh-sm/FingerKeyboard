#ifndef Fk_TIME_
#define FK_TIME_
#include"FkThread.h"
#include"FkKey.h"
#include"FkCondition.h"
class FkTimeScheduler : public FkThread{
	FkKey key;
	FkCondition* timer;
public:
	FkTimeScheduler();
	FkCondition* getTimerCondition();
	void run();
};
#endif