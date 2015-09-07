#include"FkFingerKeyboard.h"
#include<Windows.h>
#define WINDOW_NAME "Program"
typedef enum{Type_A, Type_B} KeyboardType;
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
	exitKey.lock();
	timeScheduler.cancel();
	mainWorker.cancel();
	virtualKeyEvnetListener.cancel();

	virtualKeyEvnetListener.join();
	timeScheduler.join();
	mainWorker.join();
	
	camera.releaseCamera();
	delete this->paperKeyboard;
	delete this->timer;
	exitKey.unlock();
}