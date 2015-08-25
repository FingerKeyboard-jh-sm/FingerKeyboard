#include"FkMainWorker.h"
FkMainWorker::FkMainWorker(int keyboardType){
	dstImage = cvCreateImage(cvSize(CAM_WIDTH, CAM_HEIGHT), IPL_DEPTH_8U, 3);
	preProcessor.cameraCalibrator.readFile();
#ifdef _WINDOWS
	message = new FkWindowsMessage();
#endif
#ifndef _WINDOWS
	message = new FkConsoleMessage();
#endif
	this->mouseListener.setMessenger(message);
}
void FkMainWorker::setCamera(FkCamera& camera){
	this->camera = camera; 
}
void FkMainWorker::setPaperKeyboardType(FkPaperKeyboard* paperKeyboard){
	preProcessor.paperKeyboardRecognizer.setPaperKeyboard(paperKeyboard);
	postProcessor.keyButtonEventListener.setPaperKeyboardType(paperKeyboard);
}
IplImage* FkMainWorker::getButtonImage(){
	return preProcessor.paperKeyboardRecognizer.buttonImage;
}
void FkMainWorker::setTimer(FkCondition* timer){
	this->timer = timer;
}
void  FkMainWorker::setWindow(){
	cvNamedWindow(WINDOW_NAME);
	cvSetMouseCallback(WINDOW_NAME, mouseListener.mouseClickEvent, dstImage);
}
void FkMainWorker::run(){
	IplImage* frame;
	IplImage* bgImage = cvCreateImage(camera.getResolution(), IPL_DEPTH_8U, 3);
	//cvNamedWindow() Method must be called in run() method of thread
	setWindow();
	while(1){
		timer->await();
		//timer->timeWait();
		frame = this->camera.getQueryFrame();
		if(!frame)
			continue;
		if(preProcessor.cameraCalibrator.isCamCalibrated())
			cvFlip(frame, dstImage, 1);
		else
			cvFlip(frame, dstImage, 1);
		if(mouseListener.isSettingROI())
			imageProcessor.paperAreaDraggingImage(dstImage, mouseListener);
		if(FkCurrentMode::state){
			if(FkCurrentMode::state  == CONFIRM_KB_REGION){
				preProcessor.paperKeyboardRecognizer.setSelectedPaperKeyboard(mouseListener.getMouseDragArea());
				mouseListener.setBenchmarkPoint();
				imageProcessor.drawSelectedArea(dstImage, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboard());
			}
			else if(FkCurrentMode::state == SET_KB_CORNER){
				if(preProcessor.paperKeyboardRecognizer.setPaperKeyboardCorner(dstImage, mouseListener) == -1){
					FkCurrentMode::state = SET_KB_REGION;
					mouseListener.resetMouseDragArea();
					message->showMessage("MESSAGE : Incorrect Area.");  
				}
				else
					FkCurrentMode::state = CONFIRM_KB_CORNER;
			}
			else if(FkCurrentMode::state == CONFIRM_KB_CORNER || FkCurrentMode::state == ADJUST_KB_CORNER){
				cvSetImageROI(dstImage, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboard());
				imageProcessor.drawPaperKeyboardCorner(dstImage);
				cvResetImageROI(dstImage);
				if(mouseListener.isAdjustCorner())
					imageProcessor.paperAreaDraggingImage(dstImage, this->mouseListener);
			}
			else if(FkCurrentMode::state == CATCH_KB_CORNER){
				cvSetImageROI(dstImage, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboard());
				imageProcessor.drawPaperKeyboardCorner(dstImage);
				cvResetImageROI(dstImage);
				imageProcessor.drawSelectedArea(dstImage, mouseListener.getMouseDragArea());
			}
			else if(FkCurrentMode::state == MOVE_KB_CORNER){
				cvSetImageROI(dstImage, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboard());
				imageProcessor.drawPaperKeyboardCorner(dstImage);
				cvResetImageROI(dstImage);
			}
			else if(FkCurrentMode::state == SET_KB_BUTTON){
				preProcessor.paperKeyboardRecognizer.setKeyButton(dstImage);
				preProcessor.paperKeyboardRecognizer.setKeyButtonImage(dstImage);
				getBackgroundImage(dstImage, bgImage);
				if(preProcessor.cameraCalibrator.isCamCalibrated())
					FkCurrentMode::state = WAIT_HAND;
				else
					FkCurrentMode::state = SET_CAM_CALIB;
			}
			else if(FkCurrentMode::state == SET_CAM_CALIB){
				//preProcessor.cameraCalibrator.cameraCalibration(dstImage, this->paperKeyboard);
				FkCurrentMode::state = SET_KB_REGION;
			}
			else if(FkCurrentMode::state == WAIT_HAND){
				imageProcessor.drawHandInputCircle(dstImage);
			}
			else if(FkCurrentMode::state == SET_HIST){
				preProcessor.skinColorDetector.createSkinColorHistogram(dstImage);
				FkCurrentMode::state = INPUT_AVAILABLE;
			}
			else if(FkCurrentMode::state == INPUT_AVAILABLE){
				postProcessor.fingerTipDetector.getHandBinaryImage(dstImage, bgImage, preProcessor.skinColorDetector.skinColorHistogram);
				postProcessor.fingerTipDetector.detectHandContour(preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboard());
				postProcessor.fingerTipDetector.detectFingerTip(dstImage);
				postProcessor.fingerTipDetector.calcMotionProperty();
				imageProcessor.drawFingerTip(dstImage,postProcessor.fingerTipDetector.detectHandCount, postProcessor.fingerTipDetector.userHand);
				postProcessor.keyButtonEventListener.keyEventProcessing();
				postProcessor.keyButtonEventListener.setInputAvailable();
				postProcessor.fingerTipDetector.resetData();
			}
		}
		if(FkCurrentMode::state > CONFIRM_KB_REGION && FkCurrentMode::state < WAIT_HAND)
			imageProcessor.drawDetermineArea(dstImage, preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboard());
		cvShowImage(WINDOW_NAME, dstImage);
		
		key->lock();
#ifndef _WINDOWS
		if((cvWaitKey(1)) == 27)
			break;
#else
		cvWaitKey(1);
#endif
		key->unlock();
	}
}
void FkMainWorker::setKey(FkKey* key){
	this->key = key;
}
void getBackgroundImage(IplImage* srcImage, IplImage* dstImage){
	cvCopy(srcImage, dstImage);
	cvCvtColor(dstImage, dstImage, CV_BGR2YCrCb);
}
FkMainWorker::~FkMainWorker(){
	cvReleaseImage(&dstImage);
	delete message;
}