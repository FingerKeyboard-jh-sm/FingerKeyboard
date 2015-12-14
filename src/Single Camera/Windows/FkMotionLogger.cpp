#include"FkMotionLogger.h"

FkMotionLogger::FkMotionLogger(FkHand* userHand){
	this->userHand[0] = &userHand[0];
	this->userHand[1] = &userHand[1];
	this->frameCount = 0;
	fout.open("motion_logging.txt");
	fout.precision(3);
	fout.widen(10);
	if(!fout.is_open())
		return;
}

void FkMotionLogger::writeMotion(){
	//프레임 번호
	fout << "Frame\t: " <<frameCount << endl;
	//손가락 번호
	fout << "Finger\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << i + 1 << "\t\t";
	fout<<endl;
	//이전 프레임 손가락 좌표
	fout << "PrevF\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << "(" <<userHand[0]->finger[i].prevFinger->fingerTip.x << ", "<< userHand[0]->finger[i].prevFinger->fingerTip.y<<")" <<"\t";
	fout<<endl;
	//현재 손프레임 가락 좌표
	fout << "CurrF\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << "(" <<userHand[0]->finger[i].fingerTip.x << ", "<< userHand[0]->finger[i].fingerTip.y<<")" <<"\t";
	fout<<endl;
	//유효성
	fout << "isValid\t: ";
	for(int i = 0 ; i < 5 ; i++){
		if(userHand[0]->finger[i].validMotion)
			fout << "VALID" << "\t\t";
		else
			fout << "INVALID" << "\t";
	}
	fout<<endl;
	//방향
	fout << "Orient\t: ";
	for(int i = 0 ; i < 5 ; i++){
		if(userHand[0]->finger[i].downOrientMotion)
			fout << "DOWN" << "\t\t";
		else
			fout << "UP" << "\t\t";
	}
	fout<<endl;

	//움직임 벡터
	fout << "Vector\t: ";
	for(int i = 0; i < 5 ; i++)
		fout << userHand[0]->finger[i].motionVector << "\t\t";
	fout<<endl;

	//움직임 벡터 누적
	fout << "Accum\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout<<userHand[0]->finger[i].motionVectorAccumulation << "\t\t";
	fout<<endl<<endl;

	frameCount++;
}
FkMotionLogger::~FkMotionLogger(){
	fout.close();
}