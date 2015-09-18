#ifdef WIN32
#include<opencv\cv.h>
#include<opencv\highgui.h>
#else
#include<cv.h>
#include<highgui.h>
#endif
#ifndef FK_POST_PROC_
#define FK_POST_PROC_
#include"FkPaperKeyboard.h"
#define OVERLAP_HAND_AREA 50000
#define MAX_HAND_AREA 40000
#define MIN_HAND_AREA 3000
#define MIN_FINGER_DEPTH 30
class FkFinger{
	bool downOrientMotion;
	bool validMotion;
	double motionVector;
	double motionVectorAccumulation;
public:
	FkFinger* prevFinger;
	CvPoint fingerTip;
	void setPrevFinger();
	void fingerCopy(FkFinger* finger);
	void setValidMotion();
	void setMotionVector();
	void initAttribute();
	bool isMotion();
	bool isDownMotion();
	bool isFingerInButton(FkKeyButton button);
	double getmotionVectorAccumulation();
	FkFinger();
	~FkFinger();
};
class FkHand{
	CvMemStorage* handStorage;
	CvMemStorage* hullStorage;
	CvSeq* hull;
public:
	CvPoint handCenter;
	FkFinger finger[5];
	CvSeq* defect;
	CvConvexityDefect defectArray[100];
	int pressFinger;
	double handArea;
	int detectFingerCount;
	int prevDetectFingerCount;
	CvSeq* handContour;
	void setHandArea(double handArea);
	void setHandContour(CvSeq* contour);
	void getHandDefect();
	int getDefectTotal();
	void convertArray();
	void arrayMemSet();
	void correctPrevFingerTipIndex();
	void setValidMotionVector();
	void setFingerMotionVector();
	void setPrevDetectFingerCount();
	void resetFingerAttribute();
	bool isAllFingerDownMotion();
	void determineMotion();
	void setHandCenter(CvRect selectedArea);
	bool isFingerPressButton();
	bool isPressKey(FkKeyButton button);
	CvPoint getPressFingerLocation();
	FkHand();
	~FkHand();
};
class FkFingerTipDetector{
	CvSize size;
	IplImage* transImage;
	IplImage* splitImage;
	IplImage* bgSplitImage;
	IplImage* handMasking;
	IplImage* backProImage;
	IplImage* handBinaryImage;
	CvMemStorage* storage;
	CvSeq* contour;
	CvRect selectedArea;

public:
	FkHand userHand[2];
	int detectHandCount;
	FkFingerTipDetector();
	void getHandBinaryImage(IplImage* srcImage, IplImage* bgImage, CvHistogram* skinColorHistogram );
	void detectHandContour(CvRect selectedArea);
	void detectFingerTip(IplImage* srcImage);
	void determineSingleHandFingerTip();
	void determineDoubleHandFingerTip();
	void resetData();
	void setHandCenterPoint();
	void detectFingerTip2();
	void calcMotionProperty();
	~FkFingerTipDetector();
};
class FkKeyButtonEventListener{
	FkPaperKeyboard* paperKeyboard;
	FkHand* userHand[2];
	bool inputAvailable;
	double inputStartingPoint;
	double captureFrame;
public:
	FkKeyButtonEventListener(FkHand* userHand_1,FkHand* userHand_2);
	void setPaperKeyboardType(FkPaperKeyboard* paperKeyboard);
	void keyEventProcessing();
	bool keyEvent(CvPoint fingerLocation);
	void setInputAvailable();
};
class FkPostProcessor{
public:
	FkFingerTipDetector fingerTipDetector;
	FkKeyButtonEventListener keyButtonEventListener;
	FkPostProcessor();

};
#endif