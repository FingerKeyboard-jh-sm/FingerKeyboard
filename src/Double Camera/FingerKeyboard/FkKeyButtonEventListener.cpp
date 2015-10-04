#include"FkPostprocessor.h"

FkKeyButtonEventListener::FkKeyButtonEventListener() {
	this->frameCnt = 0;
	this->preKeyButton = NULL;
	this->currentKeyButton = NULL;
	this->isSpecailKeyPressed = false;
}

void FkKeyButtonEventListener::keyEvent(FkKeyButton* eventKeyButton) {
	//원본
	currentKeyButton = eventKeyButton;
	KeyId currentKeyId = currentKeyButton->getKeyId();
	if( currentKeyId == KEY_ID_LSHIFT || currentKeyId == KEY_ID_RSHIFT || 
		currentKeyId == KEY_ID_CTRL || currentKeyId == KEY_ID_ALT ) {
		if( currentKeyButton != preKeyButton ) {
			currentKeyButton->setPress();
			currentKeyButton->keyAction();
			isSpecailKeyPressed = true;
			frameCnt=1;
		}
		else {
			if(frameCnt==0) {
				if(isSpecailKeyPressed == true) {
					currentKeyButton->setNone();
					currentKeyButton->keyAction();
					isSpecailKeyPressed = false;
				}
				else {
					currentKeyButton->setPress();
					currentKeyButton->keyAction();
					isSpecailKeyPressed = true;
					frameCnt=1;
				}
			}
			else
				frameCnt++;
		}
	}
	else { 
		if(currentKeyButton != preKeyButton) {
			currentKeyButton->setPress();
			currentKeyButton->keyAction();
			frameCnt=1;
		}
		else if(currentKeyButton == preKeyButton) {
			if(frameCnt==0) { // 처음 눌릴 때
				currentKeyButton->setPress();
				currentKeyButton->keyAction();
				frameCnt++;
			}
			else if(frameCnt==20) { // 계속 누를 때
				currentKeyButton->setPress();
				currentKeyButton->keyAction();
			}
			else // 한 번 눌렀는데 여러 프레임에 잡힘을 방지
				frameCnt++;
		}
		if(isSpecailKeyPressed == true) {
			#ifdef _WINDOWS
			FkKeyButton::initSpecailKey();
			#endif
			isSpecailKeyPressed = false;
		}
	}

	preKeyButton = currentKeyButton;


	//currentKeyButton = eventKeyButton;
	//KeyId currentKeyId = currentKeyButton->getKeyId();
	//if( currentKeyId == KEY_ID_LSHIFT || currentKeyId == KEY_ID_RSHIFT || 
	//	currentKeyId == KEY_ID_CTRL || currentKeyId == KEY_ID_ALT ) {
	//	if( currentKeyButton != preKeyButton ) 
	//		frameCnt=0;
	//	else {
	//		if(frameCnt==1) {
	//			if(isSpecailKeyPressed == true) {
	//				currentKeyButton->setNone();
	//				currentKeyButton->keyAction();
	//				isSpecailKeyPressed = false;
	//			}
	//			else {
	//				currentKeyButton->setPress();
	//				currentKeyButton->keyAction();
	//				isSpecailKeyPressed = true;
	//			}
	//		}
	//	}
	//}
	//else { 
	//	if(currentKeyButton != preKeyButton) 
	//		frameCnt=0;
	//	else if(currentKeyButton == preKeyButton) {
	//		if(frameCnt==1) {
	//			currentKeyButton->setPress();
	//			currentKeyButton->keyAction();
	//			if(isSpecailKeyPressed == true) {
	//				FkKeyButton::initSpecailKey();
	//				isSpecailKeyPressed = false;
	//			}
	//		}
	//		else if(frameCnt>=20) { // 계속 누를 때
	//			currentKeyButton->setPress();
	//			currentKeyButton->keyAction();
	//		}	
	//	}
	//}
	//frameCnt++;
	//preKeyButton = currentKeyButton;
}

void FkKeyButtonEventListener::detachFinger() {
	this->frameCnt = 0;
	this->preKeyButton = NULL;
	this->currentKeyButton = NULL;
}
