#include"FkFingerKeyboard.h"
FkFingerKeyboard::FkFingerKeyboard(int camIndex, int keyboardType) : camera(camIndex), mainWorker(keyboardType), virtualKeyEvnetListener(&messageQueue){
	timer = key.newCondition();
	timeScheduler.setTimer(timer);
	timeScheduler.setkey(&key);
	
	mainWorker.setTimer(timer);
	mainWorker.setKey(&key);
	mainWorker.setExitKey(&exitKey);
	mainWorker.setCamera(camera);
	switch(keyboardType){
	case Type_A:
		paperKeyboard = new FkPaperKeyboard_TypeA(&messageQueue);
		break;
	case Type_B:
		//create keyboard
		break;
	}
	mainWorker.setPaperKeyboardType(paperKeyboard);

}
bool FkFingerKeyboard::isCameraSet(){
	if(camera.isSettingCamera())
		return true;
	else
		return false;
}
FkCamera& FkFingerKeyboard::getCamera(){
	return this->camera;
}
IplImage* FkFingerKeyboard::getButtonImage(){
	return this->mainWorker.getButtonImage();
}
int FkFingerKeyboard::getFPS(){
	return timeScheduler.fps;
}
void FkFingerKeyboard::run(){
	virtualKeyEvnetListener.start();
	timeScheduler.start();
	mainWorker.start();
	
#ifndef _WINDOWS
	mainWorker.join();
	out();
#endif
}
FkFingerKeyboard::~FkFingerKeyboard(){
	cvDestroyAllWindows();
#ifndef _WINDOWS

#endif
}
void FkFingerKeyboard::cleanUp(){
	
}
void FkFingerKeyboard::out(){
	timeScheduler.cancel();
	exitKey.lock();
	mainWorker.cancel();
	exitKey.unlock();
	virtualKeyEvnetListener.cancel();
	
	virtualKeyEvnetListener.join();
	timeScheduler.join();
	mainWorker.join();
	
	camera.releaseCamera();
	delete this->paperKeyboard;
	delete this->timer;
	FkCurrentMode::state = SET_KB_REGION;
}