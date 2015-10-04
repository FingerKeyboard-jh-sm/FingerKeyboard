#include"FkMouserListener.h"
#include"FkProgramState.h"
#include"FkCamera.h"
//#include"FkPaperKeyboard.h"
#include<string>
using namespace std;
FkMouse FkMouseListener::mouse;
CvRect FkMouseListener::mouseDragArea;
CvPoint FkMouseListener::originPoint;
CvPoint FkMouseListener::benchmarkPoint;
FkMessage* FkMouseListener::message;
CvSize FkMouseListener::camResolution;

FkMouseListener::FkMouseListener(CvSize camResolution){
	this->camResolution = camResolution;
}
FkMouseListener::~FkMouseListener(){
}
bool FkMouseListener::isSettingROIBottom(){
	if(mouse.focusIsTop())
		return false;
	return FkCurrentMode::state == SET_KB_REGION_BOTTOM && mouse.getLButtonDownState() && isMouseDragSize();
}
void FkMouseListener::resetMouseDragArea(){
	mouseDragArea.width = 0;
	mouseDragArea.height = 0;
	mouseDragArea.x = 0;
	mouseDragArea.y = 0;
}
void FkMouseListener::setMessenger(FkMessage* messenger){
	this->message = messenger;
}
bool FkMouseListener::isMouseDragSize(){
	return this->mouseDragArea.width >0 && this->mouseDragArea.height > 0;
}
FkMouse FkMouseListener::getMouse(){
	return this->mouse;
}
CvRect FkMouseListener::getMouseDragArea(){
	return this->mouseDragArea;
}
void FkMouseListener::setBenchmarkPoint(){
	benchmarkPoint.x = mouseDragArea.x;
	benchmarkPoint.y = mouseDragArea.y;
}
void FkMouseListener::mouseClickEvent(int mEvent, int x, int y, int flags, void* param){
	char *topOrBottom = (char *)param;
	static int cornerIndex;
	static CvPoint2D32f adjustPoint;

	if(strcmp(topOrBottom, "TOP")) mouse.setFocusBottom();
	else mouse.setFocusTop();

	if(FkCurrentMode::state == SET_KB_REGION_BOTTOM && mouse.getLButtonDownState()){
			mouseDragArea.x = MIN(x, originPoint.x);
			mouseDragArea.y = MIN(y, originPoint.y);
			mouseDragArea.width = mouseDragArea.x + CV_IABS(x - originPoint.x);
			mouseDragArea.height = mouseDragArea.y + CV_IABS(y- originPoint.y);

			mouseDragArea.x = MAX(mouseDragArea.x, 0);
			mouseDragArea.y = MAX(mouseDragArea.y, 0);
			mouseDragArea.width = MIN(mouseDragArea.width, camResolution.width);
			mouseDragArea.height = MIN(mouseDragArea.height, camResolution.height);
			mouseDragArea.width -= mouseDragArea.x;
			mouseDragArea.height -= mouseDragArea.y;
	}
	switch(mEvent){
	case CV_EVENT_LBUTTONDOWN:
		switch(FkCurrentMode::state) {
		case SET_KB_REGION_BOTTOM:
			originPoint = cvPoint(x, y);
			mouseDragArea = cvRect(x, y, 0, 0);
			mouse.setLButtonDown();
			break;
		case CONFIRM_KB_REGION_BOTTOM:
			message->showMessage("MESSAGE : BOTTOM Setting ROI");
			FkCurrentMode::state = SET_KB_CONTOUR_BOTTOM;
			break;
		case CONFIRM_KB_CONTOUR_BOTTOM:
			FkCurrentMode::state = POSTPROCESS_INIT;
			message->showMessage("MESSAGE : INPUT_AVAILABLE");
			break;
		case CONFRIM_KB_BUTTON:
			FkCurrentMode::state = SET_KB_REGION_BOTTOM;
			break;
		}
		break;
	case CV_EVENT_LBUTTONUP:
		switch(FkCurrentMode::state) {
		case SET_KB_REGION_BOTTOM:
			mouse.setLButtonUp();
			if(mouseDragArea.width > 0 && mouseDragArea.height > 0){
				FkCurrentMode::state = CONFIRM_KB_REGION_BOTTOM;
				message->showMessage("MESSAGE : BOTTOM ROI Confirm");
			}
			break;
		}
		break;
	case CV_EVENT_RBUTTONDOWN: 
		switch(FkCurrentMode::state) {
		case SET_KB_BUTTON:
			message->showMessage("MESSAGE : TOP Reset ROI");
			FkCurrentMode::state = PREPROCESS_TOP;
			break;
		case CONFRIM_KB_BUTTON:
			FkCurrentMode::state = PREPROCESS_TOP;
			break;
		case CONFIRM_KB_REGION_BOTTOM:
		case CONFIRM_KB_CONTOUR_BOTTOM:
			message->showMessage("MESSAGE : BOTTOM Reset ROI");
			mouseDragArea.width = 0;
			mouseDragArea.height = 0;
			mouseDragArea.x = 0;
			mouseDragArea.y = 0;
			FkCurrentMode::state = SET_KB_REGION_BOTTOM;
			break;
		}
		break;
	}
}
