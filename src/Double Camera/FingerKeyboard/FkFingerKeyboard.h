#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>


#ifndef FK_PROGRAM_
#define FK_PROGRAM_

#include"FkCamera.h"
#include"FkProgramState.h"
#include"FkMouserListener.h"
#include"FkImageProcessor.h"
#include"FkPreprocessor.h"
#include"FkPostprocessor.h"
#include "MmalDualCamera.h"

class FkFingerKeyboard{
	FkCamera camera;
	FkMouseListener mouseListener;
	FkPreprocessor preProcessor;
	FkPostprocessor postProcessor;
	FkImageProcessor imageProcessor;
	IplImage* dstImageTop;
	IplImage* dstImageBottom;
	FkMessage* message;
public:
	FkFingerKeyboard(int camIndexTop, int camIndexBottom, int keyboardType);
	void programRun();
	~FkFingerKeyboard();
};

#endif