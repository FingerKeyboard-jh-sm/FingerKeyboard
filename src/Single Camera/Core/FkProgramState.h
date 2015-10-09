/**
* @file FkProgramState.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 프로그램 동작 상태 정의
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