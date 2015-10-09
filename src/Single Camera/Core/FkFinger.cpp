/**
* @file FkFinger.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 사용자의 손가락 움직임 분석
*/
#include"FkPostProcessor.h"
FkFinger::FkFinger(){
	this->validMotion		= false;
	this->downOrientMotion	= false;
	this->fingerTip			= cvPoint(0,0);
	this->motionVector		= 0;
	this->motionVectorAccumulation = 0;

}
void FkFinger::setPrevFinger(){
	this->prevFinger		 = new FkFinger();
}
void FkFinger::fingerCopy(FkFinger* finger){
	if(finger){
		this->prevFinger->fingerTip.x = finger->fingerTip.x;
		this->prevFinger->fingerTip.y = finger->fingerTip.y;
		this->prevFinger->downOrientMotion = finger->downOrientMotion;
		this->prevFinger->validMotion = finger->validMotion;
		this->prevFinger->motionVector = finger->motionVector;
		this->prevFinger->motionVectorAccumulation = finger->motionVectorAccumulation;
	}
	else{
		prevFinger->fingerTip.x = -1;
		prevFinger->fingerTip.y = -1;
		prevFinger->validMotion = false;
		prevFinger->downOrientMotion = false;
		prevFinger->motionVector = 0;
		prevFinger->motionVectorAccumulation = 0;
	}
}
void FkFinger::setValidMotion(){
	double deltaX, deltaY;
	deltaX = CV_IABS(prevFinger->fingerTip.x - fingerTip.x);
	deltaY = CV_IABS(prevFinger->fingerTip.y - fingerTip.y);
	deltaX < MAX_TOLERANCE_X && deltaY < MAX_TOLERANCE_Y ? this->validMotion = true : this->validMotion = false;
}
void FkFinger::setMotionVector(){
	double x, y;
	x = fingerTip.x - prevFinger->fingerTip.x;
	y = fingerTip.y - prevFinger->fingerTip.y;
	if(CV_IABS(x) < MIN_TOLERANCE_X && CV_IABS(y) < MIN_TOLERANCE_Y){
		this->motionVector = 0;
		this->downOrientMotion = false;
		motionVectorAccumulation = 0;
		return;
	}
	if(y > 0)
		downOrientMotion =true;
	else 
		downOrientMotion = false;
	if(prevFinger->fingerTip.x == -1)
		this->downOrientMotion = false;
	x *= x;
	x *= 0.2;
	y *= y;
	y *= 20;
	this->motionVector = sqrt(x+y);
	if(motionVector > MAX_TOLERANCE_MOTION)
		this->motionVector = 0;
	this->isMotion()?motionVectorAccumulation = prevFinger->motionVectorAccumulation + this->motionVector:motionVectorAccumulation = 0;
}
bool FkFinger::isMotion(){
	return this->downOrientMotion && this->motionVector > MIN_TOLERANCE_MOTION && this->validMotion;	//motionVector = 35
}
double FkFinger::getmotionVectorAccumulation(){
	return this->motionVectorAccumulation;
}
void FkFinger::initAttribute(){
	prevFinger->fingerTip.x = fingerTip.x;
	prevFinger->fingerTip.y = fingerTip.y;
	prevFinger->validMotion = this->validMotion;
	prevFinger->downOrientMotion = this->downOrientMotion;
	prevFinger->motionVector = this->motionVector;
	prevFinger->motionVectorAccumulation = this->motionVectorAccumulation;

	this->validMotion = false;
	this->downOrientMotion = false;
	this->fingerTip.x = -1;
	this->fingerTip.y = -1;

}
bool FkFinger::isDownMotion(){
	return downOrientMotion && motionVectorAccumulation > MIN_TOLERANCE_MOTIONACCUMULATION;
}
bool FkFinger::isFingerInButton(FkKeyButton button){
	int t = 1;
	CvRect keyButton = button.getKeyLocation();
	if(fingerTip.x > keyButton.x -t && t+fingerTip.x < keyButton.x + keyButton.width)
		if(fingerTip.y > keyButton.y -t && t+fingerTip.y < keyButton.y + keyButton.height)
			return true;
	return false;
}
FkFinger::~FkFinger(){
//	delete prevFinger;
}