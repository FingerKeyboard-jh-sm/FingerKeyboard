#include<opencv\cv.h>
#include<opencv\highgui.h>
#include"FkCamera.h"
#include"FkProgramState.h"
#include"FkMouserListener.h"
#include"FkPreProcessor.h"
#include"FkPostProcessor.h"
#include"FkImageProcessor.h"
class FkFingerKeyboard{
	FkCamera camera;
	FkMouseListener mouseListener;
	FkPreprocessor preProcessor;
	FkPostProcessor postProcessor;
	FkImageProcessor imageProcessor;
	IplImage* dstImage;
	
public:
	FkFingerKeyboard(int camIndex, int keyboardType);
	bool isCameraSet();
	void programRun();
	~FkFingerKeyboard();
	friend void getBackgroundImage(IplImage* srcImage, IplImage* dstImage);
};
