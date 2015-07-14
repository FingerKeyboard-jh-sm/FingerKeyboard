#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_MOUSE_
#define FK_MOUSE_
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
public :
	FkMouseListener();
	FkMouse getMouse();
	CvRect	getMouseDragArea();
	bool	isMouseDragSize();
	bool	isSettingROI();
	bool	isAdjustCorner();
	void	resetMouseDragArea();
	void	setBenchmarkPoint();
	static	void mouseClickEvent(int mEvent, int x, int y, int flags, void* param);
	~FkMouseListener();
};
#endif 