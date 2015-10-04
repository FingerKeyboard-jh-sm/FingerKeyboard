#include<opencv\cv.h>
#include<opencv\highgui.h>

#ifndef FK_PROGRAM_
#define FK_PROGRAM_

#include"FkCamera.h"
#include"FkProgramState.h"
#include"FkMouserListener.h"
#include"FkImageProcessor.h"
#include"FkPreprocessor.h"
#include"FkPostprocessor.h"
#include"FKTimeScheduler.h"

class FkFingerKeyboard{
	FkMouseListener mouseListener;
	FkPostprocessor postProcessor;
	FkImageProcessor imageProcessor;
	IplImage* dstImageTop;
	IplImage* dstImageBottom;
	FkMessage* message;
	FKTimeScheduler timeScheduler;
public:
	FkCamera camera;
	FkPreprocessor preProcessor;
	FkFingerKeyboard(int camIndexTop, int camIndexBottom, int keyboardType);
	bool isCameraSet();
	void programRun();
	~FkFingerKeyboard();
};

#endif