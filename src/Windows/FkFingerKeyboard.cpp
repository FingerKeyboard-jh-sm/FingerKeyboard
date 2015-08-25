#include"FkFingerKeyboard.h"
#define WINDOW_NAME "Program"
typedef enum{Type_A, Type_B} KeyboardType;
//FkCondition* FkFingerKeyboard::timer;
FkFingerKeyboard::FkFingerKeyboard(int camIndex, int keyboardType) : camera(camIndex), mainWorker(keyboardType), virtualKeyEvnetListener(&messageQueue){
	timer = key.newCondition();
	timeScheduler.setTimer(timer);
	mainWorker.setCamera(camera);
	mainWorker.setTimer(timer);
	mainWorker.setKey(&exitKey);
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
	timeScheduler.start();
	mainWorker.start();
	virtualKeyEvnetListener.start();
}
FkFingerKeyboard::~FkFingerKeyboard(){
	cvDestroyAllWindows();
}
void FkFingerKeyboard::out(){
	exitKey.lock();
	mainWorker.exit();
	mainWorker.join();
	timeScheduler.exit();
	timeScheduler.join();
	virtualKeyEvnetListener.exit();
	//virtualKeyEvnetListener.join();
	camera.releaseCamera();
	delete this->paperKeyboard;
	delete this->timer;
	exitKey.unlock();

}