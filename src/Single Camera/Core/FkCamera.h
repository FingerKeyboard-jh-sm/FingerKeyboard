/**
* @file FkCamera.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 카메라 클래스 정의
*/
#ifdef WIN32
#include<opencv\cv.h>
#include<opencv\highgui.h>
#else
#include<cv.h>
#include<highgui.h>
#endif


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