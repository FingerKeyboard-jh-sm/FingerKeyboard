/**
* @file FkPaperKeyboard.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 추상적인 종이 키보드 
*/
#include"FkPaperKeyboard.h"
CvPoint2D32f FkPaperKeyboard::keyboardCorner[4];
int FkPaperKeyboard::getKeyButtonCornerCount(){
	return this->keyButtonCount;
}
CvPoint2D32f FkPaperKeyboard::getKeyButtonCorner(int index){
	return this->keyButtonCorner[index];
}
void FkPaperKeyboard::sortPaperKeyboardCorner(){
	CvPoint2D32f temp;
	for(int i = 0 ; i < 4 ; i++){
		for(int j = 0 ; j < 3 - i ; j++){
			if(keyboardCorner[j].y > keyboardCorner[j+1].y){
				temp = keyboardCorner[j];
				keyboardCorner[j] = keyboardCorner[j+1];
				keyboardCorner[j+1] = temp;
			}
		}
	}
	for(int i =0 ; i < 2 ; i++){
		for(int j = 0 ; j < 1 -i ; i++){
			if(keyboardCorner[j].x > keyboardCorner[j+1].x){
				temp = keyboardCorner[j];
				keyboardCorner[j] = keyboardCorner[j+1];
				keyboardCorner[j+1] = temp;
			}
		}
	}
	for(int i = 0 ; i < 2 ; i++){
		for(int j = 0 ; j < 1 -i ; i++){
			if(keyboardCorner[j+2].x < keyboardCorner[j+3].x){
				temp = keyboardCorner[j+2];
				keyboardCorner[j+2] = keyboardCorner[j+3];
				keyboardCorner[j+3] = temp;
			}
		}
	}
}
void FkPaperKeyboard::cornerSortingX(int startIndex, int cornerCount){
	CvPoint2D32f tmp;
	for(int i = 0  ; i < cornerCount  ; i++){
		for(int j = startIndex ; j < (cornerCount + startIndex -1 ) -i ; j++){
			if(keyButtonCorner[j].x > keyButtonCorner[j+1].x){
				tmp = keyButtonCorner[j];
				keyButtonCorner[j] = keyButtonCorner[j+1];
				keyButtonCorner[j+1] = tmp;
			}	
		}
	}
}
void FkPaperKeyboard::cornerSortingY(int startIndex, int cornerCount){
	CvPoint2D32f tmp;
	for(int i = 0 ; i < cornerCount ; i++){
		for(int j = startIndex ; j < (startIndex + cornerCount -1 ) -i ; j++){
			if(keyButtonCorner[j].y < keyButtonCorner[j+1].y){
				tmp = keyButtonCorner[j];
				keyButtonCorner[j] = keyButtonCorner[j+1];
				keyButtonCorner[j+1] = tmp;
			}	
		}
	}
}
CvPoint2D32f* FkPaperKeyboard::getPoint(){
	return keyButtonCorner;
}