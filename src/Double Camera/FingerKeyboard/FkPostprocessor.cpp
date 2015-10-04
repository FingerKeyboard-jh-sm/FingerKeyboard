#include"FkPostprocessor.h"

FkPostprocessor::FkPostprocessor(CvSize camResolution) : fingerTipDetector(camResolution) {

}

void FkPostprocessor::keyEventProcessing() {
	FkKeyButton* eventKeyButton = fingerTipDetector.getEventKey();
	if(eventKeyButton) {
		keyButtonEventListener.keyEvent(eventKeyButton);
	}
}