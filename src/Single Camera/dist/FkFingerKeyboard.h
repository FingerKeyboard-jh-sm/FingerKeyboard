#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_PROGRAM_
#define FK_PROGRAM_
#include"FkThread.h"
#include"FkCameraManager.h"
#include"FkTimeScheduler.h"
#include"FkImageBuffer.h"
#include"FkImageDisplayer.h"
#include"FkCamera.h"
class FkFingerKeyboard : public FkThread{
	FkTimeScheduler timeScheduler;
	FkCamera camera;
	FkCameraManager cameraManager;
	FkImageBuffer imageBuffer;
	FkImageDisplayer imageDisplayer;
public:
	FkFingerKeyboard(int camIndex, int keyboardType);
	void run();
};
#endif