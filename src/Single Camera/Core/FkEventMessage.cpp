/**
* @file FkEventMessage.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief Message Queue에 전달되는 키 이벤트 메세지
*/
#include"FkEventMessage.h"
KeyId FkEventMessage::getId(){
	return this->id;
}
KeyState FkEventMessage::getState(){
	return this->state;
}
FkEventMessage::FkEventMessage(KeyId id, KeyState state){
	this->id = id;
	this->state = state;
}
FkEventMessage::FkEventMessage(){

}