#include"FkTimeScheduler.h"
#include<opencv\cv.h>
#include<opencv\highgui.h>
FkTimeScheduler::FkTimeScheduler(){
}
void FkTimeScheduler::setTimer(FkCondition* timer){
	this->timer = timer;
}

void FkTimeScheduler::run(){
	while(1){
		//std::cout<<i<<std::endl;
		timer->signal();
	}
}
