#include"FkFingerKeyboard.h"
#include<time.h>
#define WINDOW_NAME "Program"
FkFingerKeyboard::FkFingerKeyboard(int cameraDeviceIndex, int keyboardType) : camera(cameraDeviceIndex, 640, 480), preProcessor(keyboardType), postProcessor(preProcessor.paperKeyboardRecognizer.getPaperKeyboard()){
	dstImage = cvCreateImage(camera.getResolution(), IPL_DEPTH_8U, 3);
	cvNamedWindow(WINDOW_NAME);
	cvSetMouseCallback(WINDOW_NAME, mouseListener.mouseClickEvent, dstImage);
	preProcessor.cameraCalibrator.readFile();
}
bool FkFingerKeyboard::isCameraSet(){
	if(camera.isSettingCamera())
		return true;
	else
		return false;
}
void FkFingerKeyboard::programRun(){
	IplImage* frame;
	IplImage* bgImage = cvCreateImage(camera.getResolution(), IPL_DEPTH_8U, 3);
	double start, finish, duration;
	while(1){
		start = (double)(clock())/CLOCKS_PER_SEC;
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
				preProcessor.paperKeyboardRecognizer.setPaperKeyboardCorner(dstImage, mouseListener);				
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
				preProcessor.paperKeyboardRecognizer.showKeyButton(dstImage);
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
		if((cvWaitKey(30)) == 27)
			break;
		finish = (double)(clock())/CLOCKS_PER_SEC;
		duration = (finish - start);
		std::cout<<duration<<std::endl;
	}
}
FkFingerKeyboard::~FkFingerKeyboard(){
	cvDestroyWindow(WINDOW_NAME);
	cvReleaseImage(&dstImage);
}
void getBackgroundImage(IplImage* srcImage, IplImage* dstImage){
	cvCopy(srcImage, dstImage);
	cvCvtColor(dstImage, dstImage, CV_BGR2YCrCb);
}