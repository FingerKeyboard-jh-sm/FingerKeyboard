/**
* @file FkMouseListener.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 마우스 이벤트 처리
*/
#include"FkMouseListener.h"
FkMouse FkMouseListener::mouse;
CvRect FkMouseListener::mouseDragArea;
CvPoint FkMouseListener::originPoint;
CvPoint FkMouseListener::benchmarkPoint;
FkMessage* FkMouseListener::message;
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
void FkMouseListener::setMessenger(FkMessage* messenger){
	this->message = messenger;
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
			message->showMessage("MESSAGE : 검출된 종이 키보드의 코너를 확인합니다.");//<<endl;
			FkCurrentMode::state = SET_KB_CORNER;
		}
		else if(FkCurrentMode::state == CONFIRM_KB_CORNER){
			FkCurrentMode::state = SET_KB_BUTTON;
			message->showMessage("MESSAGE : 종이 키보드의 코너가 설정되었습니다. 초록색 원 안에 손을 올려놓으세요. 사용자 피부색을 계산합니다.");
		}
		else if(FkCurrentMode::state  == CATCH_KB_CORNER){
			mouse.setLButtonDown();
			if(mouseDragArea.x < x && mouseDragArea.x + mouseDragArea.width > x){
				if(mouseDragArea.y < y && mouseDragArea.y + mouseDragArea.height > y){
					message->showMessage("MESSAGE : 코너의 위치를 조정합니다.");
					FkCurrentMode::state = MOVE_KB_CORNER;
				}
			}
		}
		else if(FkCurrentMode::state == WAIT_HAND){
			message->showMessage("MESSAGE : 타이핑이 가능합니다.");
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
				message->showMessage("MESSAGE : 종이 키보드의 영역을 확인합니다.");
			}
		}
		else if(FkCurrentMode::state  == MOVE_KB_CORNER){
			mouse.setLButtonUp();
			message->showMessage("MESSAGE : 종이 키보드의 코너를 확인합니다.");
			FkCurrentMode::state  = CONFIRM_KB_CORNER;
		}
		break;
	case CV_EVENT_RBUTTONDOWN: 
		if(FkCurrentMode::state == CONFIRM_KB_REGION){
			message->showMessage("MESSAGE : 종이 키보드의 영역을 재설정합니다.");
			mouseDragArea.width = 0;
			mouseDragArea.height = 0;
			mouseDragArea.x = 0;
			mouseDragArea.y = 0;
			FkCurrentMode::state = SET_KB_REGION;
		}
		else if(FkCurrentMode::state == CONFIRM_KB_CORNER){
			message->showMessage("MESSAGE : 종이 키보드의 코너를 선택합니다.");

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
							message->showMessage("MESSAGE : 종이 키보드의 코너를 선택되었습니다.");
							break;
					}
				}
				if(i == 3){
					message->showMessage("MESSAGE : 종이 키보드의 코너 선택에 실패하였습니다.");
					FkCurrentMode::state = CONFIRM_KB_CORNER;
				}
			}
		}
		break;
	}
}
