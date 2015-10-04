#include"FkMouserListener.h"
FkMouse::FkMouse(){
	bLButtonDown = false;
	bRButtonDown = false;
}
void FkMouse::setLButtonDown(){
	this->bLButtonDown = true;
}
void FkMouse::setLButtonUp(){
	this->bLButtonDown = false;
}
void FkMouse::setRButtonDown(){
	this->bRButtonDown = true;
} 
void FkMouse::setRButtonUp(){
	this->bRButtonDown = true;
}
void FkMouse::setFocusTop(){
	this->isTop = true;
}
void FkMouse::setFocusBottom(){
	this->isTop = false;
}
bool FkMouse::focusIsTop(){
	return isTop;
}
bool FkMouse::getLButtonDownState(){
	return this->bLButtonDown;
}
bool FkMouse::getRButtonDownState(){
	return this->bRButtonDown;
}
