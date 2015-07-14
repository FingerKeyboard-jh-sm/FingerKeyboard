#include"FkPreProcessor.h"
#include"FkProgramState.h"
typedef enum{Type_A, Type_B} KeyboardType;
FkPaperKeyboardRecognizer::FkPaperKeyboardRecognizer(int keyboardType){
	switch(keyboardType){
	case Type_A:
		paperKeyboard = new FkPaperKeyboard_TypeA();
		break;
	case Type_B:
		break;
	}
}
FkPaperKeyboard* FkPaperKeyboardRecognizer::getPaperKeyboard(){
	return this->paperKeyboard;
}
void FkPaperKeyboardRecognizer::setSelectedPaperKeyboard(CvRect selectedArea){
	this->selectedPaperArea = selectedArea;
}
CvRect FkPaperKeyboardRecognizer::getSelectedPaperKeyboard(){
	return this->selectedPaperArea;
}
void FkPaperKeyboardRecognizer::setPaperKeyboardCorner(IplImage* srcImage, FkMouseListener mouseListener){
	CvSize size = cvGetSize(srcImage);
	IplImage* transImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* splitImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* dstImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* eigImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* tempImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	CvPoint2D32f corner[4];
	int paperCorenrCount = 4;


	cvCvtColor(srcImage, transImage, CV_BGR2HSV);
	cvSplit(transImage, 0, splitImage, 0, 0);
	cvErode(splitImage, splitImage, 0 ,5);
	cvDilate(splitImage, splitImage, 0, 6);
	cvSmooth(splitImage, dstImage, CV_BLUR, 5);
	cvShowImage("dst", dstImage);

	cvSetImageROI(dstImage, selectedPaperArea);
	cvSetImageROI(srcImage, selectedPaperArea);
	cvGoodFeaturesToTrack(dstImage, eigImage, tempImage, corner, &paperCorenrCount, 0.04, 200);//, NULL, 7, 0);
	cvFindCornerSubPix (dstImage, corner, paperCorenrCount,cvSize (3, 3), cvSize (-1, -1), cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));
	if(paperCorenrCount != 4){
		std::cout<<"MESSAGE : Incorrect Area."<<std::endl;  
		FkCurrentMode::state = SET_KB_REGION;
		mouseListener.resetMouseDragArea();
		cvResetImageROI(dstImage);
		cvResetImageROI(srcImage);
		return;
	}
	setKeyboardCorner(corner);
	cvResetImageROI(dstImage);
	cvResetImageROI(srcImage);

	cvReleaseImage(&dstImage);
	cvReleaseImage(&eigImage);
	cvReleaseImage(&tempImage);
	cvReleaseImage(&transImage);
	cvReleaseImage(&splitImage);
	FkCurrentMode::state = CONFIRM_KB_CORNER;

}
void FkPaperKeyboardRecognizer::setKeyboardCorner(CvPoint2D32f* corner){
	for(int i = 0 ; i < 4 ; i++)
		paperKeyboard->keyboardCorner[i] = corner[i];
}

void FkPaperKeyboardRecognizer::setKeyButton(IplImage* srcImage){
	this->paperKeyboard->setKeyButton(srcImage, this->selectedPaperArea);
}
void FkPaperKeyboardRecognizer::showKeyButton(IplImage* srcImage){
	this->paperKeyboard->showKeyButton(srcImage, this->buttonImage);
}