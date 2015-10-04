#include<opencv/cv.h>
#include<opencv/highgui.h>
#ifndef FK_PRE_PROC_
#define FK_PRE_PROC_
/*
#define KB_WHITE_LOW_SCALAR cvScalar(0,0,210)
#define KB_WHITE_HIGH_SCALAR cvScalar(255,70,255)
#define KB_BLACK_LOW_SCALAR cvScalar(0,30,50)
#define KB_BLACK_HIGH_SCALAR cvScalar(255,30,30)
*/
//
//#define KB_REGION_LOW_SCALAR cvScalar(45)
//#define KB_REGION_HIGH_SCALAR cvScalar(150)

//0~130 --> 0~100
#define KB_REGION_LOW_SCALAR cvScalar(0)
#define KB_REGION_HIGH_SCALAR cvScalar(100)

#include"FkPaperKeyboard.h"
#include"FkMouserListener.h"

class FkPaperKeyboardRecognizer{
	//A4 사각형 
	CvRect selectedPaperAreaBottom;
	FkPaperKeyboard* paperKeyboard;
	IplImage* buttonImage;
public:
	FkPaperKeyboardRecognizer(int keyboardType, CvSize camResolution);
	void setSelectedPaperKeyboardBottom(CvRect selectedArea);
	CvRect getSelectedPaperKeyboardBottom();
	bool setPaperKeyboardCornerTop(IplImage* srcImage);
	int setPaperKeyboardContourBottom(IplImage* srcImage, FkMouseListener mouseListener);
	void setKeyboardCorner(CvPoint2D32f* corner);
	//void setKeyboardContour(CvRect contour);
	//void setKeyboardContour(CvSeq* contour);
	void setKeyboardMaskTop(IplImage* keyboardMaskTop);
	void setKeyboardMaskBottom(IplImage* keyboardMaskBottom);
	void setKeyButton(IplImage* srcImage);
	void setKeyButtonImage(IplImage* srcImage);
	FkKeyButton* getKeyButton();
	FkPaperKeyboard* getPaperKeyboard();
	void showButtonImage();
	~FkPaperKeyboardRecognizer();
};

//class FkCameraCalibrator{
//	CvFileStorage* camCalibrateReader;
//	CvFileStorage* camCalibrateWriter;
//	CvMat* cameraMat;
//	CvMat* distortionCoeffs; //왜곡 계수
//	bool camCalibrate;
//public:
//	FkCameraCalibrator();
//	~FkCameraCalibrator();
//	bool isCamCalibrated();
//	void readFile();
//	void cameraCalibration(IplImage* srcImage, FkPaperKeyboard* paperKeyboard);
//};
//class FkSkinColorDetector{
//	IplImage* transImage;
//	IplImage* splitImage;
//	
//public:
//	CvHistogram* skinColorHistogram;
//	FkSkinColorDetector();
//	void createSkinColorHistogram(IplImage* srcImage);
//};
class FkPreprocessor{
public:
	FkPaperKeyboardRecognizer paperKeyboardRecognizer;
	//FkCameraCalibrator cameraCalibrator;
	//FkSkinColorDetector skinColorDetector;
	FkPreprocessor(int keyboardType, CvSize camResolution);
};
#endif