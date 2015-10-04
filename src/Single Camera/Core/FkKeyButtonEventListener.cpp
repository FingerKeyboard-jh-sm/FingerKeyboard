#include"FkPostProcessor.h"
FkKeyButtonEventListener::FkKeyButtonEventListener(FkHand* userHand_1,FkHand* userHand_2){
	userHand[0] = userHand_1;
	userHand[1] = userHand_2;
	inputAvailable = true;
	inputStartingPoint = 1;
	captureFrame = 0;
}
void FkKeyButtonEventListener::setPaperKeyboardType(FkPaperKeyboard* paperKeyboard){
	this->paperKeyboard = paperKeyboard;
}
void FkKeyButtonEventListener::keyEventProcessing(){
	int i;
	if(paperKeyboard->pressedKey != -1 && paperKeyboard->keyButton[paperKeyboard->pressedKey].getKeyState() == KEY_STATE_PRESS){
			if(inputAvailable){
				for(i = 0 ; i < 2 ; i++){
					if(userHand[i]->isPressKey(paperKeyboard->keyButton[paperKeyboard->pressedKey])){
						if(paperKeyboard->holdKey == -1){
							paperKeyboard->keyButton[paperKeyboard->pressedKey].setHold();
							inputStartingPoint = captureFrame +5;
							inputAvailable = false;

							paperKeyboard->holdKey = paperKeyboard->pressedKey;
						}
						break;
					}
					if(i== 1){
						paperKeyboard->keyButton[paperKeyboard->pressedKey].setNone();
						paperKeyboard->keyButton[paperKeyboard->pressedKey].keyAction();
						paperKeyboard->pressedKey = -1;
					}

				}
			}
			else{
				for(i = 0 ; i < 2 ; i++){
					if(userHand[i]->isPressKey(paperKeyboard->keyButton[paperKeyboard->pressedKey]))
						break;
					if(i== 1){
						paperKeyboard->keyButton[paperKeyboard->pressedKey].setNone();
						paperKeyboard->keyButton[paperKeyboard->pressedKey].keyAction();
						paperKeyboard->pressedKey = -1;
					}
				}
			}
		}

		if(paperKeyboard->holdKey != -1 && paperKeyboard->keyButton[paperKeyboard->holdKey].getKeyState() == KEY_STATE_PRESS_HOLD){
			if(inputAvailable){
				for(i = 0 ; i < 2 ; i++){
					if(userHand[i]->isPressKey(paperKeyboard->keyButton[paperKeyboard->holdKey])){
						paperKeyboard->keyButton[paperKeyboard->holdKey].keyAction();
						break;
					}
					else if(i==1)
						paperKeyboard->keyButton[paperKeyboard->holdKey].setRelease();
				}
			}
			else{
				for(i =0 ; i < 2 ; i++){
					if(userHand[i]->isPressKey(paperKeyboard->keyButton[paperKeyboard->holdKey]))
						break;
					else if(i == 1)
						paperKeyboard->keyButton[paperKeyboard->holdKey].setRelease();
				}
			}
		}
		else if(paperKeyboard->keyButton[paperKeyboard->holdKey].getKeyState() == KEY_STATE_RELEASE){
			paperKeyboard->keyButton[paperKeyboard->holdKey].keyAction();
			paperKeyboard->keyButton[paperKeyboard->holdKey].setNone();
			paperKeyboard->holdKey = -1;
		}
	for(int i = 0 ; i < 2 ; i++){
		if(userHand[i]->isAllFingerDownMotion()){
			userHand[i]->determineMotion();
			if(userHand[i]->isFingerPressButton() && inputAvailable)
				if(keyEvent(userHand[i]->getPressFingerLocation()))
					this->inputStartingPoint = captureFrame;
		}
	}
	captureFrame++;
}
void FkKeyButtonEventListener::setInputAvailable(){
	if(this->inputStartingPoint != 0 && this->inputStartingPoint + 5< captureFrame)
		inputAvailable = true;
}
bool FkKeyButtonEventListener::keyEvent(CvPoint fingerLocation){
	int t = 1;
	CvRect keyButton;
	for(int i = 0 ; i < 79 ; i++){
		keyButton = paperKeyboard->keyButton[i].getKeyLocation();
		if(keyButton.x-t  < fingerLocation.x  && t+keyButton.x +  keyButton.width > fingerLocation.x)
			if(keyButton.y -t < fingerLocation.y &&t+keyButton.y +  keyButton.height > fingerLocation.y){
				paperKeyboard->keyButton[i].setPress();
				paperKeyboard->keyButton[i].keyAction();
				paperKeyboard->pressedKey = paperKeyboard->keyButton[i].getKeyId();
				this->inputAvailable = false;
				return true;	
			}
	}
	return false;
}