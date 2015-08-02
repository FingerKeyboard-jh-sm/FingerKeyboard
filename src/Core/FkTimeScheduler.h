#ifndef Fk_TIME_
#define FK_TIME_
#include"FkThread.h"
#include"FkKey.h"
#include"FkCondition.h"
class FkTimeScheduler : public FkThread{
	FkCondition* timer;
public:
	FkTimeScheduler();
	void setTimer(FkCondition* timer);
	void run();
};
#endif