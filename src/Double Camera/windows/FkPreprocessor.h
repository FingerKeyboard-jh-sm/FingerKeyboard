#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_PRE_PROC_
#define FK_PRE_PROC_

//밝기에 따라 cr범위 수정
#define KB_REGION_LOW_SCALAR cvScalar(0)
#define KB_REGION_HIGH_SCALAR cvScalar(90)

#include"FkPaperKeyboard.h"
#include"FkMouserListener.h"

class FkPaperKeyboardRecognizer{
	//A4 사각형 
	CvRect selectedPaperAreaBottom;
	FkPaperKeyboard* paperKeyboard;
public:
	IplImage* buttonImage;
	IplImage* bottomMaskImage;
	FkPaperKeyboardRecognizer(int keyboardType, CvSize camResolution);
	void setSelectedPaperKeyboardBottom(CvRect selectedArea);
	CvRect getSelectedPaperKeyboardBottom();
	bool setPaperKeyboardCornerTop(IplImage* srcImage);
	bool setPaperKeyboardContourBottom(IplImage* srcImage, FkMouseListener mouseListener);
	void setKeyboardCorner(CvPoint2D32f* corner);
	void setKeyboardMaskTop(IplImage* keyboardMaskTop);
	void setKeyboardMaskBottom(IplImage* keyboardMaskBottom);
	void setKeyButton(IplImage* srcImage);
	void setKeyButtonImage(IplImage* srcImage);
	void setKeyMaskBottomImage(IplImage* srcImage);
	FkKeyButton* getKeyButton();
	FkPaperKeyboard* getPaperKeyboard();
	~FkPaperKeyboardRecognizer();
};

class FkPreprocessor{
public:
	FkPaperKeyboardRecognizer paperKeyboardRecognizer;
	FkPreprocessor(int keyboardType, CvSize camResolution);
};
#endif