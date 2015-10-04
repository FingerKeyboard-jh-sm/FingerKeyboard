#include"FkFingerKeyboard.h"

FkFingerKeyboard::FkFingerKeyboard(int camIndex, int keyboardType) : camera(camIndex), cameraManager(camera){
	cameraManager.setTimerCondition(timeScheduler.getTimerCondition());
	cameraManager.setBuffer(&imageBuffer);
	imageDisplayer.setBuffer(&imageBuffer);
}
void FkFingerKeyboard::run(){
	cameraManager.start();
	timeScheduler.start();
	imageDisplayer.start();
	cameraManager.join();
	timeScheduler.join();
	imageDisplayer.join();
}