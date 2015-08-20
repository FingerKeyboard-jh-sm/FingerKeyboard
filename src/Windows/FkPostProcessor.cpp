#include"FkPostProcessor.h"
FkPostProcessor::FkPostProcessor(FkPaperKeyboard* paperKeyboard) : keyButtonEventListener(&fingerTipDetector.userHand[0], &fingerTipDetector.userHand[1], paperKeyboard){
	
}