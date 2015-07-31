#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_PROGRAM_
#define FK_PROGRAM_
#include"FkCamera.h"
#include"FkProgramState.h"
#include"FkMouserListener.h"
#include"FkPreProcessor.h"
#include"FkPostProcessor.h"
#include"FkImageProcessor.h"
#include"FkThread.h"
#include"FkTimeScheduler.h"
void* programRun();
class FkFingerKeyboard : public FkThread{
	FkCamera camera;
	FkMouseListener mouseListener;
	FkPreprocessor preProcessor;
	FkPostProcessor postProcessor;
	FkImageProcessor imageProcessor;
	FkTimeScheduler timeScheduler;
	FkCondition* timer;
	FkMessage* message;
	IplImage* dstImage;	
public:
	FkFingerKeyboard(int camIndex, int keyboardType);
	bool isCameraSet();
	void run();
	void setTimer(FkCondition* condition);
	void setWindow();
	IplImage* getButtonImage();
	FkCamera& getCamera();
	~FkFingerKeyboard();
	friend void getBackgroundImage(IplImage* srcImage, IplImage* dstImage);
};
#endif