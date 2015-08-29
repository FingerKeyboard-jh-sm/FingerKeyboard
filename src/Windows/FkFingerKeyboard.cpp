#include"FkFingerKeyboard.h"
#define WINDOW_NAME "Program"
typedef enum{Type_A, Type_B} KeyboardType;
FkFingerKeyboard::FkFingerKeyboard(int camIndex, int keyboardType) : camera(camIndex), mainWorker(keyboardType), virtualKeyEvnetListener(&messageQueue){
	timer = key.newCondition();
	startCondition = key.newCondition();
	timeScheduler.setTimer(timer);
	timeScheduler.setkey(&key);
	timeScheduler.setStartCondition(startCondition);
	
	mainWorker.setTimer(timer);
	mainWorker.setKey(&key);
	mainWorker.setStartCondition(startCondition);
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
	mainWorker.start();
	timeScheduler.start();
	virtualKeyEvnetListener.start();
	
#ifndef _WINDOWS
	mainWorker.join();
	timeScheduler.exit();
	timeScheduler.join();
	virtualKeyEvnetListener.exit();
	virtualKeyEvnetListener.join();
#endif
}
FkFingerKeyboard::~FkFingerKeyboard(){
	cvDestroyAllWindows();
#ifndef _WINDOWS
	camera.releaseCamera();
	delete this->paperKeyboard;
	delete this->timer;
	delete this->startCondition;
#endif
}
void FkFingerKeyboard::out(){
	exitKey.lock();
	mainWorker.exit();
	mainWorker.join();
	timeScheduler.exit();
	timeScheduler.join();
	virtualKeyEvnetListener.exit();
	virtualKeyEvnetListener.join();
	camera.releaseCamera();
	delete this->paperKeyboard;
	delete this->timer;
	delete this->startCondition;
	exitKey.unlock();
}