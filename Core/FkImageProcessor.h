#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_MOUSE_
#include"FkMouserListener.h"
#endif
#ifndef FK_PAPER_
#include"FkPaperKeyboard.h"
#endif
#include"FkCircleLocation.h"
#ifndef FK_POSTPRO_
#include"FkPostProcessor.h"
#endif

class FkImageProcessor{
public:
	void paperAreaDraggingImage(IplImage* srcImage, FkMouseListener mouseListener);
	void drawPaperKeyboardCorner(IplImage* srcImage);
	void drawSelectedArea(IplImage* srcImage, CvRect rect);
	void drawDetermineArea(IplImage* srcImage, CvRect rect);
	void drawHandInputCircle(IplImage* srcImage);
	void drawFingerTip(IplImage* srcImage,int detectHandCount, FkHand userHand[]);
};