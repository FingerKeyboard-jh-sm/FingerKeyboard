#include"FkCamera.h"
FkCamera::FkCamera(int deviceIndex){
	setCamera(deviceIndex);
	setResolution(CAM_WIDTH, CAM_HEIGHT);
#ifdef WIN32
	setInitProperty();
#endif
}
void FkCamera::setInitProperty(){
	this->setBrightness(INIT_BRIGHT);
	this->setContrast(INIT_CONTRA);
	this->setSaturation(INIT_SATURA);
	this->setGain(INIT_GAIN);
	this->setExposure(INIT_EXPOSU);
	this->setWhiteBalance(INIT_WHITE);
}
void FkCamera::setBrightness(int value){
	cvSetCaptureProperty(camCapture, CV_CAP_PROP_BRIGHTNESS, value);//160
}
void FkCamera::setContrast(int value){
	cvSetCaptureProperty(camCapture, CV_CAP_PROP_CONTRAST, value);//29
}
void FkCamera::setSaturation(int value){
	cvSetCaptureProperty(camCapture, CV_CAP_PROP_SATURATION, value);//34
}
void FkCamera::setGain(int value){
	cvSetCaptureProperty(camCapture, CV_CAP_PROP_GAIN, value);//100
}
void FkCamera::setExposure(int value){
	cvSetCaptureProperty(camCapture, CV_CAP_PROP_EXPOSURE,value);//-4
}
void FkCamera::setWhiteBalance(int value){
	cvSetCaptureProperty(camCapture, CV_CAP_PROP_WHITE_BALANCE_U, value);//6820
}
FkCamera::FkCamera(char* fileName){
	setVideo(fileName);
	setResolution(CAM_WIDTH, CAM_HEIGHT);
}
bool FkCamera::isSettingCamera(){
	if(this->camCapture)
		return true;
	else
		return false;
}
void FkCamera::setResolution(int width, int height){
	camResolution = cvSize(width, height);
	cvSetCaptureProperty(camCapture, CV_CAP_PROP_FRAME_WIDTH, camResolution.width);
	cvSetCaptureProperty(camCapture, CV_CAP_PROP_FRAME_HEIGHT, camResolution.height);
}

CvSize FkCamera::getResolution(){
	return camResolution;
}

void FkCamera::setCamera(int deviceIndex){
	this->camCapture = cvCreateCameraCapture(deviceIndex);
}


IplImage* FkCamera::getQueryFrame(){
	return cvQueryFrame(this->camCapture);
}

void FkCamera::setVideo(char* fileName){
	this->camCapture = cvCaptureFromFile(fileName);

}
void FkCamera::releaseCamera(){
	cvReleaseCapture(&camCapture);
}
FkCamera::FkCamera(){

}