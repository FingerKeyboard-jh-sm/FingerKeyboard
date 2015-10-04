#include"FkCamera.h"
CvCapture* FkCamera::camCaptureTop;
CvCapture* FkCamera::camCaptureBottom;
FkCamera::FkCamera(int deviceIndexTop, int deviceIndexBottom){
	//카메라 설정
	setCamera(deviceIndexTop, deviceIndexBottom);
	//해상도 설정
	setResolution();	
}

void FkCamera::setBrightness(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_BRIGHTNESS, value);
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_BRIGHTNESS, value);
}
void FkCamera::setContrast(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_CONTRAST, value);
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_CONTRAST, value);
}
void FkCamera::setSaturation(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_SATURATION, value);
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_SATURATION, value);
}
void FkCamera::setGain(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_GAIN, value);
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_GAIN, value);
}
void FkCamera::setExposure(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_EXPOSURE, value);
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_EXPOSURE, value);
}
void FkCamera::setWhiteBalance(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_WHITE_BALANCE_U, value);
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_WHITE_BALANCE_U, value);
}
void FkCamera::setResolution(){
	int width = (int)cvGetCaptureProperty(camCaptureTop, CV_CAP_PROP_FRAME_WIDTH);
	int height = (int)cvGetCaptureProperty(camCaptureTop, CV_CAP_PROP_FRAME_HEIGHT);
	
	camResolution = cvSize(width, height);
}

CvSize FkCamera::getResolution(){
	camResolution = cvSize(640, 480);
	return camResolution;
}

//카메라 deviceIndex = -1  :: 카메라 없음
//카메라 deviceIndex = 0  :: 내부 카메라 
//카메라 deviceIndex = 1  :: 외부 카메라

void FkCamera::setCamera(int deviceIndexTop, int deviceIndexBottom){
	this->camCaptureTop = cvCaptureFromCAM(deviceIndexTop);
	this->camCaptureBottom = cvCaptureFromCAM(deviceIndexBottom);
}
void FkCamera::setCameraPostprocessTop(){
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_BRIGHTNESS, POST_BRIGHT_TOP);
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_CONTRAST, POST_CONTRA);
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_SATURATION, POST_SATURA);
}
void FkCamera::setCameraPreprocessBottom(){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_BRIGHTNESS, PRE_BRIGHT);
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_CONTRAST, PRE_CONTRA);
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_SATURATION, PRE_SATURA);
}
void FkCamera::setCameraPostprocessBottom(){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_BRIGHTNESS, POST_BRIGHT_BOTTOM);  
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_CONTRAST, POST_CONTRA);			 
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_SATURATION, POST_SATURA);		 
}
bool FkCamera::getQueryFrame(IplImage** dstImageTop, IplImage** dstImageBottom){
	*dstImageTop = cvQueryFrame(this->camCaptureTop);
	*dstImageBottom = cvQueryFrame(this->camCaptureBottom);
	if(!(*dstImageTop) || !(*dstImageBottom)) {
		printf("You need to connect a camera to your computer");
		return false;
	}
	else {
		cvFlip(*dstImageTop, *dstImageTop, 1);
		cvFlip(*dstImageBottom, *dstImageBottom, 1);
		return true;
	}
}

FkCamera::~FkCamera(){
	cvReleaseCapture(&camCaptureTop);
	cvReleaseCapture(&camCaptureBottom);
}