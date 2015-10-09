/**
* @file FkImageProcessor.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 출력되는 영상에 의미있는 정보를 표시
*/
#include"FkImageProcessor.h"
void FkImageProcessor::paperAreaDraggingImage(IplImage* srcImage, FkMouseListener mouseListener){
	cvSetImageROI(srcImage, mouseListener.getMouseDragArea());
	cvAddS(srcImage, cvScalar(200, 0, 0), srcImage);
	cvRectangleR(srcImage, cvRect(0, 0, mouseListener.getMouseDragArea().width, mouseListener.getMouseDragArea().height), CV_RGB(51, 153, 255),2);
	cvResetImageROI(srcImage);
}
void FkImageProcessor::drawPaperKeyboardCorner(IplImage* srcImage){
	for(int i = 0 ; i < 4 ; i++)
		cvCircle(srcImage, cvPointFrom32f(FkPaperKeyboard::keyboardCorner[i]), 2, CV_RGB(255, 0, 0), 2);
}
void FkImageProcessor::drawDetermineArea(IplImage* srcImage, CvRect rect){
	cvRectangleR(srcImage, rect, CV_RGB(0, 230, 0), 2);
}
void FkImageProcessor::drawSelectedArea(IplImage* srcImage, CvRect rect){
	cvRectangleR(srcImage, rect, CV_RGB(51, 153, 255), 2);
}
void FkImageProcessor::drawHandInputCircle(IplImage* srcImage){
	cvCircle(srcImage, cvPoint(CIRCLE_X, CIRCLE_Y), CIRCLE_R, CV_RGB(0, 255, 0), 3);
}
void FkImageProcessor::drawFingerTip(IplImage* srcImage, int detectHandCount, FkHand userHand[]){
	switch(detectHandCount){
	case 0:
		break;
	case 1:
		for(int i =0 ; i < userHand[0].detectFingerCount ; i++)
			cvCircle(srcImage, userHand[0].finger[i].fingerTip, 3, CV_RGB(255, 0, 0), 2);
		break;
	case 2:
		for(int i =0 ; i < userHand[0].detectFingerCount ; i++)
			cvCircle(srcImage, userHand[0].finger[i].fingerTip, 3, CV_RGB(255, 0,0 ), 2);
		for(int i =0 ; i < userHand[1].detectFingerCount ; i++)
			cvCircle(srcImage, userHand[1].finger[i].fingerTip, 3, CV_RGB(0, 0,255 ), 2);
	}
}