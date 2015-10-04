#include "FkFingerKeyboard.h"
#define WINDOW_NAME_TOP "TOP"
#define WINDOW_NAME_BOTTOM "BOTTOM"
bool FkFingerKeyboard::isCameraSet(){
	return true;
}

FkFingerKeyboard::FkFingerKeyboard(int camIndexTop, int camIndexBottom, int keyboardType) : 
	camera(camIndexTop, camIndexBottom), mouseListener(camera.getResolution()), preProcessor(keyboardType, camera.getResolution()), postProcessor(camera.getResolution()){
	dstImageTop = cvCreateImage(camera.getResolution(), IPL_DEPTH_8U, 3);
	dstImageBottom = cvCreateImage(camera.getResolution(), IPL_DEPTH_8U, 3);
	cvNamedWindow(WINDOW_NAME_TOP);
	cvNamedWindow(WINDOW_NAME_BOTTOM);
	cvSetMouseCallback(WINDOW_NAME_TOP, mouseListener.mouseClickEvent, WINDOW_NAME_TOP);
	cvSetMouseCallback(WINDOW_NAME_BOTTOM, mouseListener.mouseClickEvent, WINDOW_NAME_BOTTOM);
#ifdef _WINDOWS
	message = new FkWindowsMessage();
#endif
#ifndef _WINDOWS
	message = new FkConsoleMessage();
#endif
	this->mouseListener.setMessenger(message);
}

void FkFingerKeyboard::programRun(){
	while(true) {
		if(!this->camera.getQueryFrame(&(this->dstImageTop), &(this->dstImageBottom))) break;
		switch(FkCurrentMode::state) {
		case PREPROCESS_TOP:
			if(preProcessor.paperKeyboardRecognizer.setPaperKeyboardCornerTop(this->dstImageTop)) {
				preProcessor.paperKeyboardRecognizer.setKeyButton(this->dstImageTop);
				preProcessor.paperKeyboardRecognizer.setKeyButtonImage(this->dstImageTop);
				FkCurrentMode::state = CONFRIM_KB_BUTTON;
			}
			break;
		case CONFRIM_KB_BUTTON:
			break;
		case SET_KB_REGION_BOTTOM :
			if(mouseListener.isSettingROIBottom())
				imageProcessor.paperAreaDraggingImage(this->dstImageBottom, mouseListener);
			break;
		case CONFIRM_KB_REGION_BOTTOM: 
			preProcessor.paperKeyboardRecognizer.setSelectedPaperKeyboardBottom(mouseListener.getMouseDragArea());
			mouseListener.setBenchmarkPoint();
			imageProcessor.drawSelectedArea(this->dstImageBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom());
			break;
		case SET_KB_COLOR_BOTTOM:
			camera.setCameraPreprocessBottom();
			FkCurrentMode::state = SET_KB_CONTOUR_BOTTOM;
			break;
		case SET_KB_CONTOUR_BOTTOM:
			if(!preProcessor.paperKeyboardRecognizer.setPaperKeyboardContourBottom(this->dstImageBottom, mouseListener)){
				FkCurrentMode::state = SET_KB_CONTOUR_BOTTOM;
				mouseListener.resetMouseDragArea();
				message->showMessage("MESSAGE : Bottom Incorrect Area.");  
			}
			else {
				FkCurrentMode::state = CONFIRM_KB_CONTOUR_BOTTOM;
				camera.setCameraPostprocessBottom();
			}
			break;
		case CONFIRM_KB_CONTOUR_BOTTOM:
			preProcessor.paperKeyboardRecognizer.setKeyMaskBottomImage(this->dstImageBottom);
			break;
		case POSTPROCESS_INIT:
			camera.setCameraPostprocessBottom();
			postProcessor.fingerTipDetector.setkeyboardMaskTop(this->dstImageTop,FkPaperKeyboard::keyboardMaskTop);
			postProcessor.fingerTipDetector.setkeyboardMaskBottom(this->dstImageBottom,FkPaperKeyboard::keyboardMaskBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom());
			postProcessor.fingerTipDetector.setkeyboardMaskRectBottom();
			postProcessor.fingerTipDetector.setKeyButtonDivision(preProcessor.paperKeyboardRecognizer.getKeyButton());
			FkCurrentMode::state = INPUT_AVAILABLE;
			break;
		case INPUT_AVAILABLE:
			postProcessor.fingerTipDetector.initFingerTipPoint();
			if(postProcessor.fingerTipDetector.isTouchKeyboard(this->dstImageBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom())) {
				postProcessor.fingerTipDetector.setFingerXTop();
				postProcessor.fingerTipDetector.setFingerROITop();
				postProcessor.fingerTipDetector.detectFingerTip(this->dstImageTop);
				postProcessor.keyEventProcessing();
				postProcessor.fingerTipDetector.drawFingerTip(this->dstImageTop, this->dstImageBottom);
			}
			else 
				postProcessor.keyButtonEventListener.detachFinger();
			break;
		}	
		timeScheduler.getFPS();
		timeScheduler.printFPS(this->dstImageTop);
		cvShowImage(WINDOW_NAME_TOP, this->dstImageTop);
		cvShowImage(WINDOW_NAME_BOTTOM, this->dstImageBottom);

		char chKey = cvWaitKey(1);
	}
}

FkFingerKeyboard::~FkFingerKeyboard(){
	cvDestroyAllWindows();
}