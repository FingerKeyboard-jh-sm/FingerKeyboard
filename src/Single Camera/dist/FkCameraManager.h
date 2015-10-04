#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_CAM_MANA_
#define FK_CAM_MANA_
#include"FkThread.h"
#include"FkKey.h"
#include"FkCondition.h"
#include"FkImageBuffer.h"
#include"FkCamera.h"
#define CAM_WIDTH 640
#define CAM_HEIGHT 480

class FkCameraManager:public FkThread{
	FkCamera camera;
	FkCondition* timer; 
	FkImageBuffer* imageBuffer;
public:
	void run();
	FkCameraManager(FkCamera& camera);
	void setBuffer(FkImageBuffer* imageBuffer);
	void setTimerCondition(FkCondition* timer);
};
#endif