#include"FkPostProcessor.h"
FkPostProcessor::FkPostProcessor() : keyButtonEventListener(&fingerTipDetector.userHand[0], &fingerTipDetector.userHand[1]){
	
}