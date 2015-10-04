#include"FkPostProcessor.h"

FkFingerTipDetector::FkFingerTipDetector(CvSize camResolution) {
	keyboardMaskTop = cvCreateImage(camResolution, IPL_DEPTH_8U, 1);
	keyboardMaskBottom = cvCreateImage(camResolution, IPL_DEPTH_8U, 1);
	this->divisionNum = -1;
	this->divisionCnt[0] = DIVISIONNUM0;
	this->divisionCnt[1] = DIVISIONNUM1;
	this->divisionCnt[2] = DIVISIONNUM2;
	this->divisionCnt[3] = DIVISIONNUM3;
	this->divisionCnt[4] = DIVISIONNUM4;
	this->divisionCnt[5] = DIVISIONNUM5;
}

void FkFingerTipDetector::initFingerTipPoint(){
	fingerTipPoint.x = 0;
	fingerTipPoint.y = 0;
}
void FkFingerTipDetector::setkeyboardMaskTop(IplImage *srcImage, IplImage* keyboardMaskTop) {
	cvCopy(keyboardMaskTop, this->keyboardMaskTop);
}
void FkFingerTipDetector::setkeyboardMaskBottom(IplImage *srcImage, IplImage* keyboardMaskBottom, CvRect selectedPaperArea) {
	cvCopy(keyboardMaskBottom, this->keyboardMaskBottom);
}
void FkFingerTipDetector::setkeyboardMaskRectBottom(){

	IplImage *temp = cvCreateImage(cvGetSize(keyboardMaskBottom), IPL_DEPTH_8U, 1);
	IplImage *test = cvCreateImage(cvGetSize(keyboardMaskBottom), IPL_DEPTH_8U, 1);
	cvSet(test, cvScalar(240));
	cvCopy(keyboardMaskBottom,temp);


	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq * contour;
	if(cvFindContours(temp, storage, &contour, 88, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE)==NULL) {
		puts("MESSAGE : keyboardMaskRect Contour Error");
	}

	keyboardMaskRectBottom = cvBoundingRect(contour, 1); // Mask의 태두리 사각형 정보 저장.

	cvRectangleR(keyboardMaskBottom, keyboardMaskRectBottom, cvScalar(155,155,155));

	cvReleaseImage(&temp);
	cvReleaseImage(&test);
}

bool FkFingerTipDetector::isTouchKeyboard(IplImage* bottomImage, CvRect selectedPaperArea) {
	IplImage* yCrCbImage = cvCreateImage(cvGetSize(bottomImage), IPL_DEPTH_8U, 3);
	IplImage* test = cvCreateImage(cvGetSize(bottomImage), IPL_DEPTH_8U, 3);
	IplImage* skinImage = cvCreateImage(cvGetSize(bottomImage), IPL_DEPTH_8U, 1);

	cvCopy(bottomImage, test, keyboardMaskBottom);

	cvCvtColor(bottomImage, yCrCbImage, CV_BGR2YCrCb);

	cvInRangeS(yCrCbImage, SKIN_S_MIN_BOTTOM, SKIN_S_MAX_BOTTOM, skinImage);

	int pointCnt=0;
	int pointXSum=0, pointYSum=0;
	int pointXAvg=0, pointYAvg=0;
	for(int j=keyboardMaskRectBottom.y; j<keyboardMaskRectBottom.y+keyboardMaskRectBottom.height; j++) {
		for(int i=keyboardMaskRectBottom.x; i<keyboardMaskRectBottom.x+keyboardMaskRectBottom.width; i++) {	
			if(cvGetReal2D(skinImage,j,i)==255 && cvGetReal2D(keyboardMaskBottom,j,i)==255 ) {
				pointXSum += i;
				pointYSum += j;
				pointCnt++;
			}
			else 
				cvSetReal2D(skinImage,j,i,0);
		}
	}

	cvReleaseImage(&yCrCbImage);
	cvReleaseImage(&skinImage);
	cvReleaseImage(&test);

	if(pointCnt > 5) {
		pointXAvg = pointXSum/pointCnt;
		fingerXBottom = pointXAvg;
		return true;
	}
	return false;
}

void FkFingerTipDetector::setFingerXTop() {
	double bottomWidth = keyboardMaskRectBottom.width;
	double bottomDiffX = fingerXBottom - keyboardMaskRectBottom.x;
	double topWidth = FkPaperKeyboard::keyboardCorner[2].x-FkPaperKeyboard::keyboardCorner[3].x;
	double topDiffX = bottomDiffX*topWidth/bottomWidth;
	fingerXTop =  topDiffX + FkPaperKeyboard::keyboardCorner[3].x;
}

void FkFingerTipDetector::setFingerROITop() {
	fingerROITop.x = fingerXTop - 12;
	fingerROITop.width = 24;
	if(FkPaperKeyboard::keyboardCorner[0].y < FkPaperKeyboard::keyboardCorner[1].y) {
		fingerROITop.y = FkPaperKeyboard::keyboardCorner[0].y;
		fingerROITop.height = FkPaperKeyboard::keyboardCorner[2].y - FkPaperKeyboard::keyboardCorner[0].y - 3;
	}
	else {
		fingerROITop.y = FkPaperKeyboard::keyboardCorner[1].y;
		fingerROITop.height = FkPaperKeyboard::keyboardCorner[3].y - FkPaperKeyboard::keyboardCorner[1].y - 3;
	}
}

CvPoint FkFingerTipDetector::getFingerTipPoint() {
	return fingerTipPoint;
}

void FkFingerTipDetector::detectFingerTip(IplImage *topImage) {
	IplImage *yCrCbImage = cvCreateImage(cvGetSize(topImage), IPL_DEPTH_8U, 3);
	IplImage *skinImage = cvCreateImage(cvGetSize(topImage), IPL_DEPTH_8U, 1);
	cvCvtColor(topImage, yCrCbImage, CV_BGR2YCrCb);

	cvSetImageROI(yCrCbImage, fingerROITop);
	cvSetImageROI(skinImage, fingerROITop);
	cvSetImageROI(keyboardMaskTop, fingerROITop);

	cvInRangeS(yCrCbImage, SKIN_S_MIN_TOP, SKIN_S_MAX_TOP, skinImage);

	int pointCnt=0;
	int pointXSum=0;
	int pointXAvg=0;
	for(int j=fingerROITop.height-1; j>0; j--) {
		for(int i=0; i<fingerROITop.width; i++) {	
			if( ((int)cvGetReal2D(keyboardMaskTop,j,i)==255) && ((int)cvGetReal2D(skinImage,j,i))==255) {
				for(int l=j; l>j-10; l--) {
					if(l==0) {
						cvResetImageROI(yCrCbImage);
						cvResetImageROI(skinImage);
						cvResetImageROI(keyboardMaskTop);
						cvReleaseImage(&yCrCbImage);
						cvReleaseImage(&skinImage);
						return;
					}
					for(int k=0; k<fingerROITop.width; k++) {
						if(((int)cvGetReal2D(skinImage,l,k))==255) {
							pointCnt++;
							pointXSum += k;
						}
					}
				}
				pointXAvg = pointXSum/pointCnt;
				fingerTipPoint = cvPoint(pointXAvg+fingerROITop.x,j+fingerROITop.y-5);
				cvResetImageROI(yCrCbImage);
				cvResetImageROI(skinImage);
				cvResetImageROI(keyboardMaskTop);
				cvReleaseImage(&yCrCbImage);
				cvReleaseImage(&skinImage);
				return;
			}
		}
	}
}

void FkFingerTipDetector::setKeyButtonDivision(FkKeyButton* keyButton) {
	for(int i=0; i<5; i++) {
		keyButtonDivision[i] = keyButton;
		keyButton += divisionCnt[i];
	}
	keyButtonDivision[5] = keyButton;	
}

void FkFingerTipDetector::setFingerTipDivision() {
	if( fingerTipPoint.y>=keyButtonDivision[0][0].getKeyLocation().y && fingerTipPoint.y<=keyButtonDivision[0][0].getKeyLocation().y+keyButtonDivision[0][0].getKeyLocation().height) 
		divisionNum = 0;
	else if( fingerTipPoint.y>=keyButtonDivision[1][0].getKeyLocation().y && fingerTipPoint.y<=keyButtonDivision[1][0].getKeyLocation().y+keyButtonDivision[1][0].getKeyLocation().height)
		divisionNum = 1;
	else if( fingerTipPoint.y>=keyButtonDivision[2][0].getKeyLocation().y && fingerTipPoint.y<=keyButtonDivision[2][0].getKeyLocation().y+keyButtonDivision[2][0].getKeyLocation().height)
		divisionNum = 2;
	else if( fingerTipPoint.y>=keyButtonDivision[3][0].getKeyLocation().y && fingerTipPoint.y<=keyButtonDivision[3][0].getKeyLocation().y+keyButtonDivision[3][0].getKeyLocation().height)
		divisionNum = 3;
	else if( fingerTipPoint.y>=keyButtonDivision[4][0].getKeyLocation().y && fingerTipPoint.y<=keyButtonDivision[4][0].getKeyLocation().y+keyButtonDivision[4][0].getKeyLocation().height)
		divisionNum = 4;
	else if( fingerTipPoint.y>=keyButtonDivision[5][0].getKeyLocation().y && fingerTipPoint.y<=keyButtonDivision[5][0].getKeyLocation().y+keyButtonDivision[5][0].getKeyLocation().height) 
		divisionNum = 5;
	else
		divisionNum = -1;
}
FkKeyButton* FkFingerTipDetector::getEventKey() {
	setFingerTipDivision();
	if(divisionNum==-1) return NULL; 
	else if(divisionNum!=5) { 
		for(int i=0; i<divisionCnt[divisionNum]; i++) {
			if( fingerTipPoint.x >= keyButtonDivision[divisionNum][i].getKeyLocation().x &&
				fingerTipPoint.x <= keyButtonDivision[divisionNum][i].getKeyLocation().x + keyButtonDivision[divisionNum][i].getKeyLocation().width ) {
				return &keyButtonDivision[divisionNum][i];		
			}
		}
	}
	else {
		for(int i=0; i<divisionCnt[divisionNum]; i++) {
			if( fingerTipPoint.x >= keyButtonDivision[divisionNum][i].getKeyLocation().x &&
				fingerTipPoint.x <= keyButtonDivision[divisionNum][i].getKeyLocation().x + keyButtonDivision[divisionNum][i].getKeyLocation().width ) {
				if( i==7 ) {
					//Up Key
					if(fingerTipPoint.y > keyButtonDivision[divisionNum][i].getKeyLocation().y)
						return &keyButtonDivision[divisionNum][i];
					//Down Key
					else
						return &keyButtonDivision[divisionNum][i+3];
				}
				return &keyButtonDivision[divisionNum][i];		
			}
		}
	}
	return NULL;
}

void FkFingerTipDetector::drawFingerTip(IplImage *topImage, IplImage *bottomImage) {
	cvCircle(bottomImage, cvPoint(fingerXBottom, keyboardMaskRectBottom.y+keyboardMaskRectBottom.height),3,cvScalar(255,0,0),3);
	cvCircle(topImage, cvPoint(fingerXTop, 330),3,cvScalar(255,0,0),3);
	cvRectangleR(topImage, fingerROITop, cvScalar(0,255,0));
	cvCircle(topImage, fingerTipPoint, 3, cvScalar(0,0,255),3);
}

FkFingerTipDetector::~FkFingerTipDetector() {
	cvReleaseImage(&keyboardMaskTop);
	cvReleaseImage(&keyboardMaskBottom);
}