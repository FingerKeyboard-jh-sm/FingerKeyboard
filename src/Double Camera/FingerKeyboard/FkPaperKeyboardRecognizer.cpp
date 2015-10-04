#include"FkPreprocessor.h"
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
	paperKeyboard->keyboardMaskBottom = cvCreateImage(camResolution, IPL_DEPTH_8U, 1);
	paperKeyboard->keyboardMaskTop = cvCreateImage(camResolution, IPL_DEPTH_8U, 1);
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
	//cvShowImage("transImage",transImage);
	cvSplit(transImage, dstImage, 0, 0, 0);
	//cvShowImage("hImage",dstImage);
	cvSmooth(dstImage, dstImage, CV_BLUR, 10);
	cvDilate(dstImage, dstImage, 0, 15);
	cvErode(dstImage, dstImage, 0, 12);
	//cvShowImage("prcessedImage",dstImage);
	cvInRangeS(dstImage,cvScalar(80), cvScalar(255),dstImage);
	//cvShowImage("dstImage", dstImage);

	CvPoint2D32f corner[4];
	int paperCorenrCount = 4;
	
	cvSet(baseImage,cvScalar(0));

	//cvShowImage("dstImage", dstImage);

	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq * firstContour;
	//최외곽선 추출, 그리기
	if(cvFindContours(dstImage, storage, &firstContour, 88, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE) == NULL)
		return false;
	//if(cvContourPerimeter(firstContour) < 1000.0 || cvContourPerimeter(firstContour) > 1500.0 )
		//return -1;
	
	cvDrawContours(baseImage, firstContour, CV_RGB(255,255,255), CV_RGB(0,0,0), 0, -1, CV_AA);
	//cvShowImage("dst2", dstImage);
	//cvShowImage("baseImage", baseImage);	

	cvDilate(baseImage, baseImage, 0, 4); // 팽창효과
	cvSmooth(baseImage, baseImage, CV_BLUR, 2); // 블러링
	
	// 키보드의 4개의 코너를 추출
	cvGoodFeaturesToTrack(baseImage, eigImage, tempImage, corner, &paperCorenrCount, 0.1, 150);//, NULL, 7, 0);
	cvFindCornerSubPix(baseImage, corner, paperCorenrCount,cvSize (3, 3), cvSize (-1, -1), cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));

	if(paperCorenrCount != 4){
		return false;
	}

	//cvShowImage("dstImage",dstImage);
	//cvShowImage("baseImage",baseImage);

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
int FkPaperKeyboardRecognizer::setPaperKeyboardContourBottom(IplImage* srcImage, FkMouseListener mouseListener){
	CvSize size = cvGetSize(srcImage);
	IplImage* hsvImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* hImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* tempImage = cvCreateImage(size, IPL_DEPTH_8U, 1);

	cvCvtColor(srcImage, hsvImage, CV_BGR2HSV);
	cvSplit(hsvImage, hImage,0,0,0);
		

	cvSetImageROI(hImage, selectedPaperAreaBottom);
	cvSetImageROI(tempImage, selectedPaperAreaBottom);


	//0~130
	cvInRangeS(hImage, cvScalar(0), cvScalar(50), hImage);
	cvShowImage("hImage", hImage);

	//cvShowImage("ORG", crImage);
	// 외각선 추출 -> 내부 채우기 -> 외각선 지워서 Mask 크기 축소.
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq * contour;
	cvCopy(hImage,tempImage);
	if(cvFindContours(tempImage, storage, &contour, 88, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE)==NULL) {
		puts("MESSAGE : keyboardMaskRect Contour Error(fill in contour)");
	}
	//crImage 
	cvSet(hImage, cvScalar(0));
	cvDrawContours(hImage, contour, CV_RGB(255,255,255), CV_RGB(0,0,0), 0, -1, CV_AA);
	//cvShowImage("내부 채우기", crImage);

	for(int i=0; i<3; i++) {
		cvCopy(hImage,tempImage);
		if(cvFindContours(tempImage, storage, &contour, 88, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE)==NULL) {
			puts("MESSAGE : keyboardMaskRect Contour Error(Eraser contour)");
		}
		cvDrawContours(hImage, contour, cvScalar(0), cvScalar(0),0);
	}
	cvShowImage("FIN", hImage);

	cvResetImageROI(hImage);
	cvResetImageROI(tempImage);

	setKeyboardMaskBottom(hImage);
	
	cvReleaseImage(&hsvImage);
	cvReleaseImage(&hImage);
	cvReleaseImage(&tempImage);
	

	cvReleaseMemStorage(&storage);

	return 0;
	
	/*
	// 원본
	CvSize size = cvGetSize(srcImage);
	IplImage* ycrcbImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* crImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* crImageTemp = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* edgeImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq * firstContour;

	cvCvtColor(srcImage, ycrcbImage, CV_BGR2YCrCb);
	cvSplit(ycrcbImage, 0, crImage, 0, 0);
	cvSmooth(crImage, crImageTemp, CV_BLUR, 5, 5);

	cvShowImage("crImageTemp", crImageTemp);

	cvSetImageROI(crImage, selectedPaperAreaBottom);
	cvSetImageROI(crImageTemp, selectedPaperAreaBottom);
	cvSetImageROI(edgeImage, selectedPaperAreaBottom);

	cvThreshold(crImageTemp, crImageTemp, 120, 255, CV_THRESH_BINARY);
	cvErode(crImageTemp, crImageTemp, 0 ,2); // 침식효과
	cvCanny(crImageTemp, edgeImage, 0, 0, 3);
	

	//cvDilate(crImageTemp, crImageTemp, 0, 1); // 팽창효과
	
	if(cvFindContours(edgeImage, storage, &firstContour, 88, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE) == NULL)
		return -1;
	if(cvContourPerimeter(firstContour) < 1000.0 || cvContourPerimeter(firstContour) > 1200.0 )
		return -1;

	//CvRect contourRect = cvBoundingRect(firstContour, 1);
	//cvRectangleR(crImage,contourRect,cvScalar(150,150,150));
	//cvShowImage( "crImage", crImage );

	setKeyboardContour(firstContour);
	//setKeyboardContour(contourRect);

	//cvShowImage( "crImage", crImage );
	cvShowImage( "crImageTemp", crImageTemp );
	cvShowImage( "edgeImage", edgeImage);

	cvResetImageROI(crImage);
	cvResetImageROI(crImageTemp);
	cvResetImageROI(edgeImage);

	cvReleaseImage(&edgeImage);
	cvReleaseImage(&ycrcbImage);
	cvReleaseImage(&crImage);
	cvReleaseImage(&crImageTemp);
	return 0;
	*/
	
}
void FkPaperKeyboardRecognizer::setKeyboardCorner(CvPoint2D32f* corner){
	for(int i = 0 ; i < 4 ; i++)
		paperKeyboard->keyboardCorner[i] = corner[i];
}
//void FkPaperKeyboardRecognizer::setKeyboardContour(CvSeq* contour){
//	paperKeyboard->keyboardContour = contour;
//}
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
FkKeyButton* FkPaperKeyboardRecognizer::getKeyButton(){
	return this->paperKeyboard->getKeyButton();
}
void FkPaperKeyboardRecognizer::showButtonImage(){
	cvShowImage("buttonImage", buttonImage);
}
FkPaperKeyboardRecognizer::~FkPaperKeyboardRecognizer(){
	delete this->paperKeyboard;
}