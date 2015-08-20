#include"FkFingerKeyboard.h"
#define WINDOW_NAME "Program"
typedef enum{Type_A, Type_B} KeyboardType;
FkFingerKeyboard::FkFingerKeyboard(int camIndex, int keyboardType) : camera(camIndex), mainWorker(keyboardType), virtualKeyEvnetListener(&messageQueue){
	timer = key.newCondition();
	timeScheduler.setTimer(timer);
	mainWorker.setCamera(camera);
	mainWorker.setTimer(timer);
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

	mainWorker.join();
	timeScheduler.exit();
	virtualKeyEvnetListener.exit();
	mainWorker.exit();
	camera.releaseCamera();
	delete this->paperKeyboard;
	delete this->timer;
}
FkFingerKeyboard::~FkFingerKeyboard(){
	/*timeScheduler.exit();
	virtualKeyEvnetListener.exit();
	mainWorker.exit();*/
	//camera.releaseCamera();
	//delete this->paperKeyboard;
	//delete this->timer;
}