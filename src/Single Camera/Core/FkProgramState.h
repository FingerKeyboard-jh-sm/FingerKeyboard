/**
* @file FkProgramState.h
* @author �Ѽ����б� ��ǻ�Ͱ��а� ������(jinhuk1313@gmail.com)	
* @brief ���α׷� ���� ���� ����
*/
#ifndef FK_PROG_STATE_
#define FK_PROG_STATE_
typedef enum{SET_KB_REGION,CONFIRM_KB_REGION, SET_KB_CORNER, ADJUST_KB_CORNER,
			CATCH_KB_CORNER, MOVE_KB_CORNER, CONFIRM_KB_CORNER, SET_KB_BUTTON, SET_CAM_CALIB,
			WAIT_HAND, SET_HIST,INPUT_AVAILABLE, OTHER} FkStatus;

class FkCurrentMode{
public:
	static FkStatus state;
};
#endif