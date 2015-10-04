#include "FkCamera.h"
#include "MmalDualCamera.h"

CvCapture* FkCamera::camCaptureTop;
CvCapture* FkCamera::camCaptureBottom;
FkCamera::FkCamera(int deviceIndexTop, int deviceIndexBottom){
	//카메라 설정
#ifndef _WINDOWS
	cameraSetDataInit(2);
printf("Camera Setting Success\n");
#endif
#ifdef _WINDOWS
	setCamera(deviceIndexTop, deviceIndexBottom);
#endif
	//해상도 설정
	setResolution();
#ifdef _WINDOWS
	//초기 카메라 화질 설정
	setInitProperty();
#endif

}

void FkCamera::setResolution(){
	
#ifdef _WINDOWS
	int width = (int)cvGetCaptureProperty(camCaptureTop, CV_CAP_PROP_FRAME_WIDTH);
	int height = (int)cvGetCaptureProperty(camCaptureTop, CV_CAP_PROP_FRAME_HEIGHT);
	camResolution = cvSize(width, height);
#endif
#ifndef _WINDOWS
	camResolution = cvSize(CAMERA_VIEW_WIDTH, CAMERA_VIEW_HEIGHT);
#endif
}
CvSize FkCamera::getResolution(){
	return camResolution;
}
#ifdef _WINDOWS
void FkCamera::setInitProperty() {
	this->bright = POST_BRIGHT_TOP;
	this->contra = POST_CONTRA;
	this->satura = POST_SATURA;
	this->exposu = POST_EXPOSU;
	this->gain = POST_GAIN;
	this->white = POST_WHITE;

	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_BRIGHTNESS, PRE_BRIGHT);
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_CONTRAST, PRE_CONTRA);
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_SATURATION, PRE_SATURA);
	setBrightness(bright);
	setContrast(contra);
	setSaturation(satura);
}
void FkCamera::setBrightness(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_BRIGHTNESS, value);
}
void FkCamera::setContrast(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_CONTRAST, value);
}
void FkCamera::setSaturation(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_SATURATION, value);
}
void FkCamera::setGain(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_GAIN, value);
}
void FkCamera::setExposure(int value){
	cvSetCaptureProperty(camCaptureBottom, CV_CAP_PROP_EXPOSURE, -1*value);
}
void FkCamera::setWhiteBalance(int value){
	cvSetCaptureProperty(camCaptureBottom, 17, value);
}
void FkCamera::setBrightnessTop(int value){
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_BRIGHTNESS, value);
}
void FkCamera::setContrastTop(int value){
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_CONTRAST, value);
}
void FkCamera::setSaturationTop(int value){
	cvSetCaptureProperty(camCaptureTop, CV_CAP_PROP_SATURATION, value);
}

//카메라 deviceIndex = -1  :: 카메라 없음
//카메라 deviceIndex = 0  :: 내부 카메라 
//카메라 deviceIndex = 1  :: 외부 카메라
//cvCreateCameraCapture(index) :: 카메라 여부


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

int* FkCamera::getBright() {
	return &bright;
}
int* FkCamera::getContra() {
	return &contra;
}
int* FkCamera::getSatura() {
	return &satura;
}
int* FkCamera::getExposu() {
	return &exposu;
}
int* FkCamera::getGain() {
	return &gain;
}
int* FkCamera::getWhite() {
	return &white;
}
#endif

FkCamera::~FkCamera(){
	cvReleaseCapture(&camCaptureTop);
	cvReleaseCapture(&camCaptureBottom);
}