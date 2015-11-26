/**
* @file FkFingerKeyboard.h
* @author �Ѽ����б� ��ǻ�Ͱ��а� ������(jinhuk1313@gmail.com)	
* @brief FkFingerKeyboard Class ����
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
	* @brief ī�޶��ɸ޶�
	* @details �޶�޶� ī�޶�
	* @author ������
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
	* @brief �����ھ�
	* @details �����ض� ����
	* @param camIndex ī�޶� ��ġ ��ȣ
	* @param keyboardType ���� Ű���� Ÿ�� �л�
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

