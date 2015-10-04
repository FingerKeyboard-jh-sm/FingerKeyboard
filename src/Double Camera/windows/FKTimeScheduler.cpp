#include "FKTimeScheduler.h"

FKTimeScheduler::FKTimeScheduler() {
	this->startTime = 0;
	this->endTime = 0;
	this->runningTime = 0.0;
	this->fps = 0.0;
	cvInitFont(&fpsFont, CV_FONT_HERSHEY_COMPLEX_SMALL, 1.0, 1.0); 
}
void FKTimeScheduler::setStartTime() {
	this->startTime = GetTickCount();
}
void FKTimeScheduler::getFPS() {
	this->endTime = GetTickCount();
	if(endTime-startTime != 0 )
		runningTime = (double)(endTime-startTime)/1000;
	fps = 1.0/runningTime;
}
void FKTimeScheduler::printFPS(IplImage *dstImage) {
	gcvt(fps, 4, strBuffer);
	strBuffer[4] = ' ';
	strBuffer[5] = 'f';
	strBuffer[6] = 'p';
	strBuffer[7] = 's';
	strBuffer[8] = '\0';
	printf("%s\n", strBuffer);
	cvPutText(dstImage, strBuffer, cvPoint(10, 20), &fpsFont, CV_RGB(255, 255, 255)); 
}