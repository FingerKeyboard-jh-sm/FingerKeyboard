/**
* @file FkPostProcessor.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 후반부 처리기
*/
#include"FkPostProcessor.h"
FkPostProcessor::FkPostProcessor() : keyButtonEventListener(&fingerTipDetector.userHand[0], &fingerTipDetector.userHand[1]){
	
}