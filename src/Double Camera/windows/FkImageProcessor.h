#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_IMAGE_PROC_
#define FK_IMAGE_PROC_
#include"FkMouserListener.h"
#include"FkPaperKeyboard.h"

class FkImageProcessor{
public:
	void paperAreaDraggingImage(IplImage* srcImage, FkMouseListener mouseListener);
	void drawPaperKeyboardCorner(IplImage* srcImage);
	void drawMaskTop(IplImage* srcImage);
	void drawMaskBottom(IplImage* srcImage);
	//ROI ¼³Á¤
	void drawSelectedArea(IplImage* srcImage, CvRect rect);
};
#endif