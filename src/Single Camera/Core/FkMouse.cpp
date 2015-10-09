/**
* @file FkMouse.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 마우스
*/
#include"FkMouseListener.h"
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
bool FkMouse::getLButtonDownState(){
	return this->bLButtonDown;
}
bool FkMouse::getRButtonDownState(){
	return this->bRButtonDown;
}
