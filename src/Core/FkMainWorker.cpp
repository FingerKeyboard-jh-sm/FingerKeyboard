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
#ifndef WIN32
	CvRect piCamResolution = cvRect(100, 100, 440, 330); 
#endif
	setWindow();	//cvNamedWindow() Method must be called in run() method of thread
	while(1){
		key->lock();
		timer->signal();
		timer->await();
		key->unlock();
		frame = this->camera.getQueryFrame();
		if(!frame)
			continue;
		if(preProcessor.cameraCalibrator.isCamCalibrated()){
#ifdef WIN32
			cvFlip(frame, dstImage, 1);
#else
			cvFlip(frame, frame, 1);
			cvSetImageROI(frame, piCamResolution);
			cvResize(frame, dstImage);

#endif	

		}
		else{
#ifdef WIN32
			cvFlip(frame, dstImage, 1);
#else
			cvFlip(frame, frame, 1);
			cvSetImageROI(frame, piCamResolution);
			cvResize(frame, dstImage);
#endif	
		}
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
					message->showMessage("MESSAGE : 종이 키보드 선택이 정확하지 않습니다");  
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
		exitKey->lock();
#ifndef _WINDOWS
		if((cvWaitKey(1)) == 27){
			exitKey->unlock();
			break;
		}
#else
		cvWaitKey(1);
#endif
		exitKey->unlock();
	}
}
void FkMainWorker::cleanUp(){
	key->unlock();
	exitKey->unlock();
	key->lock();
	timer->signal();
	key->unlock();
}
void FkMainWorker::setKey(FkKey* key){
	this->key = key;
}
void FkMainWorker::setExitKey(FkKey* exitKey){
	this->exitKey = exitKey;
}
void FkMainWorker::getBackgroundImage(IplImage* srcImage, IplImage* dstImage){
	cvCopy(srcImage, dstImage);
	cvCvtColor(dstImage, dstImage, CV_BGR2YCrCb);
}
FkMainWorker::~FkMainWorker(){
	cvReleaseImage(&dstImage);
	delete message;
}