/**
* @file FkPostProcessor.cpp
* @author �Ѽ����б� ��ǻ�Ͱ��а� ������(jinhuk1313@gmail.com)	
* @brief �Ĺݺ� ó����
*/
#include"FkPostProcessor.h"
FkPostProcessor::FkPostProcessor() : keyButtonEventListener(&fingerTipDetector.userHand[0], &fingerTipDetector.userHand[1]){
	
}