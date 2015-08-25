#include"FkTimeScheduler.h"
#include<opencv\cv.h>
#include<opencv\highgui.h>
FkTimeScheduler::FkTimeScheduler(){
	exitFlag = false;
}
void FkTimeScheduler::setTimer(FkCondition* timer){
	this->timer = timer;
}
FkTimeScheduler::~FkTimeScheduler(){

}
void FkTimeScheduler::run(){
	while(1){
		timer->signal();
	}
}
