#ifndef FK_KEY_EVENT
#define FK_KEY_EVENT
#include"FkThread.h"
#include"FkKey.h"
#include"FkCondition.h"
#include"FkEventMessage.h"
#include"FkMessageQueue.h"
#include"FkKeyButtonProperty.h"
//FkVirtual Key Event Listener thread consume a Key event Message
//Message Processing was differance to defined each OS(e.g Windows, Unix..)
class FkVirtualKeyEventListener : public FkThread{
	FkMessageQueue* messageQueue;
public:
	FkVirtualKeyEventListener(FkMessageQueue* messageQueue);
	void run();
};
#endif