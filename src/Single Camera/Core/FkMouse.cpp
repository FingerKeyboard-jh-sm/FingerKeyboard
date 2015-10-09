/**
* @file FkMouse.cpp
* @author �Ѽ����б� ��ǻ�Ͱ��а� ������(jinhuk1313@gmail.com)	
* @brief ���콺
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
