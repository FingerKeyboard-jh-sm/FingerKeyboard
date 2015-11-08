/**
* @file FkHand.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 손 윤곽선 검출 및 손의 움직임 산출
*/
#include"FkPostProcessor.h"
void FkHand::setHandContour(CvSeq* contour){
	this->handContour = contour;	
}
void FkHand::setHandArea(double handArea){
	this->handArea = handArea;
}
FkHand::FkHand(){
	for(int i = 0 ; i < 5 ; i++)
		finger[i].setPrevFinger();
	prevDetectFingerCount	= 0;
	detectFingerCount		= 0;
	hullStorage				= cvCreateMemStorage(0);
	handStorage				= cvCreateMemStorage(0);
	tempStorage				= cvCreateMemStorage(0);
	handContour				= NULL;
	center				= cvPoint(0, 0);
}
void FkHand::getHandDefect(){
	this->handContour = cvApproxPoly(handContour,sizeof(CvContour), handStorage, CV_POLY_APPROX_DP, 10, 1);
	hull = cvConvexHull2(this->handContour, this->hullStorage, CV_CLOCKWISE, 0);
	defect = cvConvexityDefects(this->handContour,this->hull,this->handStorage );
}
void FkHand::calcCenter(){
	int x = 0, y = 0;
	int total = defect->total;
	for (int i = 0; i < total && i < 8; i++){
		x += this->defectArray[i].depth_point->x;
		y += this->defectArray[i].depth_point->y;
	}
	x /= total;
	y /= total;
	center.x = x;
	center.y = y;
}
int FkHand::getDefectTotal(){
	return this->defect->total;
}
void FkHand::convertArray(){
	cvCvtSeqToArray(this->defect, this->defectArray, CV_WHOLE_SEQ);
}
void FkHand::arrayMemSet(){
	memset(defectArray, 0, 100);
}
void FkHand::correctPrevFingerTipIndex(){
	FkFinger* tempFingerTip[5];
	for(int i = 0 ; i < 5 ; i++)
		tempFingerTip[i] = finger[i].prevFinger;
	for(int i =0 ; i < 5 ; i++){
		for(int j = 0 ; j < 5 ; j++){
			if(CV_IABS(this->finger[i].fingerTip.x - tempFingerTip[j]->fingerTip.x) < MAX_TOLERANCE_X 
				&& CV_IABS(this->finger[i].fingerTip.y - tempFingerTip[j]->fingerTip.y) < MAX_TOLERANCE_Y){
					finger[i].fingerCopy(tempFingerTip[j]);
					break;
			}
			else if(j == 4)
				finger[i].fingerCopy(NULL);
		}
	}
}
bool FkHand::isAllFingerDownMotion(){
	int downCount = 0;
	for(int i = 0 ; i < this->prevDetectFingerCount ; i++)
		if(finger[i].isDownMotion())	//motionVector -> motionVectorSum
			downCount++;
	if(downCount > 0 &&downCount >= this->prevDetectFingerCount -1)
		return false;
	return true;
}
void FkHand::setValidMotionVector(){
	for(int i = 0 ; i < 5 ; i++)
		finger[i].setValidMotion();
}
void FkHand::setFingerMotionVector(){
	for(int i = 0 ; i < 5 ; i++)
		finger[i].setMotionVector();
}
void FkHand::setPrevDetectFingerCount(){
	prevDetectFingerCount = detectFingerCount;
}
void FkHand::resetFingerAttribute(){
	for(int i =0 ;  i < 5 ; i++)
		finger[i].initAttribute();
}
void FkHand::determineMotion(){
	double maxMotion = 0, fingerMotion;
	int count = 0, index;
	for(int i = 0 ; i < 5 ; i++){
		fingerMotion = finger[i].getmotionVectorAccumulation();
		if(fingerMotion > MIN_TOLERANCE_MOTIONACCUMULATION ){
			count++;
			if(fingerMotion > maxMotion){
				maxMotion = fingerMotion;
				index = i;
			}
		}
	}
	count == 1?pressFinger = index:pressFinger =  -1;
}
bool FkHand::isFingerPressButton(){
	if(pressFinger == -1)
		return false;
	else
		return true;
}
CvPoint FkHand::getPressFingerLocation(){
	return finger[pressFinger].fingerTip;
}
bool FkHand::isPressKey(FkKeyButton button){
	for(int i = 0 ; i < 5; i++)
		if(finger[i].isFingerInButton(button))
			return true;
	return false;
}
FkHand::~FkHand(){
	cvReleaseMemStorage(&handStorage);
}