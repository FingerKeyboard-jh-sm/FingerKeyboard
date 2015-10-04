#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_POST_PROC_
#define FK_POST_PROC_
#define SKIN_S_MIN_TOP cvScalar(0,133,80)
#define SKIN_S_MAX_TOP cvScalar(255,160,158)
#define SKIN_S_MIN_BOTTOM cvScalar(0,146,80)
#define SKIN_S_MAX_BOTTOM cvScalar(255,180,160)

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
	void initFingerTipPoint();
	void setkeyboardMaskTop(IplImage *srcImage, IplImage* keyboardMaskTop);
	void setkeyboardMaskBottom(IplImage *srcImage, IplImage* keyboardMaskBottom, CvRect selectedPaperArea);
	void setkeyboardMaskRectBottom();
	CvPoint getFingerTipPoint();
	bool isTouchKeyboard(IplImage* bottomImage, CvRect selectedPaperArea);
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