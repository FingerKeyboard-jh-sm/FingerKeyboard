#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_PAPER_
#define FK_PAPER_
#include"FkKeyButtonProperty.h"
#include"FkMessageQueue.h"
#define CLOCKWISE_1 1
#define CLOCKWISE_7 2
#define CLOCKWISE_5 3
#define CLOCKWISE_11 0


class FkKeyButton{
	KeyId  keyId;
	KeyState keyState;
	CvRect keyLocation;
	static FkMessageQueue* messageQueue;
public:
	FkKeyButton();
	void setKeyLocation(int x, int y, int width, int height);
	void setKeyId(KeyId keyId);
	void keyAction();
	void setPress();
	void setNone();
	void setHold();
	void setRelease();
	static void setMessageQueue(FkMessageQueue* messageQueue);
	KeyId getKeyId();
	KeyState getKeyState();
	CvRect getKeyLocation();
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
	int getKeyButtonCornerCount();
	CvPoint2D32f getKeyButtonCorner(int index);
	CvPoint2D32f* getPoint();
	void setKeyboardCorner(CvPoint2D32f* corner);
	void sortPaperKeyboardCorner();
	void cornerSortingY(int startIndex, int cornerCount);
	void cornerSortingX(int startIndex, int cornerCount);
	
	virtual void initKeyButtonCorner()= 0;
	virtual void setKeyButton(IplImage* srcImage, CvRect selectedPaperArea) =0;
	virtual void setKeyButtonImage(IplImage* srcImage, IplImage* dstImage) = 0;
};
class FkPaperKeyboard_TypeA :public FkPaperKeyboard{
public:
	FkPaperKeyboard_TypeA(FkMessageQueue* messageQueue);
	void initKeyButtonCorner();
	void setKeyboardCorner(CvPoint2D32f* corner);
	void setKeyButton(IplImage* srcImage, CvRect selectedPaperArea);
	void cornerVerification(IplImage* srcImage);
	void detectKeyButtonCorner(IplImage* srcImage);
	void setKeyButtonArea(CvPoint2D32f* corners, int startIndex, int keyCount);
	void setDirectionKeyButtonArea(CvPoint2D32f* corners, int startIndex, int next, int index);
	void setKeyButtonImage(IplImage* srcImage, IplImage* dstImage);
	~FkPaperKeyboard_TypeA();
};
#endif