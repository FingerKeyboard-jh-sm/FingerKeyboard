#include "FkFingerKeyboard.h"
#define WINDOW_NAME_TOP "TOP"
#define WINDOW_NAME_BOTTOM "BOTTOM"

#ifndef _WINDOWS
#include "MmalDualCamera.h"
#endif

#ifdef _WINDOWS
#include <Windows.h>
#endif


FkFingerKeyboard::FkFingerKeyboard(int camIndexTop, int camIndexBottom, int keyboardType) : camera(camIndexTop, camIndexBottom), 
		mouseListener(camera.getResolution()), preProcessor(keyboardType, camera.getResolution()), postProcessor(camera.getResolution()) {
	dstImageTop = cvCreateImage(camera.getResolution(), IPL_DEPTH_8U, 3);
	dstImageBottom = cvCreateImage(camera.getResolution(), IPL_DEPTH_8U, 3);
	cvNamedWindow(WINDOW_NAME_TOP, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(WINDOW_NAME_BOTTOM, CV_WINDOW_AUTOSIZE);
	#ifdef _WINDOWS
	cvCreateTrackbar("Bright", WINDOW_NAME_BOTTOM, camera.getBright(), 255, camera.setBrightness);
	cvCreateTrackbar("Contra", WINDOW_NAME_BOTTOM, camera.getContra(), 255, camera.setContrast);
	cvCreateTrackbar("Satura", WINDOW_NAME_BOTTOM, camera.getSatura(), 255, camera.setSaturation);
	cvCreateTrackbar("Exposu", WINDOW_NAME_BOTTOM, camera.getExposu(), 10, camera.setExposure);
	cvCreateTrackbar("Gain", WINDOW_NAME_BOTTOM, camera.getGain(), 10, camera.setGain);
	cvCreateTrackbar("White", WINDOW_NAME_BOTTOM, camera.getWhite(), 10000, camera.setWhiteBalance);
	//cvCreateTrackbar("Bright", WINDOW_NAME_TOP, camera.getBright(), 255, camera.setBrightnessTop);
	//cvCreateTrackbar("Contra", WINDOW_NAME_TOP, camera.getContra(), 255, camera.setContrastTop);
	//cvCreateTrackbar("Satura", WINDOW_NAME_TOP, camera.getSatura(), 255, camera.setSaturationTop);
	cvSetMouseCallback(WINDOW_NAME_TOP, mouseListener.mouseClickEvent, WINDOW_NAME_TOP);
	cvSetMouseCallback(WINDOW_NAME_BOTTOM, mouseListener.mouseClickEvent, WINDOW_NAME_BOTTOM);
	#endif
	#ifndef _WINDOWS
	cvSetMouseCallback(WINDOW_NAME_TOP, mouseListener.mouseClickEvent, (void*)WINDOW_NAME_TOP);
	cvSetMouseCallback(WINDOW_NAME_BOTTOM, mouseListener.mouseClickEvent, (void*)WINDOW_NAME_BOTTOM);
	#endif
	
#ifdef _WINDOWS
	message = new FkWindowsMessage();
#endif
#ifndef _WINDOWS
	message = new FkConsoleMessage();
#endif
	this->mouseListener.setMessenger(message);
}

void FkFingerKeyboard::programRun(){
	//////////////////////////디버깅용/////////////
	//FkCurrentMode::state = SET_KB_REGION_BOTTOM;
	///////////////////////////////////////////////
	int a = 135;
	int b = 180;
	int c = 80;
	int d = 160;
	while(true) {
#ifdef _WINDOWS	//Window
		if(!this->camera.getQueryFrame(&(this->dstImageTop), &(this->dstImageBottom))) break;
		switch(FkCurrentMode::state) {
		case PREPROCESS_TOP:
			if(preProcessor.paperKeyboardRecognizer.setPaperKeyboardCornerTop(dstImageTop)) {
				camera.setCameraPostprocessTop();
				preProcessor.paperKeyboardRecognizer.setKeyButton(dstImageTop);
				preProcessor.paperKeyboardRecognizer.setKeyButtonImage(dstImageTop);
				preProcessor.paperKeyboardRecognizer.showButtonImage();
				FkCurrentMode::state = CONFRIM_KB_BUTTON;
			}
			break;
		case CONFRIM_KB_BUTTON:
			break;
		case SET_KB_REGION_BOTTOM :
			if(mouseListener.isSettingROIBottom())
				imageProcessor.paperAreaDraggingImage(this->dstImageBottom, mouseListener);
			break;
		case CONFIRM_KB_REGION_BOTTOM : 
			preProcessor.paperKeyboardRecognizer.setSelectedPaperKeyboardBottom(mouseListener.getMouseDragArea());
			mouseListener.setBenchmarkPoint();
			imageProcessor.drawSelectedArea(this->dstImageBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom());
			camera.setCameraPreprocessBottom();
			break;
		case SET_KB_CONTOUR_BOTTOM:
			if(preProcessor.paperKeyboardRecognizer.setPaperKeyboardContourBottom(this->dstImageBottom, mouseListener) == -1){
				FkCurrentMode::state = SET_KB_REGION_BOTTOM;
				mouseListener.resetMouseDragArea();
				message->showMessage("MESSAGE : Bottom Incorrect Area.");  
			}
			else
				FkCurrentMode::state = CONFIRM_KB_CONTOUR_BOTTOM;
			camera.setCameraPostprocessBottom();
			break;
		case CONFIRM_KB_CONTOUR_BOTTOM:
			//cvSetImageROI(this->dstImageBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom());
			//imageProcessor.drawPaperKeyboardContour(this->dstImageBottom);
			//cvResetImageROI(this->dstImageBottom);
			imageProcessor.drawMaskBottom(this->dstImageBottom);
			break;
		case POSTPROCESS_INIT:
			//cvDestroyAllWindows();
			camera.setCameraPostprocessBottom();
			//postProcessor.fingerTipDetector.setBackgroundImageBottom(this->dstImageBottom); // 배경이미지 가져옴.
			//postProcessor.fingerTipDetector.setkeyboardMaskBottom(this->dstImageBottom,FkPaperKeyboard::keyboardContour, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom()); // 외각선 mask 설정.
			postProcessor.fingerTipDetector.setkeyboardMaskTop(this->dstImageTop,FkPaperKeyboard::keyboardMaskTop);
			postProcessor.fingerTipDetector.setkeyboardMaskBottom(this->dstImageBottom,FkPaperKeyboard::keyboardMaskBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom());
			postProcessor.fingerTipDetector.setkeyboardMaskRectBottom();
			postProcessor.fingerTipDetector.setKeyButtonDivision(preProcessor.paperKeyboardRecognizer.getKeyButton());
			FkCurrentMode::state = INPUT_AVAILABLE;
			break;
		case INPUT_AVAILABLE:
			//test
			//cvSetImageROI(this->dstImageBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom());
			//imageProcessor.drawPaperKeyboardContour(this->dstImageBottom);
			//cvResetImageROI(this->dstImageBottom);
			//
			//imageProcessor.drawMaskTop(this->dstImageTop);
			//imageProcessor.drawMaskBottom(this->dstImageBottom);
			postProcessor.fingerTipDetector.initFingerTipPoint();
			if(postProcessor.fingerTipDetector.isTouchKeyboard(this->dstImageBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom(),a,b,c,d)) {
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

		cvShowImage(WINDOW_NAME_TOP, this->dstImageTop);
		cvShowImage(WINDOW_NAME_BOTTOM, this->dstImageBottom);

		char chKey = cvWaitKey(1);
		
		if ( chKey == 27)
			break;
#endif
#ifndef _WINDOWS //Linux
		if ((vcos_semaphore_wait(&(camera0Set.complete_semaphore)) == VCOS_SUCCESS) && (vcos_semaphore_wait(&(camera1Set.complete_semaphore)) == VCOS_SUCCESS)  ) {
		
		memcpy(this->dstImageTop->imageData, camera0Set.image->imageData, CAMERA_VIEW_WIDTH * CAMERA_VIEW_HEIGHT * 3); //Img Copy
		memcpy(this->dstImageBottom->imageData, camera1Set.image->imageData, CAMERA_VIEW_WIDTH * CAMERA_VIEW_HEIGHT * 3); //Img Copy
		
		cvFlip(this->dstImageTop,this->dstImageTop,1);			//Img Reverse
		cvFlip(this->dstImageBottom,this->dstImageBottom,1);	//Img Reverse
		
		switch(FkCurrentMode::state) {

		case PREPROCESS_TOP:
			if(preProcessor.paperKeyboardRecognizer.setPaperKeyboardCornerTop(this->dstImageTop)) {
				preProcessor.paperKeyboardRecognizer.setKeyButton(this->dstImageTop);
				preProcessor.paperKeyboardRecognizer.setKeyButtonImage(this->dstImageTop);
				preProcessor.paperKeyboardRecognizer.showButtonImage();
				FkCurrentMode::state = CONFRIM_KB_BUTTON;
			}
			break;
		case CONFRIM_KB_BUTTON:
			break;
		case SET_KB_REGION_BOTTOM :
			if(mouseListener.isSettingROIBottom())
				imageProcessor.paperAreaDraggingImage(this->dstImageBottom, mouseListener);
			break;
		case CONFIRM_KB_REGION_BOTTOM : 
			preProcessor.paperKeyboardRecognizer.setSelectedPaperKeyboardBottom(mouseListener.getMouseDragArea());
			mouseListener.setBenchmarkPoint();
			imageProcessor.drawSelectedArea(this->dstImageBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom());
			break;
		case SET_KB_CONTOUR_BOTTOM:
			if(preProcessor.paperKeyboardRecognizer.setPaperKeyboardContourBottom(this->dstImageBottom, mouseListener) == -1){
				FkCurrentMode::state = SET_KB_REGION_BOTTOM;
				mouseListener.resetMouseDragArea();
				message->showMessage("MESSAGE : Bottom Incorrect Area.");  
			}
			else
				FkCurrentMode::state = CONFIRM_KB_CONTOUR_BOTTOM;
			break;
		case CONFIRM_KB_CONTOUR_BOTTOM:
			//cvSetImageROI(this->dstImageBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom());
			//imageProcessor.drawPaperKeyboardContour(this->dstImageBottom);
			//cvResetImageROI(this->dstImageBottom);
			imageProcessor.drawMaskBottom(this->dstImageBottom);
			break;
		case POSTPROCESS_INIT:
			//cvDestroyAllWindows();
			//postProcessor.fingerTipDetector.setBackgroundImageBottom(this->dstImageBottom); // 배경이미지 가져옴.
			//postProcessor.fingerTipDetector.setkeyboardMaskBottom(this->dstImageBottom,FkPaperKeyboard::keyboardContour, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom()); // 외각선 mask 설정.
			postProcessor.fingerTipDetector.setkeyboardMaskTop(this->dstImageTop,FkPaperKeyboard::keyboardMaskTop);
			postProcessor.fingerTipDetector.setkeyboardMaskBottom(this->dstImageBottom,FkPaperKeyboard::keyboardMaskBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom());
			postProcessor.fingerTipDetector.setkeyboardMaskRectBottom();
			postProcessor.fingerTipDetector.setKeyButtonDivision(preProcessor.paperKeyboardRecognizer.getKeyButton());
			FkCurrentMode::state = INPUT_AVAILABLE;
			break;
		case INPUT_AVAILABLE:
			//test
			//cvSetImageROI(this->dstImageBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom());
			//imageProcessor.drawPaperKeyboardContour(this->dstImageBottom);
			//cvResetImageROI(this->dstImageBottom);
			//
			//imageProcessor.drawMaskTop(this->dstImageTop);
			//imageProcessor.drawMaskBottom(this->dstImageBottom);
			postProcessor.fingerTipDetector.initFingerTipPoint();
			if(postProcessor.fingerTipDetector.isTouchKeyboard(this->dstImageBottom, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboardBottom(),a,b,c,d)) {
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
		
		cvShowImage(WINDOW_NAME_TOP, this->dstImageTop);
		cvShowImage(WINDOW_NAME_BOTTOM, this->dstImageBottom);
		char chKey = cvWaitKey(500);
		
		if ( chKey == 27)
			break;

		
#endif
		}
	}
}

FkFingerKeyboard::~FkFingerKeyboard(){
	//cvReleaseImage(&dstImageTop);
	//cvReleaseImage(&dstImageBottom);
	//cvReleaseImage(&bgImage);
	cvDestroyAllWindows();
}