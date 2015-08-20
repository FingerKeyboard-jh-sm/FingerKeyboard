#include<opencv\cv.h>
#include<opencv\highgui.h>

#ifndef FK_CAM_
#define FK_CAM_

//Camera property
#define INIT_BRIGHT 160
#define INIT_CONTRA 29
#define INIT_SATURA 34
#define INIT_EXPOSU -4
#define INIT_GAIN 100
#define INIT_WHITE 6820
#define CAM_WIDTH 640
#define CAM_HEIGHT 480

class FkCamera{
	CvCapture* camCapture;
	CvSize camResolution;
public:
	FkCamera();
	FkCamera(int deviceIndex);
	FkCamera(char* fileName);
	bool isSettingCamera();
	CvSize getResolution();
	IplImage* getQueryFrame();
	void setResolution(int width, int height);
	void setCamera(int deviceIndex);
	void setVideo(char* fileName);
	void setInitProperty();
	void setBrightness(int value);
	void setContrast(int value);
	void setSaturation(int value);
	void setExposure(int value);
	void setWhiteBalance(int value);
	void setGain(int value);
	void releaseCamera();
};
#endif