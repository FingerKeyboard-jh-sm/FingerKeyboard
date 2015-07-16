#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_IMAGE_PROC_
#define FK_IMAGE_PROC_
#include"FkMouserListener.h"
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