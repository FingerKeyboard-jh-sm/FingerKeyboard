#include<opencv/cv.h>
#include<opencv/highgui.h>
#ifndef FK_POST_PROC_
#define FK_POST_PROC_
//128 ¡Â Cr ¡Â 170, 73 ¡Â Cb ¡Â 158
//#define skinSmin cvScalar(0,130,73)
//#define skinSmax cvScalar(255,170,158)
//skinSminTop 0,133,80  // skinmaxTop 255,160,158 // skinSminBottom 0,140,80 // skinSmaxBottom 255,160,158
#define skinSminTop cvScalar(0,133,80)
#define skinSmaxTop cvScalar(255,160,158)
#define skinSminBottom cvScalar(0,140,80)
#define skinSmaxBottom cvScalar(255,160,158)

#include"FkPaperKeyboard.h"

class FkFingerTipDetector{
	IplImage* keyboardMaskTop;
	IplImage* keyboardMaskBottom;
	CvRect keyboardMaskRectBottom;
	int fingerXBottom;
	int fingerXTop;
	CvRect fingerROITop;
	CvPoint fingerTipPoint;

	FkKeyButton* keyButtonDivision[6];
	int divisionNum;
	int divisionCnt[6];
public:
	FkFingerTipDetector(CvSize camResolution);
	~FkFingerTipDetector();
	//void setkeyboardMaskBottom(IplImage *srcImage, CvSeq * keyboardContour, CvRect selectedPaperArea);
	void initFingerTipPoint();
	void setkeyboardMaskTop(IplImage *srcImage, IplImage* keyboardMaskTop);
	void setkeyboardMaskBottom(IplImage *srcImage, IplImage* keyboardMaskBottom, CvRect selectedPaperArea);
	void setkeyboardMaskRectBottom();
	CvPoint getFingerTipPoint();
	bool isTouchKeyboard(IplImage* bottomImage, CvRect selectedPaperArea, int a, int b, int c, int d);
	void setFingerXTop();
	void setFingerROITop();
	void detectFingerTip(IplImage *topImage);
	void setKeyButtonDivision(FkKeyButton* keyButton);
	void setFingerTipDivision();
	void drawFingerTip(IplImage *topImage, IplImage *bottomImage);
	FkKeyButton* getEventKey();
};
class FkKeyButtonEventListener{
	int frameCnt;
	FkKeyButton* preKeyButton;
	FkKeyButton* currentKeyButton;
	bool isSpecailKeyPressed;
public:
	void keyEvent(FkKeyButton* eventKeyButton);
	void detachFinger();
	FkKeyButtonEventListener();
};
class FkPostprocessor{
public:
	FkFingerTipDetector fingerTipDetector;
	FkKeyButtonEventListener keyButtonEventListener;

	FkPostprocessor(CvSize camResolution);
	void keyEventProcessing();
};

#endif