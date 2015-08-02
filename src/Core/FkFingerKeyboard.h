#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_PROGRAM_
#define FK_PROGRAM_
#include"FkCamera.h"
#include"FkThread.h"
#include"FkTimeScheduler.h"
#include"FkMainWorker.h"
#include"FkMessageQueue.h"
#include"FkMessage.h"
#include"FkKey.h"
#include"FkPaperKeyboard.h"
#include"FkVirtualKeyEventListener.h"
class FkFingerKeyboard : public FkThread{
	FkCamera camera;
	FkPaperKeyboard* paperKeyboard;
	FkTimeScheduler timeScheduler;
	FkMainWorker mainWorker;
	FkKey key;
	FkCondition* timer;
	//FkMessageQueue messageQueue;
	//FkVirtualKeyEventListener virtualKeyEvnetListener;
public:
	FkFingerKeyboard(int camIndex, int keyboardType);
	bool isCameraSet();
	void run();
	IplImage* getButtonImage();
	FkCamera& getCamera();
	~FkFingerKeyboard();
};
#endif