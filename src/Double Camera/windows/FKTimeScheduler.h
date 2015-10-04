#include<opencv\cv.h>
#include<opencv\highgui.h>

#include<Windows.h>

#ifndef FK_FRAME_MANAGER_
#define FK_FRAME_MANAGER_

#define MAX_STR_BUFFER_SIZE 64

class FKTimeScheduler {
	int startTime;
	int endTime;
	double runningTime;
	CvFont fpsFont;
	char strBuffer[MAX_STR_BUFFER_SIZE];
	double fps;
	
public:
	
	FKTimeScheduler();
	void setStartTime();
	void getFPS();
	void printFPS(IplImage *dstImage);
};

#endif