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