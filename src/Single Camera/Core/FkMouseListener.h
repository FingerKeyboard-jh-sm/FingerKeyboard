/**
* @file FkMouseListener.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief FkMouseListener Class 정의
*/
#ifdef WIN32
#include<opencv\cv.h>
#include<opencv\highgui.h>
#else
#include<cv.h>
#include<highgui.h>
#endif
#ifndef FK_MOUSE_
#define FK_MOUSE_
#include"FkMessage.h"
#include"FkProgramState.h"
#include"FkPaperKeyboard.h"
using namespace std;
class FkMouse{
	bool bLButtonDown;
	bool bRButtonDown;
public:
	FkMouse();
	void setLButtonDown();
	void setLButtonUp();
	void setRButtonDown();
	void setRButtonUp();
	bool getLButtonDownState();
	bool getRButtonDownState();
};
class FkMouseListener{
	static FkMouse mouse;
	static CvRect mouseDragArea;
	static CvPoint originPoint;
	static CvPoint benchmarkPoint;
	static FkMessage* message;
public :
	FkMouseListener();
	FkMouse getMouse();
	CvRect	getMouseDragArea();
	bool	isMouseDragSize();
	bool	isSettingROI();
	bool	isAdjustCorner();
	void	setMessenger(FkMessage* messenger);
	void	resetMouseDragArea();
	void	setBenchmarkPoint();
	static	void mouseClickEvent(int mEvent, int x, int y, int flags, void* param);
	~FkMouseListener();
};
#endif