/**
* @file FkMainWorker.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief FkMainWorker Class 정의
*/
#ifndef FK_MAIN_WORK_
#define FK_MAIN_WORK_
#include"FkCamera.h"
#include"FkProgramState.h"
#include"FkMouseListener.h"
#include"FkPreProcessor.h"
#include"FkPostProcessor.h"
#include"FkImageProcessor.h"
#include"FkThread.h"
#include"FkCondition.h"
#include"FkKey.h"
#include"FkMotionLogger.h"
#define WINDOW_NAME "Program"
class FkMainWorker : public FkThread{
	FkCamera camera;
	FkMouseListener mouseListener;
	FkPreprocessor preProcessor;
	FkPostProcessor postProcessor;
	FkImageProcessor imageProcessor;
	FkMessage* message;
	FkCondition* timer;
	FkKey* key;
	FkKey* exitKey;
	IplImage* dstImage;

	CvVideoWriter* vout;
	FkMotionLogger* motionLogger;
public:
	FkMainWorker(int keyboardType);
	void run();
	void cleanUp();
	void setWindow();
	void setExitKey(FkKey* exitKey);
	void setKey(FkKey* key);
	void setTimer(FkCondition* timer);
	void setCamera(FkCamera& camera);
	void setPaperKeyboardType(FkPaperKeyboard* paperKeyboard);
	IplImage* getButtonImage();
	void getBackgroundImage(IplImage* srcImage, IplImage* dstImage);
	~FkMainWorker();
};
#endif