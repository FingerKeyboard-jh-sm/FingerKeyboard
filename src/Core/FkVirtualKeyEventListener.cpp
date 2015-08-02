#include"FkVirtualKeyEventListener.h"
FkVirtualKeyEventListener::FkVirtualKeyEventListener(FkMessageQueue* messageQueue){
	this->messageQueue = messageQueue;
}
void FkVirtualKeyEventListener::run(){
	FkEventMessage message;
	while(1){
		message = messageQueue->dequeue();
		switch(message.getId()){










		}
	}
}
