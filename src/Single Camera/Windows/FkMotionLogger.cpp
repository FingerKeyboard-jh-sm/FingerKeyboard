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
	//������ ��ȣ
	fout << "������\t: " <<frameCount << endl;
	//�հ��� ��ȣ
	fout << "�հ���\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << i + 1 << "\t";
	fout<<endl;
	//�հ��� x��ǥ
	fout << "x��ǥ\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << userHand[0]->finger[i].fingerTip.x << "\t";
	fout<<endl;
	//�հ��� y��ǥ
	fout << "y��ǥ\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout << userHand[0]->finger[i].fingerTip.y << "\t";
	fout<<endl;
	//��ȿ��
	fout << "��ȿ\t: ";
	for(int i = 0 ; i < 5 ; i++){
		if(userHand[0]->finger[i].validMotion)
			fout << "VALID" << "\t";
		else
			fout << "INVALID" << "\t";
	}
	fout<<endl;
	//����
	fout << "����\t: ";
	for(int i = 0 ; i < 5 ; i++){
		if(userHand[0]->finger[i].downOrientMotion)
			fout << "DOWN" << "\t";
		else
			fout << "UP" << "\t";
	}
	fout<<endl;

	//������ ����
	fout << "����\t: ";
	for(int i = 0; i < 5 ; i++)
		fout << userHand[0]->finger[i].motionVector << "\t";
	fout<<endl;

	//������ ���� ����
	fout << "����\t: ";
	for(int i = 0 ; i < 5 ; i++)
		fout<<userHand[0]->finger[i].motionVectorAccumulation << "\t";
	fout<<endl<<endl;

	frameCount++;
}
FkMotionLogger::~FkMotionLogger(){
	fout.close();
}