/**
* @file FkTimeScheduler.h
* @author �Ѽ����б� ��ǻ�Ͱ��а� ������(jinhuk1313@gmail.com)	
* @brief FkTimeScheduler Class ����
*/
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
	double timeQuantum;
	double startTime, endTime, runningTime;
	int overTimeCount;
	int frameCount;
#ifndef _WINDOWS
	FkConsoleMessage msg;
#else
	FkWindowsMessage msg;
#endif
public:
	int fps;
	FkTimeScheduler();
	void setTimer(FkCondition* timer);
	void setkey(FkKey* key);
	void run();
	void cleanUp();
	int calcWaitTime();

};
#endif