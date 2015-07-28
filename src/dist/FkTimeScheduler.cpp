#include"FkTimeScheduler.h"
#include<opencv\cv.h>
#include<Windows.h>
#include<opencv\highgui.h>
FkTimeScheduler::FkTimeScheduler(){
	timer = key.newCondition();
}
FkCondition* FkTimeScheduler::getTimerCondition(){
	return timer;

}
void FkTimeScheduler::run(){
	while(1){
		timer->signal();
		cvWaitKey(1);
	}
}