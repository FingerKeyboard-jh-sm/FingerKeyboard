/**
* @file FkKeyButton.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 종이 키보드에 배치되는 키 버튼
*/
#include"FkPaperKeyboard.h"
FkMessageQueue* FkKeyButton::messageQueue;
void FkKeyButton::setMessageQueue(FkMessageQueue* messageQueue){
	FkKeyButton::messageQueue = messageQueue;
}
void FkKeyButton::setKeyLocation(int x, int y, int width, int height){
	this->keyLocation = cvRect(x, y, width, height);
}
CvRect FkKeyButton::getKeyLocation(){
	return keyLocation;
}
FkKeyButton::FkKeyButton(){
	this->keyState = KEY_STATE_NONE;
}
void FkKeyButton::setKeyId(KeyId keyId){
	this->keyId = keyId;
}
KeyId FkKeyButton::getKeyId(){
	return this->keyId;
}
KeyState FkKeyButton::getKeyState(){
	return this->keyState;
}
void FkKeyButton::setPress(){
	this->keyState = KEY_STATE_PRESS;
}
void FkKeyButton::setHold(){
	this->keyState = KEY_STATE_PRESS_HOLD;
}
void FkKeyButton::setRelease(){
	this->keyState = KEY_STATE_RELEASE;
}
void FkKeyButton::setNone(){
	this->keyState = KEY_STATE_NONE;
}
void FkKeyButton::keyAction(){
	FkEventMessage msg(this->keyId, this->keyState);
	messageQueue->enqueue(msg);
}
