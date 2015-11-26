/**
* @file FkFingerKeyboard.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief FkFingerKeyboard Class 정의
*/
#ifdef WIN32
#include<opencv\cv.h>
#include<opencv\highgui.h>
#else
#include<cv.h>
#include<highgui.h>
#endif
#ifndef FK_PROGRAM_
#define FK_PROGRAM_
#include"FkCamera.h"
#include"FkThread.h"
#include"FkTimeScheduler.h"
#include"FkMainWorker.h"
#include"FkMessageQueue.h"
#include"FkMessage.h"
#include"FkKey.h"
#include"FkCondition.h"
#include"FkPaperKeyboard.h"
#include"FkVirtualKeyEventListener.h"

typedef enum{Type_A, Type_B} KeyboardType;
/** 
* @brief 
* @details 
* @author
* @date
* @version
*/
class FkFingerKeyboard : public FkThread{
	/** 
	* @brief 카메라케메라
	* @details 메라메라 카메라
	* @author 진혁찡
	* @date
	* @version
	*/
	FkCamera camera; ///< data member 1 description
	FkPaperKeyboard* paperKeyboard;
	FkTimeScheduler timeScheduler;
	FkMainWorker mainWorker;
	FkKey key;
	FkKey exitKey;
	FkCondition* timer;
	FkMessageQueue messageQueue;
	FkVirtualKeyEventListener virtualKeyEvnetListener;
public:
	/**
	* @brief 생성자얌
	* @details 생성해라 빠샤
	* @param camIndex 카메라 장치 번호
	* @param keyboardType 종이 키보드 타입 뿅뿅
	*/
	FkFingerKeyboard(int camIndex, int keyboardType);
	bool isCameraSet();
	void run();
	void cleanUp();
	void out();
	int getFPS();
	IplImage* getButtonImage();
	FkCamera& getCamera();
	~FkFingerKeyboard();
};
#endif

