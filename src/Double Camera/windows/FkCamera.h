#include<opencv\cv.h>
#include<opencv\highgui.h>

#ifndef FK_CAM_
#define FK_CAM_

//Camera property
#define ORG_BRIGHT 20
#define ORG_CONTRA 30
#define ORG_SATURA 70
#define ORG_EXPOSU -4
#define ORG_GAIN 1
#define ORG_WHITE 2150

#define PRE_BRIGHT 255
#define PRE_CONTRA 0
#define PRE_SATURA 255

#define POST_BRIGHT_TOP 120
#define POST_BRIGHT_BOTTOM 200
#define POST_CONTRA 30 // ³·
#define POST_SATURA 70 // ³·

class FkCamera{
	static CvCapture* camCaptureTop;
	static CvCapture* camCaptureBottom;
	CvSize camResolution;
	int bright;
	int contra;
	int satura;
	int exposu;
	int gain;
	int white;
public:
	FkCamera(int deviceIndexTop, int deviceIndexBottom);
	CvSize getResolution();
	bool getQueryFrame(IplImage** dstImageTop, IplImage** dstImageBottom);
	void setResolution();
	void setCamera(int deviceIndexTop, int deviceIndexBottom);
	void setCameraPreprocessBottom();
	void setCameraPostprocessTop();
	void setCameraPostprocessBottom();
	static void setBrightness(int value);
	static void setContrast(int value);
	static void setSaturation(int value);
	static void setExposure(int value);
	static void setGain(int value);
	static void setWhiteBalance(int value);
	~FkCamera();
};

#endif