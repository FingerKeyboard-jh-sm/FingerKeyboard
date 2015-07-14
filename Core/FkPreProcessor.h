#include<opencv\cv.h>
#include<opencv\highgui.h>
#include"FkPaperKeyboard.h"
#include"FkMouserListener.h"

class FkPaperKeyboardRecognizer{
	CvRect selectedPaperArea;
	FkPaperKeyboard* paperKeyboard;
public:
	FkPaperKeyboardRecognizer(int keyboardType);
	void setSelectedPaperKeyboard(CvRect selectedArea);
	CvRect getSelectedPaperKeyboard();
	void setPaperKeyboardCorner(IplImage* srcImage, FkMouseListener mouseListener);
	void setKeyboardCorner(CvPoint2D32f* corner);
	void setKeyButton(IplImage* srcImage);
	void showKeyButton(IplImage* srcImage);
	FkPaperKeyboard* getPaperKeyboard();
	IplImage* buttonImage;
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
	FkPreprocessor(int keyboardType);
	
};