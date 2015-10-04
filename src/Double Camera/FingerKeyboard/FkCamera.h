#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui.hpp>




#ifndef FK_CAM_
#define FK_CAM_
#ifdef _WINDOWS
//Camera property
#define PRE_BRIGHT 255
#define PRE_CONTRA 0
#define PRE_SATURA 255
#define PRE_EXPOSU -4
#define PRE_GAIN 1
#define PRE_WHITE 2150

#define POST_BRIGHT_TOP 120
#define POST_BRIGHT_BOTTOM 200
//#define POST_CONTRA 46 ¿øº»
//#define POST_SATURA 41 ¿øº»
#define POST_CONTRA 30 // ³·
#define POST_SATURA 70 // ³·
#define POST_EXPOSU -4
#define POST_GAIN 1
#define POST_WHITE 2150
#endif

class FkCamera{
	CvSize camResolution;	
	static CvCapture* camCaptureTop;
	static CvCapture* camCaptureBottom;
	#ifdef _WINDOWS
	int bright;
	int contra;
	int satura;
	int exposu;
	int gain;
	int white;
	#endif
public:
	FkCamera(int deviceIndexTop, int deviceIndexBottom);
	//bool isSettingCamera();
	CvSize getResolution();
	void setResolution();
	#ifdef _WINDOWS
	bool getQueryFrame(IplImage** dstImageTop, IplImage** dstImageBottom);
	void setCamera(int deviceIndexTop, int deviceIndexBottom);
	void setCameraPreprocessBottom();
	void setCameraPostprocessTop();
	void setCameraPostprocessBottom();
	void setInitProperty();
	static void setBrightness(int value);
	static void setContrast(int value);
	static void setSaturation(int value);
	static void setExposure(int value);
	static void setGain(int value);
	static void setWhiteBalance(int value);
	static void setBrightnessTop(int value);
	static void setContrastTop(int value);
	static void setSaturationTop(int value);
	int* getBright();
	int* getContra();
	int* getSatura();
	int* getExposu();
	int* getGain();
	int* getWhite();
	#endif
	~FkCamera();
};

#endif