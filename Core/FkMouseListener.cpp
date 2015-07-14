#include"FkMouserListener.h"
#include"FkProgramState.h"
#include"FkPaperKeyboard.h"
using namespace std;
FkMouse FkMouseListener::mouse;
CvRect FkMouseListener::mouseDragArea;
CvPoint FkMouseListener::originPoint;
CvPoint FkMouseListener::benchmarkPoint;

FkMouseListener::~FkMouseListener(){
}
bool FkMouseListener::isSettingROI(){
	return FkCurrentMode::state  == SET_KB_REGION && mouse.getLButtonDownState() && isMouseDragSize();
}
bool FkMouseListener::isAdjustCorner(){
	return FkCurrentMode::state == ADJUST_KB_CORNER && mouse.getRButtonDownState() && isMouseDragSize();
}
void FkMouseListener::resetMouseDragArea(){
	mouseDragArea.width = 0;
	mouseDragArea.height = 0;
	mouseDragArea.x = 0;
	mouseDragArea.y = 0;
}
FkMouseListener::FkMouseListener(){

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
	IplImage* targetImage = (IplImage*) param;
	static int cornerIndex;
	static CvPoint2D32f adjustPoint;
	//std::cout<<"asdasd"<<std::endl;
	if(!targetImage)
		return;
	if((FkCurrentMode::state == SET_KB_REGION && mouse.getLButtonDownState())||
		FkCurrentMode::state == ADJUST_KB_CORNER && mouse.getRButtonDownState()){
			mouseDragArea.x = MIN(x, originPoint.x);
			mouseDragArea.y = MIN(y, originPoint.y);
			mouseDragArea.width = mouseDragArea.x + CV_IABS(x - originPoint.x);
			mouseDragArea.height = mouseDragArea.y + CV_IABS(y- originPoint.y);

			mouseDragArea.x = MAX(mouseDragArea.x, 0);
			mouseDragArea.y = MAX(mouseDragArea.y, 0);
			mouseDragArea.width = MIN(mouseDragArea.width, targetImage->width);
			mouseDragArea.height = MIN(mouseDragArea.height, targetImage->height);
			mouseDragArea.width -= mouseDragArea.x;
			mouseDragArea.height -= mouseDragArea.y;
	}
	switch(mEvent){
	case CV_EVENT_LBUTTONDOWN:
		if(FkCurrentMode::state  == SET_KB_REGION){
			originPoint = cvPoint(x, y);
			mouseDragArea = cvRect(x, y, 0, 0);
			mouse.setLButtonDown();
		}
		else if(FkCurrentMode::state == CONFIRM_KB_REGION){
			cout<<"MESSAGE : Setting ROI"<<endl;
			//AfxMessageBox(_T("Setting ROI"), MB_OK | MB_ICONEXCLAMATION | MB_APPLMODAL);
			//MessageBox(NULL,_T("Setting ROI"),_T("Setting ROI"), MB_OK)

			FkCurrentMode::state = SET_KB_CORNER;
		}
		else if(FkCurrentMode::state == CONFIRM_KB_CORNER){
			FkCurrentMode::state = SET_KB_BUTTON;
			cout<<"MESSAGE : CORNER CONFIRM"<<endl;

		}
		else if(FkCurrentMode::state  == CATCH_KB_CORNER){
			mouse.setLButtonDown();
			if(mouseDragArea.x < x && mouseDragArea.x + mouseDragArea.width > x){
				if(mouseDragArea.y < y && mouseDragArea.y + mouseDragArea.height > y){
					cout<<"MESSAGE : Corner Position Adjusting"<<endl;
					FkCurrentMode::state = MOVE_KB_CORNER;
				}
			}
		}
		else if(FkCurrentMode::state == WAIT_HAND){
			cout<<"MESSAGE : CALCUALATE SKIN COLOR"<<endl;

			FkCurrentMode::state = SET_HIST;
		}
		break;

	case CV_EVENT_MOUSEMOVE:
		if(FkCurrentMode::state == MOVE_KB_CORNER && mouse.getLButtonDownState()){
			adjustPoint.x = (float)(x - benchmarkPoint.x);
			adjustPoint.y = (float)(y - benchmarkPoint.y);
			FkPaperKeyboard::keyboardCorner[cornerIndex] = adjustPoint;
		}
		break;
	case CV_EVENT_LBUTTONUP:
		if(FkCurrentMode::state  == SET_KB_REGION){
			mouse.setLButtonUp();
			if(mouseDragArea.width > 0 && mouseDragArea.height >0){
				FkCurrentMode::state  = CONFIRM_KB_REGION;
				cout<<"MESSAGE : ROI Confirm"<<endl;
			}
		}
		else if(FkCurrentMode::state  == MOVE_KB_CORNER){
			mouse.setLButtonUp();
			cout<<"MESSAGE : Corner Confirm"<<endl;
			FkCurrentMode::state  = CONFIRM_KB_CORNER;
		}
		break;
	case CV_EVENT_RBUTTONDOWN: 
		if(FkCurrentMode::state == CONFIRM_KB_REGION){
			cout<<"MESSAGE : Reset ROI"<<endl;
			mouseDragArea.width = 0;
			mouseDragArea.height = 0;
			mouseDragArea.x = 0;
			mouseDragArea.y = 0;
			FkCurrentMode::state = SET_KB_REGION;
		}
		else if(FkCurrentMode::state == CONFIRM_KB_CORNER){
			cout<<"MESSAGE : Adjust Paper Coner"<<endl;

			originPoint = cvPoint(x, y);
			mouseDragArea = cvRect(x, y, 0, 0);
			mouse.setRButtonDown();
			FkCurrentMode::state = ADJUST_KB_CORNER;
		}
		else if(FkCurrentMode::state == ADJUST_KB_CORNER){
			originPoint = cvPoint(x, y);
			mouseDragArea = cvRect(x, y, 0, 0);
			mouse.setRButtonDown();
		}

		break;
	case CV_EVENT_RBUTTONUP:
		if(FkCurrentMode::state == ADJUST_KB_CORNER){
			mouse.setRButtonUp();
			for(int i = 0 ; i < 4 ; i++){
				if(FkPaperKeyboard::keyboardCorner[i].x + benchmarkPoint.x > (mouseDragArea.x)
					&& FkPaperKeyboard::keyboardCorner[i].x + benchmarkPoint.x < (mouseDragArea.x + mouseDragArea.width)){
					if(FkPaperKeyboard::keyboardCorner[i].y + benchmarkPoint.y > (mouseDragArea.y)
						&& FkPaperKeyboard::keyboardCorner[i].y + benchmarkPoint.y < (mouseDragArea.y + mouseDragArea.height)){
							cornerIndex = i;
							adjustPoint = FkPaperKeyboard::keyboardCorner[i];
							FkCurrentMode::state = CATCH_KB_CORNER;
							cout<<"MESSAGE : Corner selected"<<endl;
							break;
					}
				}
				if(i == 3){
					cout<<"MESSAGE : failed catch corner"<<endl;
					FkCurrentMode::state = CONFIRM_KB_CORNER;
				}
			}
		}
		break;
	}
}
