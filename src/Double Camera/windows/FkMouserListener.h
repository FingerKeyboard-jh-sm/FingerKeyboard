#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_MOUSE_
#define FK_MOUSE_
#include"FkMessage.h"

class FkMouse{
	bool bLButtonDown;
	bool bRButtonDown;
	bool isTop;
public:
	FkMouse();
	void setLButtonDown();
	void setLButtonUp();
	void setRButtonDown();
	void setRButtonUp();
	void setFocusTop();
	void setFocusBottom();
	bool focusIsTop();
	bool getLButtonDownState();
	bool getRButtonDownState();
};
class FkMouseListener{
	static FkMouse mouse;
	static CvRect mouseDragArea;
	static CvPoint originPoint;
	static CvPoint benchmarkPoint;
	static FkMessage* message;
	static CvSize camResolution;
public :
	FkMouseListener(CvSize camResolution);
	FkMouse getMouse();
	CvRect	getMouseDragArea();
	bool	isMouseDragSize();
	bool	isSettingROITop();
	bool	isSettingROIBottom();
	//bool	isAdjustCorner();
	void	setMessenger(FkMessage* messenger);
	void	resetMouseDragArea();
	void	setBenchmarkPoint();
	static	void mouseClickEvent(int mEvent, int x, int y, int flags, void* param);
	~FkMouseListener();
};
#endif