/**
* @file FkPostProcessor.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 후반부 처리를 위한 FkPostProcessor Class 정의
*/
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
#include"FkDimensionalProperty.h"

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
	CvMemStorage* tempStorage;

public:
	CvSeq* hull;
	CvPoint center;
	FkFinger finger[5];
	CvSeq* defect;
	CvConvexityDefect defectArray[100];
	CvPoint points[100];
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
	bool isFingerPressButton();
	bool isPressKey(FkKeyButton button);
	CvPoint getPressFingerLocation();
	FkHand();
	~FkHand();

	void calcCenter();
};
class FkFingerTipDetector{
	CvSize size;
	IplImage* transImage;
	IplImage* splitImage;
	IplImage* bgSplitImage;
	IplImage* handMasking;
	IplImage* backProImage;
	IplImage* handBinaryImage;
	IplImage* cp_handBinaryImage;
	CvMemStorage* storage;
	CvSeq* contour;
	CvRect selectedArea;

public:
	FkHand userHand[2];
	int detectHandCount;
	FkFingerTipDetector();
	void getHandBinaryImage(IplImage* srcImage, IplImage* bgImage, CvHistogram* skinColorHistogram );
	void detectHandContour(CvRect selectedArea);
	void detectFingerTip();
	void detectFingerTip(IplImage* srcImage);
	void determineSingleHandFingerTip();
	void determineDoubleHandFingerTip();
	void determineFingerTip(int height);
	void resetData();
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