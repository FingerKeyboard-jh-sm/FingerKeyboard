#include"FkCameraManager.h"
FkCameraManager::FkCameraManager(FkCamera& camera){
	this->camera = camera;
}
void FkCameraManager::setBuffer(FkImageBuffer* imageBuffer){
	this->imageBuffer = imageBuffer;
}
void FkCameraManager::setTimerCondition(FkCondition* timer){
	this->timer = timer;
}
void FkCameraManager::run(){
	IplImage* frame;
	while(1){
		timer->await();
		frame = camera.getQueryFrame();
		if(!frame)
			continue;
		imageBuffer->inFrame(frame);
	}
}