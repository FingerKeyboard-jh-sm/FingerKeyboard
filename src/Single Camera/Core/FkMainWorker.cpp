/**
* @file FkMainWorker.cpp
* @author �Ѽ����б� ��ǻ�Ͱ��а� ������(jinhuk1313@gmail.com)	
* @brief Finger Keyboard�� �ֵ� ������ �ô� ������ν� ���α׷� ���� ���¿� ���� �۾� ó��
*/
#include"FkMainWorker.h"
FkMainWorker::FkMainWorker(int keyboardType){
	dstImage = cvCreateImage(cvSize(CAM_WIDTH, CAM_HEIGHT), IPL_DEPTH_8U, 3);
	preProcessor.cameraCalibrator.readFile();

	motionLogger = new FkMotionLogger(postProcessor.fingerTipDetector.userHand);
	vout = cvCreateVideoWriter( "C:\\Users\\Jinhyuk\\Desktop\\Working Directory\\git_WorkSpace\\src\\VideoAnalyzer\\Test.avi", CV_FOURCC('D', 'I', 'V', '3'), 30, cvSize(CAM_WIDTH, CAM_HEIGHT), 1);
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
					message->showMessage("MESSAGE : ���� Ű���� ������ ��Ȯ���� �ʽ��ϴ�");  
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
				//method.1  �հ��� ���� 1�� ����� ����ϱ� ���ؼ� getBackgroundImage()���� dstImage�� Color Model�� HSV�� ����
			/*	postProcessor.fingerTipDetector.getHandBinaryImage(dstImage, bgImage, preProcessor.skinColorDetector.skinColorHistogram, 1);
				postProcessor.fingerTipDetector.detectHandContour(preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboard());
				postProcessor.fingerTipDetector.detectFingerTip(dstImage);*/
				
				//method.2	�հ��� ���� 2�� ����� ����ϱ� ���ؼ� getBackgroundImage()���� dstImage�� Color Model�� YCrCb�� ����
				postProcessor.fingerTipDetector.getHandBinaryImage(dstImage, bgImage, preProcessor.skinColorDetector.skinColorHistogram);
				postProcessor.fingerTipDetector.detectHandContour(preProcessor.paperKeyboardRecognizer.getSelectedPaperKeyboard());
				postProcessor.fingerTipDetector.detectFingerTip();

				postProcessor.fingerTipDetector.calcMotionProperty();

				motionLogger->writeMotion();
				imageProcessor.drawFingerTip(dstImage,postProcessor.fingerTipDetector.detectHandCount, postProcessor.fingerTipDetector.userHand);
				postProcessor.keyButtonEventListener.keyEventProcessing();
				postProcessor.keyButtonEventListener.setInputAvailable();
				postProcessor.fingerTipDetector.resetData();
				cvWriteFrame(vout, dstImage);
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
	//cvCvtColor(dstImage, dstImage, CV_BGR2HSV);
	cvCvtColor(dstImage, dstImage, CV_BGR2YCrCb);
}
FkMainWorker::~FkMainWorker(){
	cvReleaseVideoWriter(&vout);
	cvReleaseImage(&dstImage);
	delete message;
}