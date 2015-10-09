/**
* @file FkMessageQueue.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief FkMessageQueue Class 정의
*/
#include<vector>
using namespace std;
#ifndef FK_MSG_QUEUE
#define FK_MSG_QUEUE
#include"FkKey.h"
#include"FkCondition.h"
#include"FkEventMessage.h"
class FkMessageQueue{
	FkKey key;
	FkCondition* msgIn;
	FkCondition* msgOut;
	vector<FkEventMessage> queue;
	vector<FkEventMessage>::iterator iterator;

public:
	FkMessageQueue();
	void enqueue(FkEventMessage msg);
	FkEventMessage dequeue();
};
#endif