#include"FkPostProcessor.h"

FkKeyButtonEventListener::FkKeyButtonEventListener() {
	this->frameCnt = 0;
	this->preKeyButton = NULL;
	this->currentKeyButton = NULL;
	this->isSpecailKeyPressed = false;
}

void FkKeyButtonEventListener::keyEvent(FkKeyButton* eventKeyButton) {
	//����
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
			if(frameCnt==0) { // ó�� ���� ��
				currentKeyButton->setPress();
				currentKeyButton->keyAction();
				frameCnt++;
			}
			else if(frameCnt==20) { // ��� ���� ��
				currentKeyButton->setPress();
				currentKeyButton->keyAction();
			}
			else // �� �� �����µ� ���� �����ӿ� ������ ����
				frameCnt++;
		}
		if(isSpecailKeyPressed == true) {
			FkKeyButton::initSpecailKey();
			isSpecailKeyPressed = false;
		}
	}

	preKeyButton = currentKeyButton;
}

void FkKeyButtonEventListener::detachFinger() {
	this->frameCnt = 0;
	this->preKeyButton = NULL;
	this->currentKeyButton = NULL;
}
