/**
* @file FkPreProcessor.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 전반부 처리를 위한 FkPreProcessor 정의
*/
#ifdef WIN32
#include<opencv\cv.h>
#include<opencv\highgui.h>
#else
#include<cv.h>
#include<highgui.h>
#endif
#ifndef FK_PRE_PROC_
#define FK_PRE_PROC_
#include"FkPaperKeyboard.h"
#include"FkMouseListener.h"

class FkPaperKeyboardRecognizer{
	CvRect selectedPaperArea;
	FkPaperKeyboard* paperKeyboard;
public:
	FkPaperKeyboardRecognizer();
	void setSelectedPaperKeyboard(CvRect selectedArea);
	CvRect getSelectedPaperKeyboard();
	int setPaperKeyboardCorner(IplImage* srcImage, FkMouseListener mouseListener);
	void setKeyboardCorner(CvPoint2D32f* corner);
	void setKeyButton(IplImage* srcImage);
	void setKeyButtonImage(IplImage* srcImage);
	void setPaperKeyboard(FkPaperKeyboard* paperKeyboard);
	FkPaperKeyboard* getPaperKeyboard();
	IplImage* buttonImage;
	~FkPaperKeyboardRecognizer();
};
class FkCameraCalibrator{
	CvFileStorage* camCalibrateReader;
	CvFileStorage* camCalibrateWriter;
	CvMat* cameraMat;
	CvMat* distortionCoeffs;
	bool camCalibrate;
public:
	FkCameraCalibrator();
	~FkCameraCalibrator();
	bool isCamCalibrated();
	void readFile();
	void cameraCalibration(IplImage* srcImage, FkPaperKeyboard* paperKeyboard);
};
class FkSkinColorDetector{
	IplImage* transImage;
	IplImage* splitImage;
	
public:
	CvHistogram* skinColorHistogram;
	FkSkinColorDetector();
	void createSkinColorHistogram(IplImage* srcImage);
};
class FkPreprocessor{
public:
	FkPaperKeyboardRecognizer paperKeyboardRecognizer;
	FkCameraCalibrator cameraCalibrator;
	FkSkinColorDetector skinColorDetector;
	FkPreprocessor();
	
};
#endif