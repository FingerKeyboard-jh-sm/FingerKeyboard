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