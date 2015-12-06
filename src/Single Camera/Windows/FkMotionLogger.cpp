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
	//������ ��ȣ
	fout << "Frame\t: " <<frameCount << endl;
	//�հ��� ��ȣ
	fout << "Finger\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << i + 1 << "\t\t";
	fout<<endl;
	//���� ������ �հ��� ��ǥ
	fout << "PrevF\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << "(" <<userHand[0]->finger[i].prevFinger->fingerTip.x << ", "<< userHand[0]->finger[i].prevFinger->fingerTip.y<<")" <<"\t";
	fout<<endl;
	//���� �������� ���� ��ǥ
	fout << "CurrF\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << "(" <<userHand[0]->finger[i].fingerTip.x << ", "<< userHand[0]->finger[i].fingerTip.y<<")" <<"\t";
	fout<<endl;
	//��ȿ��
	fout << "isValid\t: ";
	for(int i = 0 ; i < 5 ; i++){
		if(userHand[0]->finger[i].validMotion)
			fout << "VALID" << "\t\t";
		else
			fout << "INVALID" << "\t";
	}
	fout<<endl;
	//����
	fout << "Orient\t: ";
	for(int i = 0 ; i < 5 ; i++){
		if(userHand[0]->finger[i].downOrientMotion)
			fout << "DOWN" << "\t\t";
		else
			fout << "UP" << "\t\t";
	}
	fout<<endl;

	//������ ����
	fout << "Vector\t: ";
	for(int i = 0; i < 5 ; i++)
		fout << userHand[0]->finger[i].motionVector << "\t\t";
	fout<<endl;

	//������ ���� ����
	fout << "Accum\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout<<userHand[0]->finger[i].motionVectorAccumulation << "\t\t";
	fout<<endl<<endl;

	frameCount++;
}
FkMotionLogger::~FkMotionLogger(){
	fout.close();
}