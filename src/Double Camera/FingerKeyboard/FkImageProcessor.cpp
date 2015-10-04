#include "FkImageProcessor.h"

void FkImageProcessor::paperAreaDraggingImage(IplImage* srcImage, FkMouseListener mouseListener){
	cvSetImageROI(srcImage, mouseListener.getMouseDragArea());
	cvAddS(srcImage, cvScalar(200,0,0), srcImage);
	cvRectangleR(srcImage, cvRect(0, 0, mouseListener.getMouseDragArea().width, mouseListener.getMouseDragArea().height), CV_RGB(51, 153, 255),2);
	cvResetImageROI(srcImage);
}
void FkImageProcessor::drawPaperKeyboardCorner(IplImage* srcImage){
	for(int i = 0 ; i < 4 ; i++)
		cvCircle(srcImage, cvPointFrom32f(FkPaperKeyboard::keyboardCorner[i]), 2, CV_RGB(255, 0, 0), 2);
}
//void FkImageProcessor::drawPaperKeyboardContour(IplImage* srcImage){
//	//cvRectangleR(srcImage, FkPaperKeyboard::keyboardContour, CV_RGB(255,0,0));
//	cvDrawContours(srcImage, FkPaperKeyboard::keyboardContour, CV_RGB(0,255,0), CV_RGB(255,0,0), 0, 1, CV_AA);
//}
void FkImageProcessor::drawMaskTop(IplImage* srcImage){
	cvSet(srcImage, cvScalar(200,0,0), FkPaperKeyboard::keyboardMaskTop);
}
void FkImageProcessor::drawMaskBottom(IplImage* srcImage){
	//IplImage *maskImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, 3);
	//cvCvtColor(FkPaperKeyboard::keyboardMaskBottom, maskImage, CV_GRAY2RGB);
	//cvCopy(maskImage, srcImage, FkPaperKeyboard::keyboardMaskBottom);
	//cvSet(srcImage, cvScalar(200,0,0), FkPaperKeyboard::keyboardMaskBottom);
}
void FkImageProcessor::drawSelectedArea(IplImage* srcImage, CvRect rect){
	cvRectangleR(srcImage, rect, CV_RGB(0, 230, 0), 2);
}
//
////확정된 표시부분 직사각형
//void drawDetermineArea(IplImage* srcImage, CvRect rect){
//	cvRectangleR(srcImage, rect, CV_RGB(51, 153, 255), 2);
//}
