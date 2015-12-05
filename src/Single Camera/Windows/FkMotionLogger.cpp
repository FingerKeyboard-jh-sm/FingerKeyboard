#include"FkMotionLogger.h"

FkMotionLogger::FkMotionLogger(FkHand* userHand){
	this->userHand[0] = &userHand[0];
	this->userHand[1] = &userHand[1];
	this->frameCount = 0;
	fout.open("motion_logging.txt");
	fout.precision(3);
	fout.widen(15);
	if(!fout.is_open())
		return;
}

void FkMotionLogger::writeMotion(){
	//프레임 번호
	fout << "프레임\t: " <<frameCount << endl;
	//손가락 번호
	fout << "손가락\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << i + 1 << "\t";
	fout<<endl;
	//손가락 x좌표
	fout << "x좌표\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << userHand[0]->finger[i].fingerTip.x << "\t";
	fout<<endl;
	//손가락 y좌표
	fout << "y좌표\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << userHand[0]->finger[i].fingerTip.y << "\t";
	fout<<endl;
	//유효성
	fout << "유효\t: ";
	for(int i = 0 ; i < 5 ; i++){
		if(userHand[0]->finger[i].validMotion)
			fout << "VALID" << "\t";
		else
			fout << "INVALID" << "\t";
	}
	fout<<endl;
	//방향
	fout << "방향\t: ";
	for(int i = 0 ; i < 5 ; i++){
		if(userHand[0]->finger[i].downOrientMotion)
			fout << "DOWN" << "\t";
		else
			fout << "UP" << "\t";
	}
	fout<<endl;

	//움직임 벡터
	fout << "벡터\t: ";
	for(int i = 0; i < 5 ; i++)
		fout << userHand[0]->finger[i].motionVector << "\t";
	fout<<endl;

	//움직임 벡터 누적
	fout << "누적\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout<<userHand[0]->finger[i].motionVectorAccumulation << "\t";
	fout<<endl<<endl;

	frameCount++;
}
FkMotionLogger::~FkMotionLogger(){
	fout.close();
}