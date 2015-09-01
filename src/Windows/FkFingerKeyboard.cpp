#include"FkFingerKeyboard.h"
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
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
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
	FkWindowsMessage msg;
	key.lock();

	virtualKeyEvnetListener.exit();
	mainWorker.exit();
	timeScheduler.exit();
	

	virtualKeyEvnetListener.join();
	//msg.showMessage("1");
	mainWorker.join();
	//msg.showMessage("2");
	//msg.showMessage("3");
	timeScheduler.join();
	//msg.showMessage("4");
	
	camera.releaseCamera();
	delete this->paperKeyboard;
	delete this->timer;
	key.unlock();
}