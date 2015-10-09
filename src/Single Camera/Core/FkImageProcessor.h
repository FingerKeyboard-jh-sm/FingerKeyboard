/**
* @file FkImageProcessor.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 그리기 작업을 위한 Image Processor 정의
*/
#ifdef WIN32
#include<opencv\cv.h>
#include<opencv\highgui.h>
#else
#include<cv.h>
#include<highgui.h>
#endif
#ifndef FK_IMAGE_PROC_
#define FK_IMAGE_PROC_
#include"FkMouseListener.h"
#include"FkPaperKeyboard.h"
#include"FkCircleLocation.h"
#include"FkPostProcessor.h"
class FkImageProcessor{
public:
	void paperAreaDraggingImage(IplImage* srcImage, FkMouseListener mouseListener);
	void drawPaperKeyboardCorner(IplImage* srcImage);
	void drawSelectedArea(IplImage* srcImage, CvRect rect);
	void drawDetermineArea(IplImage* srcImage, CvRect rect);
	void drawHandInputCircle(IplImage* srcImage);
	void drawFingerTip(IplImage* srcImage,int detectHandCount, FkHand userHand[]);
};
#endif