#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<iostream>
#include<fstream>
#include <signal.h>
//#include<stdlib.h>
#ifndef FK_PAPER_
#define FK_PAPER_
#include"FkKeyButtonProperty.h"
#define CLOCKWISE_1 1
#define CLOCKWISE_7 2
#define CLOCKWISE_5 3
#define CLOCKWISE_11 0

#define DIVISIONNUM0 16
#define DIVISIONNUM1 14
#define DIVISIONNUM2 14
#define DIVISIONNUM3 13
#define DIVISIONNUM4 12
#define DIVISIONNUM5 11

extern int sm_fd[2];
extern char sm_buf[40];
extern int _proc_handle;

using namespace std;

class FkKeyButton{
	KeyId keyId;
	KeyState keyState;
	CvRect keyLocation;
public:
	FkKeyButton();
	void setKeyLocation(int x, int y, int width, int height);
	void setKeyId(KeyId keyId);
	void keyAction();
	void setPress();
	void setNone();
	void setHold();
	void setRelease();
	KeyId getKeyId();
	KeyState getKeyState();
	CvRect getKeyLocation();
#ifdef _WINDOWS
	static void initSpecailKey();
#endif
};
class FkPaperKeyboard{
protected:
	int keyButtonCount;
public:
	int pressedKey;
	int holdKey;
	FkKeyButton* keyButton;
	CvPoint2D32f* keyButtonCorner;
	static CvPoint2D32f keyboardCorner[4];
	//static CvSeq * keyboardContour;
	static IplImage* keyboardMaskTop;
	static IplImage* keyboardMaskBottom;
	int getKeyButtonCornerCount();
	CvPoint2D32f getKeyButtonCorner(int index);
	CvPoint2D32f* getPoint();
	void setKeyboardCorner(CvPoint2D32f* corner);
	void sortPaperKeyboardCorner();
	void cornerSortingY(int startIndex, int cornerCount);
	void cornerSortingX(int startIndex, int cornerCount);
	
	virtual void initKeyButtonCorner()= 0;
	virtual void setKeyButton(IplImage* srcImage) = 0;
	virtual void setKeyButtonImage(IplImage* srcImage, IplImage* dstImage) = 0;
	virtual FkKeyButton* getKeyButton() = 0;
};
class FkPaperKeyboard_TypeA :public FkPaperKeyboard{
	FkKeyButton keyButtonDivisionY1[16];
	FkKeyButton keyButtonDivisionY2[14];
	FkKeyButton keyButtonDivisionY3[14];
	FkKeyButton keyButtonDivisionY4[13];
	FkKeyButton keyButtonDivisionY5[12];
	FkKeyButton keyButtonDivisionY6[10];
	int divisionNum;
public:
	FkPaperKeyboard_TypeA();
	void initKeyButtonCorner();
	void setKeyboardCorner(CvPoint2D32f* corner);
	void setKeyButton(IplImage* srcImage);
	void cornerVerification(IplImage* srcImage);
	void detectKeyButtonCorner(IplImage* srcImage);
	void setKeyButtonArea(CvPoint2D32f* corners, int startIndex, int keyCount);
	void setDirectionKeyButtonArea(CvPoint2D32f* corners, int startIndex, int next, int index);
	void setKeyButtonImage(IplImage* srcImage, IplImage* dstImage);
	FkKeyButton* getKeyButton();
	~FkPaperKeyboard_TypeA();
};
#endif