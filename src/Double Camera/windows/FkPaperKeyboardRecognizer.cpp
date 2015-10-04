#include"FkPreProcessor.h"
#include"FkProgramState.h"
#include"FkCamera.h"
typedef enum{Type_A, Type_B} KeyboardType;
FkPaperKeyboardRecognizer::FkPaperKeyboardRecognizer(int keyboardType, CvSize camResolution){
	switch(keyboardType){
	case Type_A:
		paperKeyboard = new FkPaperKeyboard_TypeA();
		break;
	case Type_B:
		break;
	}
	buttonImage = cvCreateImage(camResolution, IPL_DEPTH_8U, 3);
	bottomMaskImage = cvCreateImage(camResolution, IPL_DEPTH_8U, 3);
	paperKeyboard->keyboardMaskBottom = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
	paperKeyboard->keyboardMaskTop = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
}
FkPaperKeyboard* FkPaperKeyboardRecognizer::getPaperKeyboard(){
	return this->paperKeyboard;
}
void FkPaperKeyboardRecognizer::setSelectedPaperKeyboardBottom(CvRect selectedArea){
	this->selectedPaperAreaBottom = selectedArea;
}
CvRect FkPaperKeyboardRecognizer::getSelectedPaperKeyboardBottom(){
	return this->selectedPaperAreaBottom;
}
bool FkPaperKeyboardRecognizer::setPaperKeyboardCornerTop(IplImage* srcImage){
	CvSize size = cvGetSize(srcImage);
	IplImage* transImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* dstImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* eigImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* tempImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* baseImage = cvCreateImage(size, IPL_DEPTH_8U, 1);

	cvCvtColor(srcImage, transImage, CV_BGR2HSV);
	cvSplit(transImage, dstImage, 0, 0, 0);
	cvSmooth(dstImage, dstImage, CV_BLUR, 10);
	cvDilate(dstImage, dstImage, 0, 15);
	cvErode(dstImage, dstImage, 0, 12);
	cvInRangeS(dstImage,cvScalar(80), cvScalar(255),dstImage);

	CvPoint2D32f corner[4];
	int paperCorenrCount = 4;
	
	cvSet(baseImage,cvScalar(0));

	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq * firstContour;
	//최외곽선 추출, 그리기
	if(cvFindContours(dstImage, storage, &firstContour, 88, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE) == NULL)
		return false;

	cvDrawContours(baseImage, firstContour, CV_RGB(255,255,255), CV_RGB(0,0,0), 0, -1, CV_AA);

	cvDilate(baseImage, baseImage, 0, 4); // 팽창효과
	cvSmooth(baseImage, baseImage, CV_BLUR, 2); // 블러링
	
	// 키보드의 4개의 코너를 추출
	cvGoodFeaturesToTrack(baseImage, eigImage, tempImage, corner, &paperCorenrCount, 0.1, 150);
	cvFindCornerSubPix(baseImage, corner, paperCorenrCount,cvSize (3, 3), cvSize (-1, -1), cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));

	if(paperCorenrCount != 4){
		return false;
	}

	setKeyboardCorner(corner);	

	// 침식효과 적용 후 Top Mask 설정.
	cvErode(baseImage, baseImage, 0, 10);
	setKeyboardMaskTop(baseImage);

	cvReleaseImage(&baseImage);
	cvReleaseImage(&eigImage);
	cvReleaseImage(&tempImage);

	cvReleaseImage(&transImage);
	cvReleaseImage(&dstImage);

	cvReleaseMemStorage(&storage);
	return true;
}
bool FkPaperKeyboardRecognizer::setPaperKeyboardContourBottom(IplImage* srcImage, FkMouseListener mouseListener){
	CvSize size = cvGetSize(srcImage);
	IplImage* YCrCbImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* crImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* binImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* tempImage = cvCreateImage(size, IPL_DEPTH_8U, 1);

	cvCvtColor(srcImage, YCrCbImage, CV_BGR2YCrCb);
	cvSplit(YCrCbImage, 0, crImage, 0, 0);

	cvSetImageROI(crImage, selectedPaperAreaBottom);
	cvSetImageROI(tempImage, selectedPaperAreaBottom);

	cvInRangeS(crImage, KB_REGION_LOW_SCALAR, KB_REGION_HIGH_SCALAR, crImage);

	// 외각선 추출 -> 내부 채우기 -> 외각선 지워서 Mask 크기 축소.
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq * contour;
	cvCopy(crImage,tempImage);
	if(cvFindContours(tempImage, storage, &contour, 88, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE)==NULL) {
		puts("MESSAGE : keyboardMaskRect Contour Error(fill in contour)");
		return false;
	}
	if(cvContourPerimeter(contour) < 100) false;
	cvSet(crImage, cvScalar(0));
	cvDrawContours(crImage, contour, CV_RGB(255,255,255), CV_RGB(0,0,0), 0, -1, CV_AA);

	for(int i=0; i<3; i++) {
		cvCopy(crImage,tempImage);
		if(cvFindContours(tempImage, storage, &contour, 88, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE)==NULL) {
			puts("MESSAGE : keyboardMaskRect Contour Error(Eraser contour)");
			return false;
		}
		cvDrawContours(crImage, contour, cvScalar(0), cvScalar(0),0);
	}

	cvResetImageROI(crImage);
	cvResetImageROI(tempImage);

	setKeyboardMaskBottom(crImage);
	
	cvReleaseImage(&YCrCbImage);
	cvReleaseImage(&crImage);
	cvReleaseImage(&tempImage);
	cvReleaseImage(&binImage);

	cvReleaseMemStorage(&storage);

	return true;
}
void FkPaperKeyboardRecognizer::setKeyboardCorner(CvPoint2D32f* corner){
	for(int i = 0 ; i < 4 ; i++)
		paperKeyboard->keyboardCorner[i] = corner[i];
}
void FkPaperKeyboardRecognizer::setKeyboardMaskTop(IplImage* keyboardMaskTop){
	cvSet(paperKeyboard->keyboardMaskTop, cvScalar(0));
	cvCopy(keyboardMaskTop, paperKeyboard->keyboardMaskTop);
}
void FkPaperKeyboardRecognizer::setKeyboardMaskBottom(IplImage* keyboardMaskBottom){
	cvSet(paperKeyboard->keyboardMaskBottom, cvScalar(0));
	cvSetImageROI(keyboardMaskBottom, selectedPaperAreaBottom);
	cvSetImageROI(paperKeyboard->keyboardMaskBottom, selectedPaperAreaBottom);
	cvCopy(keyboardMaskBottom, paperKeyboard->keyboardMaskBottom);
	cvResetImageROI(keyboardMaskBottom);
	cvResetImageROI(paperKeyboard->keyboardMaskBottom);
}
void FkPaperKeyboardRecognizer::setKeyButton(IplImage* srcImage){
	this->paperKeyboard->setKeyButton(srcImage);
}
void FkPaperKeyboardRecognizer::setKeyButtonImage(IplImage* srcImage){
	this->paperKeyboard->setKeyButtonImage(srcImage, this->buttonImage);
}
void FkPaperKeyboardRecognizer::setKeyMaskBottomImage(IplImage* srcImage){
	this->paperKeyboard->setKeyMaskBottomImage(srcImage, this->bottomMaskImage);
}
FkKeyButton* FkPaperKeyboardRecognizer::getKeyButton(){
	return this->paperKeyboard->getKeyButton();
}
FkPaperKeyboardRecognizer::~FkPaperKeyboardRecognizer(){
	delete this->paperKeyboard;
}